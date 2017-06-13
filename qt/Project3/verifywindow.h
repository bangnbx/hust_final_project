#ifndef VERIFYWINDOW_H
#define VERIFYWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QApplication>
#include <QProgressBar>
#include <mainwindow.h>
#include <QAbstractButton>

namespace Ui {
class VerifyWindow;
}

class VerifyWindow : public QDialog
{
  Q_OBJECT

public:
  explicit VerifyWindow(QWidget *parent = 0);
  ~VerifyWindow();

private slots:
  void on_verifyBtn_clicked();

  void on_buttonBox_clicked(QAbstractButton *button);

  void verifyAPI();

private:
  Ui::VerifyWindow *ui;
};

#endif // VERIFYWINDOW_H
