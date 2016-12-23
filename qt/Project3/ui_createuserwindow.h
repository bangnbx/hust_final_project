/********************************************************************************
** Form generated from reading UI file 'createuserwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEUSERWINDOW_H
#define UI_CREATEUSERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CreateUserWindow
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLineEdit *lineEditUsername;
    QPushButton *enrollBtn;

    void setupUi(QDialog *CreateUserWindow)
    {
        if (CreateUserWindow->objectName().isEmpty())
            CreateUserWindow->setObjectName(QStringLiteral("CreateUserWindow"));
        CreateUserWindow->resize(400, 300);
        buttonBox = new QDialogButtonBox(CreateUserWindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(CreateUserWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 60, 61, 21));
        lineEditUsername = new QLineEdit(CreateUserWindow);
        lineEditUsername->setObjectName(QStringLiteral("lineEditUsername"));
        lineEditUsername->setGeometry(QRect(140, 60, 113, 25));
        enrollBtn = new QPushButton(CreateUserWindow);
        enrollBtn->setObjectName(QStringLiteral("enrollBtn"));
        enrollBtn->setGeometry(QRect(260, 60, 80, 25));

        retranslateUi(CreateUserWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), CreateUserWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CreateUserWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(CreateUserWindow);
    } // setupUi

    void retranslateUi(QDialog *CreateUserWindow)
    {
        CreateUserWindow->setWindowTitle(QApplication::translate("CreateUserWindow", "Dialog", 0));
        label->setText(QApplication::translate("CreateUserWindow", "username", 0));
        enrollBtn->setText(QApplication::translate("CreateUserWindow", "Enroll", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateUserWindow: public Ui_CreateUserWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEUSERWINDOW_H
