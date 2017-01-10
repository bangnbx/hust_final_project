#include "identifywindow.h"
#include "ui_identifywindow.h"

#include <QtDebug>
#include <mysql/mysql.h>
#include "finger.h"

IdentifyWindow::IdentifyWindow(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::IdentifyWindow)
{
  ui->setupUi(this);
  ui->progressBar->hide();
  load_print_gallery();
}

IdentifyWindow::~IdentifyWindow()
{
  delete ui;
}

struct fp_print_data **print_gallery;
char **usernames;

int IdentifyWindow::load_print_gallery() {
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
  sprintf(query, "SELECT * FROM finger_data");
  if (mysql_query(con, query))
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

    MYSQL_ROW row;

    int n_rows = mysql_num_rows(result);

//    struct fp_print_data **print_gallery;
//    char **usernames;

    print_gallery = (fp_print_data**) malloc((n_rows + 1) * sizeof(fp_print_data*));
    usernames = (char**) malloc(n_rows * sizeof(char *));

    int index = 0;
    while ((row = mysql_fetch_row(result))) {
      usernames[index] = row[1];
      print_gallery[index++] = fp_print_data_from_data((unsigned char*)row[2], 12050);
    }

    print_gallery[index] = NULL; // it must be a NULL-terminated array
}

int identify() {


    // Open device
    int r = 1;
    struct fp_dscv_dev *ddev;
    struct fp_dscv_dev **discovered_devs;
    struct fp_dev *dev;


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

    size_t matched_index;
    matched_index = -1;

    r = fp_identify_finger(dev, print_gallery, &matched_index);

    if (r == 1) {
      printf("User: %s\n", usernames[matched_index]);
    } else {
      printf("Not found!\n");
    }


    out_close:
      fp_dev_close(dev);
    out:
      fp_exit();
    return 0;
}

void IdentifyWindow::on_identifyBtn_clicked()
{
  QProgressBar *progressBar = ui->progressBar;
  progressBar->hide();

  QLabel *label = this->findChild<QLabel *>("identifyMsg");
  identify();

}
