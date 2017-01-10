#ifndef VERIFYWINDOW_H
#define VERIFYWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QApplication>
#include <QProgressBar>

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

private:
  Ui::VerifyWindow *ui;
};

#endif // VERIFYWINDOW_H
