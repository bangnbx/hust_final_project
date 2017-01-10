#include "createuserwindow.h"
#include "ui_createuserwindow.h"
#include <QtDebug>
#include <mysql/mysql.h>
#include "finger.h"
#include <QLabel>


int init_mysql(MYSQL *mysql) {

  if (mysql_init(mysql) == NULL) {
    printf("\nInitialization error\n");
    return 2;
  }
  if (mysql_real_connect(mysql, "localhost", "root", "rootpassword",
            "project3", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(mysql));
        mysql_close(mysql);
        return 2;
    }

  return 0;
}

int save_data_to_db(unsigned char *data, size_t data_size, char *username)
{
  MYSQL con;
  init_mysql(&con);

  // insert
  int escaped_size = 2 * data_size + 1;
  char chunk[escaped_size];
  mysql_real_escape_string(&con, chunk, (const char*)data, data_size);
  const char* query_template =  "INSERT INTO finger_data(username, data, data_size) VALUES ('%s', '%s', '%d')";
  size_t template_len = strlen(query_template);
  int query_buffer_len = template_len + escaped_size + strlen(username) + sizeof(data_size);
  char query[query_buffer_len];
  int query_len = snprintf(query, query_buffer_len, query_template, username, chunk, data_size);

  if (mysql_real_query(&con, query, query_len))
  {
    printf("Something went wrong when INSERT");
    return 2;
  }
//  FILE* f = fopen("bangcht.bin", "wb");
//  for (size_t i = 0; i < data_size; i++)
//      fwrite(&data[i], sizeof(data[i]), 1, f);
//  fclose(f);

  mysql_close(&con);
  return 0;
}

int CreateUserWindow::create_user(char *username)
{
  int r = 1;
  struct fp_dscv_dev *ddev;
  struct fp_dscv_dev **discovered_devs;
  struct fp_dev *dev;
  struct fp_print_data *data;

  QLabel *label = this->findChild<QLabel *>("newMsg");


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
  if (!data) {
    label->setText("Error! Please try again");
    label->setStyleSheet("QLabel {color : red; }");
    goto out_close;
  }


  unsigned char *ret;

  size_t ret_size;
  ret_size = fp_print_data_get_data(data, &ret);

  save_data_to_db(ret, ret_size, username);
  free(ret);
  fp_print_data_free(data);
  label->setText("Saved");
  label->setStyleSheet("QLabel {color : blue; }");
out_close:
  fp_dev_close(dev);

out:
  fp_exit();
  return r;
}

CreateUserWindow::CreateUserWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateUserWindow)
{
    ui->setupUi(this);
    this->move(0, 0);
}

CreateUserWindow::~CreateUserWindow()
{
    delete ui;
}

void CreateUserWindow::on_enrollBtn_clicked()
{
  QString usernameQt = ui->lineEditUsername->text();
  QLabel *label = this->findChild<QLabel *>("newMsg");
  QByteArray ba = usernameQt.toLatin1();
  char *username = ba.data();
  if (strlen(username) == 0) {
    label->setText("Invalid username");
    label->setStyleSheet("QLabel {color : red; }");
  } else {
    label->setText("Enroll until successful (5 times)");
    label->setStyleSheet("QLabel {color : blue; }");
    qApp->processEvents();
    create_user(username);
  }
}

void CreateUserWindow::on_buttonBox_clicked(QAbstractButton *button)
{
  this->close();
  MainWindow *main = new MainWindow();
  main->show();
}
