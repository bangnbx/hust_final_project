/********************************************************************************
** Form generated from reading UI file 'verifywindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VERIFYWINDOW_H
#define UI_VERIFYWINDOW_H

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

class Ui_VerifyWindow
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEditUsername;
    QPushButton *verifyBtn;
    QLabel *verifyMsg;

    void setupUi(QDialog *VerifyWindow)
    {
        if (VerifyWindow->objectName().isEmpty())
            VerifyWindow->setObjectName(QStringLiteral("VerifyWindow"));
        VerifyWindow->resize(400, 300);
        buttonBox = new QDialogButtonBox(VerifyWindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEditUsername = new QLineEdit(VerifyWindow);
        lineEditUsername->setObjectName(QStringLiteral("lineEditUsername"));
        lineEditUsername->setGeometry(QRect(80, 80, 113, 25));
        verifyBtn = new QPushButton(VerifyWindow);
        verifyBtn->setObjectName(QStringLiteral("verifyBtn"));
        verifyBtn->setGeometry(QRect(210, 80, 80, 25));
        verifyMsg = new QLabel(VerifyWindow);
        verifyMsg->setObjectName(QStringLiteral("verifyMsg"));
        verifyMsg->setGeometry(QRect(80, 110, 211, 17));

        retranslateUi(VerifyWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), VerifyWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), VerifyWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(VerifyWindow);
    } // setupUi

    void retranslateUi(QDialog *VerifyWindow)
    {
        VerifyWindow->setWindowTitle(QApplication::translate("VerifyWindow", "Dialog", 0));
        verifyBtn->setText(QApplication::translate("VerifyWindow", "Verify", 0));
        verifyMsg->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VerifyWindow: public Ui_VerifyWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VERIFYWINDOW_H
