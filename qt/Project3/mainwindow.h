#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <createuserwindow.h>
#include <verifywindow.h>
#include <identifywindow.h>
#include <userwindow.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_newUserBtn_clicked();

    void on_quitBtn_clicked();

    void on_verifyBtn_clicked();

    // void on_identifyBtn_clicked();

private:
    Ui::MainWindow *ui;
    // CreateUserWindow *createUserWindow;
};

#endif // MAINWINDOW_H
