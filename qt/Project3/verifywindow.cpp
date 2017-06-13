
#include "ui_verifywindow.h"

#include <QtDebug>
#include <mysql/mysql.h>
#include "finger.h"
#include "mysqldb.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QFile>
#include "verifywindow.h"


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
  return 0;
  MYSQL *con = mysql_init(NULL);
  if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }


  if (mysql_real_connect(con, "bangcht.me", "root", "bayogogo",
            "project", 3306, NULL, 0) == NULL)
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


int check(QLabel *label, QString nationalID, QString password) {
  qDebug() << "Start custom funtion\n";

  int r = 1;
  struct fp_dscv_dev *ddev;
  struct fp_dscv_dev **discovered_devs;
  struct fp_dev *dev;
  struct fp_print_data *new_data;
  struct fp_img *img = NULL;

  QNetworkAccessManager *networkManager = new QNetworkAccessManager();
  QUrl url("http://bangcht.me:8080/user/verify");
  QNetworkRequest request(url);
  QUrlQuery postData;
  QByteArray postData1, ba;
  QString tempQStr;
  QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
  QHttpPart dataPart;
  QFile *sendFile;
  QNetworkReply *reply;
  QEventLoop loop;
  QString returnedString;

  int escaped_size = 2 * 2418 + 1;
  char chunk[escaped_size];

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
  int res;
  qDebug() << "Opened device\n\n";

  // convert
  unsigned char *enrolled_data, *new_data1;

  // new_data = enroll(dev);
  fp_dev_img_capture(dev, 0, &img);
  fpi_img_to_print_data_bang(dev, img, &new_data);
  // res = fpi_img_compare_print_data(data, new_data);
  // fp_print_data_get_data(data, &enrolled_data);
  fp_print_data_get_data(new_data, &new_data1);
  // res = fpi_compare_data_bang(enrolled_data, new_data1);

  // save new blob to file
  FILE* pFile;
  pFile = fopen("/tmp/new_blob_local.bin", "wb");

  if (pFile){
      fwrite(new_data1, 2418, 1, pFile);
      printf("Wrote to file!");
  }
  else{
      printf("Something wrong writiyng to File.");
  }
  fclose(pFile);
  char temp_data[2418];
  for (int i = 0; i < 2418; i++) {
    temp_data[i] = new_data1[i];
  }

  ba = QByteArray::fromRawData(temp_data, 2418);

  // qDebug() << ba;

  // qDebug() << "ba len: " << ba.length();


  // saved

  // test length

  // sending to server
  //

  sendFile = new QFile("/tmp/new_blob_local.bin");
  request.setRawHeader("id", nationalID.toLatin1());
  request.setRawHeader("password", password.toLatin1());

  dataPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));
  // dataPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\"finger\""));
  dataPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"finger\"; filename=\"finger.bin\""));
  // dataPart.setBody(ba);
  sendFile->open(QIODevice::ReadOnly);
  dataPart.setBodyDevice(sendFile);
  multiPart->append(dataPart);
  reply = networkManager->post(request, multiPart);

  // connect(reply, SIGNAL(readyRead()), this, SLOT(newData()));

  QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));

  loop.exec();

  if (reply->error() == QNetworkReply::NoError) {
    returnedString = QString(reply->readAll());
    if (returnedString == "-404") {
      label->setText("Wrong ID or password");
      label->setStyleSheet("QLabel {color : red; }");
      qApp->processEvents();
    } else if (returnedString == "-401") {
      label->setText("Fingerprint does not match!");
      label->setStyleSheet("QLabel {color : red; }");
      qApp->processEvents();
    }
    else {
      label->setText("Login successfully!");
      label->setStyleSheet("QLabel {color : blue; }");
      qApp->processEvents();
      return 14;
    }
  } else {
    label->setText("Login failed, please try again!");
    label->setStyleSheet("QLabel {color : red; }");
    qApp->processEvents();
  }
  return -1;


  // mysql_escape_string(chunk, (const char *)new_data1, 2418);
  // real_string(chunk, new_data1, 2418);

  // postData.addQueryItem("finger", ba);
  // qDebug() << postData.toString(QUrl::FullyEncoded).toUtf8();

  // request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  // request.setHeader(QNetworkRequest::ContentTypeHeader, "application/form-data");
  // networkManager->post(request, ba);

  qDebug() << "SENT\n";
  // save_data_to_db(new_data1, 2418, "bang0");

  // sent to server

//  unsigned char *ret;
//  size_t ret_size;
//  ret_size = fp_print_data_get_data(new_data, &ret);
//  qDebug() << "Match score:" << res;
//  qDebug() << "End custom funtion\n";
  goto out;
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
  //QString usernameQt = ui->lineEditUsername->text();
  // QByteArray ba = usernameQt.toLatin1();
  // char *username = ba.data();
  QLabel *label = this->findChild<QLabel *>("verifyMsg");

  QString nationalID = ui->leID->text();
  QString password = ui->lePass->text();

  if (nationalID.length() == 0 || password.length() == 0) {
    label->setText("Please enter ID and password!");
    label->setStyleSheet("QLabel {color : red; }");
  } else {
    label->setText("Please enroll your finger!");
    label->setStyleSheet("QLabel {color : blue; }");
    qApp->processEvents();
    int res = check(label, nationalID, password);
    progressBar->hide();
    if (res == 14) {
      this->close();
      UserWindow *nw = new UserWindow();
      nw->show();
    }
  }
}

void VerifyWindow::on_buttonBox_clicked(QAbstractButton *button)
{
  this->close();
  MainWindow *main = new MainWindow();
  main->show();
}

void VerifyWindow::verifyAPI()
{
  return;
}
