#include "ui_createuserwindow.h"
#include <QtDebug>
#include <mysql/mysql.h>
#include "finger.h"
#include <QLabel>
#include "mysqldb.h"
#include "createuserwindow.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QFile>



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
//  QUrl url("http://bangcht.me:8080/user/new");
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
  // testAPI("a");
  QString nationalID = ui->leID->text();
  QString password = ui->lePass->text();
  QString name = ui->leName->text();
  QString address = ui->leAddress->text();
  QString phone = ui->lePhone->text();
  QString gender = "Other";
  QString returnedString;
  QLabel *label = this->findChild<QLabel *>("newMsg");

  if (nationalID.length() == 0 || password.length() == 0 || name.length() == 0 ||
      address.length() == 0 || phone.length() == 0) {
    label->setText("Please fill all information");
    label->setStyleSheet("QLabel {color : red; }");
    return;
  }

  if (ui->rbFemale->isChecked() == true)
      gender = "Female";
  else if (ui->rbMale->isChecked() == true)
      gender = "Male";

  int r = 1;
  struct fp_dscv_dev *ddev;
  struct fp_dscv_dev **discovered_devs;
  struct fp_dev *dev;
  struct fp_print_data *data;

  QNetworkAccessManager *networkManager = new QNetworkAccessManager();
  QUrl url("http://bangcht.me:8080/user/new");
  QNetworkRequest request(url);
  QUrlQuery postData;
  QByteArray postData1, ba;
  QString tempQStr;
  QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
  QHttpPart dataPart, idPart, passwordPart, namePart, addressPart, phonePart, genderPart;
  QFile *sendFile;
  QNetworkReply *reply;

  QEventLoop loop;


//  QByteArray ba = usernameQt.toLatin1();
//  char *username = ba.data();

  label->setText("Enroll until successful (5 times)");
  label->setStyleSheet("QLabel {color : blue; }");
  qApp->processEvents();

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

  label->setText("Enrollment completed");
  label->setStyleSheet("QLabel {color : blue; }");
  qApp->processEvents();

  unsigned char *ret;

  size_t ret_size;
  ret_size = fp_print_data_get_data(data, &ret);

  // save new blob to file
  FILE* pFile;
  pFile = fopen("/tmp/enroll_blob_local.bin", "wb");

  if (pFile){
      fwrite(ret, 12050, 1, pFile);
      printf("Wrote to file!");
  }
  else{
      printf("Something wrong writiyng to File.");
  }
  fclose(pFile);


  sendFile = new QFile("/tmp/enroll_blob_local.bin");
  dataPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));
  // dataPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\"finger\""));
  dataPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"finger\"; filename=\"finger.bin\""));
  // dataPart.setBody(ba);
  sendFile->open(QIODevice::ReadOnly);
  dataPart.setBodyDevice(sendFile);
  multiPart->append(dataPart);
  request.setRawHeader("id", nationalID.toLatin1());
  request.setRawHeader("password", password.toLatin1());
  request.setRawHeader("name", name.toLatin1());
  request.setRawHeader("address", address.toLatin1());
  request.setRawHeader("phone", phone.toLatin1());
  request.setRawHeader("gender", gender.toLatin1());

  reply = networkManager->post(request, multiPart);
//  if (reply->error() == QNetworkReply::NoError) {
//    qDebug() << reply->readAll();
//    label->setText("Registration completed");
//    label->setStyleSheet("QLabel {color : blue; }");
//    qApp->processEvents();
//  } else {
//    label->setText("Something went wrong, please try again!");
//    label->setStyleSheet("QLabel {color : red; }");
//    qApp->processEvents();
//  }
  QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));

  loop.exec();

  if (reply->error() == QNetworkReply::NoError) {
    returnedString = QString(reply->readAll());
    if (returnedString == "-1") {
      label->setText("ID existed");
      label->setStyleSheet("QLabel {color : red; }");
      qApp->processEvents();
    } else {
      label->setText("Registration completed!");
      label->setStyleSheet("QLabel {color : blue; }");
      qApp->processEvents();
    }
  } else {
    label->setText("Registration failed, please try again!");
    label->setStyleSheet("QLabel {color : red; }");
    qApp->processEvents();
  }


  delete reply;

out_close:
  fp_dev_close(dev);

out:
  fp_exit();
   return;



}

void CreateUserWindow::on_buttonBox_clicked(QAbstractButton *button)
{
  this->close();
  MainWindow *main = new MainWindow();
  main->show();
}
