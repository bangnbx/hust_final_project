#include "ui_createuserwindow.h"
#include <QtDebug>
#include <mysql/mysql.h>
#include "finger.h"
#include <QLabel>
#include "mysqldb.h"
#include "createuserwindow.h"

//#include <QNetworkAccessManager>
//#include <QNetworkRequest>
//#include <QNetworkReply>
//#include <QUrl>
//#include <QUrlQuery>



int testAPI(const char *data)
{
  int r = 0;
  fp_set_debug(3);
  r = fpi_test_bang("/home/bangcht/projects/DB_finger/101_1.tif", "/home/bangcht/projects/DB_finger/101_2.tif");
  // r = fpi_test_bang("\/home\/bangcht\/projects\/DB_finger\/101_1.tif", "\/home\/bangcht\/projects\/DB_finger\/101_2.tif");
  // r = fpi_test_bang("a", "b");
  qDebug() << "Score:" << r;
//  // call API here
//  QNetworkAccessManager *networkManager = new QNetworkAccessManager();
//  QUrl url("http://localhost:8080/user/new");
//  QNetworkRequest request(url);
//  QUrlQuery postData;
//  postData.addQueryItem("finger", data);
//  printf("%s\n", data);
//  postData.addQueryItem("username", "bangcht");

//  request.setHeader(QNetworkRequest::ContentTypeHeader,
//      "application/x-www-form-urlencoded");
//  networkManager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
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
  qDebug() << "Enrolled size: ";
  qDebug() << ret_size;
  qDebug() << "\n";
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
  testAPI("a");
  return;
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
