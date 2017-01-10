#ifndef CREATEUSERWINDOW_H
#define CREATEUSERWINDOW_H

#include <QDialog>
#include <mainwindow.h>
#include <QAbstractButton>

namespace Ui {
class CreateUserWindow;
}

class CreateUserWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CreateUserWindow(QWidget *parent = 0);
    ~CreateUserWindow();

private slots:
    void on_enrollBtn_clicked();

    void on_buttonBox_clicked(QAbstractButton *button);


private:
    Ui::CreateUserWindow *ui;
    int create_user(char *username);
};

#endif // CREATEUSERWINDOW_H
