#ifndef CREATEUSERWINDOW_H
#define CREATEUSERWINDOW_H

#include <QDialog>

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

private:
    Ui::CreateUserWindow *ui;
};

#endif // CREATEUSERWINDOW_H
