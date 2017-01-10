/********************************************************************************
** Form generated from reading UI file 'identifywindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IDENTIFYWINDOW_H
#define UI_IDENTIFYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_IdentifyWindow
{
public:
    QDialogButtonBox *buttonBox;
    QPushButton *identifyBtn;
    QLabel *identifyMsg;
    QProgressBar *progressBar;

    void setupUi(QDialog *IdentifyWindow)
    {
        if (IdentifyWindow->objectName().isEmpty())
            IdentifyWindow->setObjectName(QStringLiteral("IdentifyWindow"));
        IdentifyWindow->resize(400, 300);
        buttonBox = new QDialogButtonBox(IdentifyWindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        identifyBtn = new QPushButton(IdentifyWindow);
        identifyBtn->setObjectName(QStringLiteral("identifyBtn"));
        identifyBtn->setGeometry(QRect(220, 80, 81, 25));
        identifyMsg = new QLabel(IdentifyWindow);
        identifyMsg->setObjectName(QStringLiteral("identifyMsg"));
        identifyMsg->setGeometry(QRect(90, 110, 211, 17));
        progressBar = new QProgressBar(IdentifyWindow);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setEnabled(true);
        progressBar->setGeometry(QRect(90, 130, 211, 23));
        progressBar->setMaximum(0);
        progressBar->setValue(-1);

        retranslateUi(IdentifyWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), IdentifyWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), IdentifyWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(IdentifyWindow);
    } // setupUi

    void retranslateUi(QDialog *IdentifyWindow)
    {
        IdentifyWindow->setWindowTitle(QApplication::translate("IdentifyWindow", "Dialog", 0));
        identifyBtn->setText(QApplication::translate("IdentifyWindow", "Identify", 0));
        identifyMsg->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class IdentifyWindow: public Ui_IdentifyWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IDENTIFYWINDOW_H
