#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->move(0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newUserBtn_clicked()
{
    this->close();
    CreateUserWindow *nw = new CreateUserWindow();
    nw->show();
}

void MainWindow::on_quitBtn_clicked()
{
    this->close();
}

void MainWindow::on_verifyBtn_clicked()
{
    this->close();
    VerifyWindow *nw = new VerifyWindow();
    nw->show();
}

void MainWindow::on_identifyBtn_clicked()
{
    this->close();
    IdentifyWindow *nw = new IdentifyWindow();
    nw->show();
}
