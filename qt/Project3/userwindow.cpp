
#include "ui_userwindow.h"
#include "userwindow.h"

UserWindow::UserWindow(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::UserWindow)
{
  ui->setupUi(this);
}

UserWindow::~UserWindow()
{
  delete ui;
}
