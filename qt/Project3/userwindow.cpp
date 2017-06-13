
#include "ui_userwindow.h"
#include "userwindow.h"

UserWindow::UserWindow(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::UserWindow)
{
  ui->setupUi(this);
  this->move(0, 0);
}

UserWindow::~UserWindow()
{
  delete ui;
}

void UserWindow::on_pushButton_clicked()
{
  this->close();
  MainWindow *main = new MainWindow();
  main->show();
}
