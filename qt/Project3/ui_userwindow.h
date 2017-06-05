/********************************************************************************
** Form generated from reading UI file 'userwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERWINDOW_H
#define UI_USERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_UserWindow
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLabel *label;

    void setupUi(QDialog *UserWindow)
    {
        if (UserWindow->objectName().isEmpty())
            UserWindow->setObjectName(QStringLiteral("UserWindow"));
        UserWindow->resize(545, 320);
        pushButton = new QPushButton(UserWindow);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(350, 250, 151, 51));
        pushButton_2 = new QPushButton(UserWindow);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 70, 151, 101));
        QIcon icon;
        icon.addFile(QStringLiteral("../../../vote_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon);
        pushButton_2->setIconSize(QSize(70, 70));
        pushButton_3 = new QPushButton(UserWindow);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(180, 70, 171, 101));
        QIcon icon1;
        icon1.addFile(QStringLiteral("../../../invoice.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_3->setIcon(icon1);
        pushButton_3->setIconSize(QSize(90, 90));
        pushButton_4 = new QPushButton(UserWindow);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(360, 70, 171, 101));
        QIcon icon2;
        icon2.addFile(QStringLiteral("../../../public_service.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_4->setIcon(icon2);
        pushButton_4->setIconSize(QSize(100, 100));
        label = new QLabel(UserWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 231, 16));

        retranslateUi(UserWindow);

        QMetaObject::connectSlotsByName(UserWindow);
    } // setupUi

    void retranslateUi(QDialog *UserWindow)
    {
        UserWindow->setWindowTitle(QApplication::translate("UserWindow", "Dialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("UserWindow", "Quit", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("UserWindow", "Vote", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("UserWindow", "Invoices", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("UserWindow", "Services", Q_NULLPTR));
        label->setText(QApplication::translate("UserWindow", "Welcome to e-goverment system", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class UserWindow: public Ui_UserWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERWINDOW_H
