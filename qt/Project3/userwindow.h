#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QDialog>

namespace Ui {
class UserWindow;
}

class UserWindow : public QDialog
{
  Q_OBJECT

public:
  explicit UserWindow(QWidget *parent = 0);
  ~UserWindow();

private:
  Ui::UserWindow *ui;
};

#endif // USERWINDOW_H
