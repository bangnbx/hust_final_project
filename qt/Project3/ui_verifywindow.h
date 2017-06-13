/********************************************************************************
** Form generated from reading UI file 'verifywindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
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
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_VerifyWindow
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *leID;
    QPushButton *verifyBtn;
    QLabel *verifyMsg;
    QProgressBar *progressBar;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lePass;

    void setupUi(QDialog *VerifyWindow)
    {
        if (VerifyWindow->objectName().isEmpty())
            VerifyWindow->setObjectName(QStringLiteral("VerifyWindow"));
        VerifyWindow->resize(544, 324);
        buttonBox = new QDialogButtonBox(VerifyWindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(150, 280, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);
        leID = new QLineEdit(VerifyWindow);
        leID->setObjectName(QStringLiteral("leID"));
        leID->setGeometry(QRect(160, 44, 231, 51));
        verifyBtn = new QPushButton(VerifyWindow);
        verifyBtn->setObjectName(QStringLiteral("verifyBtn"));
        verifyBtn->setGeometry(QRect(160, 160, 231, 41));
        verifyMsg = new QLabel(VerifyWindow);
        verifyMsg->setObjectName(QStringLiteral("verifyMsg"));
        verifyMsg->setGeometry(QRect(170, 210, 211, 41));
        progressBar = new QProgressBar(VerifyWindow);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setEnabled(true);
        progressBar->setGeometry(QRect(170, 250, 211, 23));
        progressBar->setMaximum(0);
        progressBar->setValue(-1);
        label = new QLabel(VerifyWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 70, 59, 14));
        label_2 = new QLabel(VerifyWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(80, 120, 59, 14));
        lePass = new QLineEdit(VerifyWindow);
        lePass->setObjectName(QStringLiteral("lePass"));
        lePass->setGeometry(QRect(160, 100, 231, 41));
        lePass->setInputMethodHints(Qt::ImhHiddenText);

        retranslateUi(VerifyWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), VerifyWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), VerifyWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(VerifyWindow);
    } // setupUi

    void retranslateUi(QDialog *VerifyWindow)
    {
        VerifyWindow->setWindowTitle(QApplication::translate("VerifyWindow", "Dialog", Q_NULLPTR));
        verifyBtn->setText(QApplication::translate("VerifyWindow", "Login", Q_NULLPTR));
        verifyMsg->setText(QString());
        label->setText(QApplication::translate("VerifyWindow", "ID", Q_NULLPTR));
        label_2->setText(QApplication::translate("VerifyWindow", "Password", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class VerifyWindow: public Ui_VerifyWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VERIFYWINDOW_H
