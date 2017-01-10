#ifndef IDENTIFYWINDOW_H
#define IDENTIFYWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QApplication>
#include <QProgressBar>

namespace Ui {
class IdentifyWindow;
}

class IdentifyWindow : public QDialog
{
  Q_OBJECT

public:
  explicit IdentifyWindow(QWidget *parent = 0);
  ~IdentifyWindow();

private slots:
  void on_identifyBtn_clicked();

private:
  Ui::IdentifyWindow *ui;
  int load_print_gallery();
};

#endif // IDENTIFYWINDOW_H
