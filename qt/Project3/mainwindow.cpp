#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // connect(newUserBtn, SIGNAL(click()), this, SLOT(openCreateUserWindow()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newUserBtn_clicked()
{
    CreateUserWindow *nw = new CreateUserWindow();
    nw->show();
    // this->hide();
}

void MainWindow::on_quitBtn_clicked()
{
    this->close();
}

void MainWindow::on_verifyBtn_clicked()
{
    VerifyWindow *nw = new VerifyWindow();
    nw->show();
}
