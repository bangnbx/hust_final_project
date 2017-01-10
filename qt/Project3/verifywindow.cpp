#include "verifywindow.h"
#include "ui_verifywindow.h"

#include <QtDebug>
#include <mysql/mysql.h>
#include "finger.h"

VerifyWindow::VerifyWindow(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::VerifyWindow)
{
  ui->setupUi(this);
  ui->progressBar->hide();
  this->move(0, 0);
}

VerifyWindow::~VerifyWindow()
{
  delete ui;
}

int scan_and_verify(char *username)
{
  int r = 1;
  struct fp_dscv_dev *ddev;
  struct fp_dscv_dev **discovered_devs;
  struct fp_dev *dev;
  struct fp_print_data *data;

  r = fp_init();
  if (r < 0) {
    qDebug() << "Failed to initialize libfprint\n";
    exit(1);
  }
  fp_set_debug(3);

  discovered_devs = fp_discover_devs();
  if (!discovered_devs) {
    qDebug() << "Could not discover devices\n";
    goto out;
  }

  ddev = discover_device(discovered_devs);
  if (!ddev) {
    qDebug() << "No devices detected.\n";
    goto out;
  }

  dev = fp_dev_open(ddev);
  fp_dscv_devs_free(discovered_devs);
  if (!dev) {
    qDebug() << "Could not open device.\n";
    goto out;
  }

  qDebug() << "Opened device\n\n";
  data = enroll(dev);
  if (!data)
    goto out_close;

  unsigned char *ret;

  size_t ret_size;
  ret_size = fp_print_data_get_data(data, &ret);

  // save_data_to_db(ret, ret_size, username);
  free(ret);
  fp_print_data_free(data);
out_close:
  fp_dev_close(dev);
out:
  fp_exit();
  return r;
}

int get_data_from_username(char *username, struct fp_print_data **data)
{
  MYSQL *con = mysql_init(NULL);
  if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

  if (mysql_real_connect(con, "localhost", "root", "rootpassword",
            "project3", 0, NULL, 0) == NULL)
    {
      mysql_close(con);
      return 2;
    }
  char query[300];
  sprintf(query, "SELECT data FROM finger_data WHERE username=('%s')", username);
  if (mysql_query(con, query))

  //if (mysql_query(con, "SELECT data FROM finger_data WHERE username='bangcht'"))
    {
      mysql_close(con);
      return 2;
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL)
    {
      mysql_close(con);
      return 2;
    }


    MYSQL_ROW row = mysql_fetch_row(result);

    unsigned long *lengths = mysql_fetch_lengths(result);
//    FILE* f = fopen("bangcht_new.bin", "wb");
//    fwrite(row[0], lengths[0], 1, f);

//    for (size_t i = 0; i < lengths[0]; i++){
//        fwrite(&row[0][i], sizeof(row[0][i]), 1, f);
//    }


//    fclose(f);
    if (lengths == NULL) {
      mysql_close(con);
      return 2;
    }
//    struct fp_print_data **data_fingers;
//    data_fingers = (fp_print_data**) malloc(1 * sizeof(fp_print_data*));

    *data = fp_print_data_from_data((unsigned char*)row[0], lengths[0]);
    return 0;
}

int check(struct fp_print_data *data, QLabel *label) {
  int r = 1;
  struct fp_dscv_dev *ddev;
  struct fp_dscv_dev **discovered_devs;
  struct fp_dev *dev;
  struct fp_print_data *new_data;


  r = fp_init();
  if (r < 0) {
    qDebug() << "Failed to initialize libfprint\n";
    exit(1);
  }
  fp_set_debug(3);

  discovered_devs = fp_discover_devs();
  if (!discovered_devs) {
    qDebug() << "Could not discover devices\n";
    goto out;
  }

  ddev = discover_device(discovered_devs);
  if (!ddev) {
    qDebug() << "No devices detected.\n";
    goto out;
  }

  dev = fp_dev_open(ddev);
  fp_dscv_devs_free(discovered_devs);
  if (!dev) {
    qDebug() << "Could not open device.\n";
    goto out;
  }

  qDebug() << "Opened device\n\n";
  int res;
  res = fp_verify_finger(dev, data);
  label->setText("Login failed");
  label->setStyleSheet("QLabel {color : red; }");
  switch (res) {
  case FP_VERIFY_NO_MATCH:
    printf("FP_VERIFY_NO_MATCH\n");
    break;
  case FP_VERIFY_MATCH:
    label->setText("Login sucessfully");
    label->setStyleSheet("QLabel {color : blue; }");
    printf("FP_VERIFY_MATCH\n");
    break;
  case FP_VERIFY_RETRY:
    printf("FP_VERIFY_RETRY\n");
    break;
  case FP_VERIFY_RETRY_TOO_SHORT:
    printf("FP_VERIFY_RETRY_TOO_SHORT\n");
    break;
  case FP_VERIFY_RETRY_CENTER_FINGER:
    printf("FP_VERIFY_RETRY_CENTER_FINGER\n");
    break;
  case FP_VERIFY_RETRY_REMOVE_FINGER:
    printf("FP_VERIFY_RETRY_REMOVE_FINGER\n");
    break;
  default:
    printf("FAIL_DUE_TO_UNKNOWN_REASON\n");
    break;
  }
  out_close:
    fp_dev_close(dev);
  out:
    fp_exit();
    return r;
}

void VerifyWindow::on_verifyBtn_clicked()
{
  QProgressBar *progressBar = ui->progressBar;
  progressBar->hide();
  QString usernameQt = ui->lineEditUsername->text();
  QByteArray ba = usernameQt.toLatin1();
  char *username = ba.data();

  QLabel *label = this->findChild<QLabel *>("verifyMsg");

  struct fp_print_data *data;
  int r = get_data_from_username(username, &data);
  if (r == 0) {
    label->setText("Please enroll your finger");
    label->setStyleSheet("QLabel {color : blue; }");
    progressBar->show();

    qApp->processEvents();
    check(data, label);
    progressBar->hide();
  } else {
    printf("Username not found!");
    label->setText("Username not found");
    label->setStyleSheet("QLabel {color : red; }");
  }
}

void VerifyWindow::on_buttonBox_clicked(QAbstractButton *button)
{
  this->close();
  MainWindow *main = new MainWindow();
  main->show();
}
