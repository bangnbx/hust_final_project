/********************************************************************************
** Form generated from reading UI file 'createuserwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
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
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_CreateUserWindow
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLineEdit *lineEditUsername;
    QPushButton *enrollBtn;
    QLabel *newMsg;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLabel *label_4;
    QLineEdit *lineEdit_3;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QLabel *label_6;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;

    void setupUi(QDialog *CreateUserWindow)
    {
        if (CreateUserWindow->objectName().isEmpty())
            CreateUserWindow->setObjectName(QStringLiteral("CreateUserWindow"));
        CreateUserWindow->resize(541, 324);
        buttonBox = new QDialogButtonBox(CreateUserWindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(400, 260, 101, 51));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);
        label = new QLabel(CreateUserWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 49, 61, 31));
        label->setTextFormat(Qt::PlainText);
        label->setScaledContents(false);
        lineEditUsername = new QLineEdit(CreateUserWindow);
        lineEditUsername->setObjectName(QStringLiteral("lineEditUsername"));
        lineEditUsername->setGeometry(QRect(120, 44, 151, 31));
        enrollBtn = new QPushButton(CreateUserWindow);
        enrollBtn->setObjectName(QStringLiteral("enrollBtn"));
        enrollBtn->setGeometry(QRect(380, 140, 131, 51));
        newMsg = new QLabel(CreateUserWindow);
        newMsg->setObjectName(QStringLiteral("newMsg"));
        newMsg->setGeometry(QRect(130, 140, 221, 31));
        label_2 = new QLabel(CreateUserWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 100, 59, 14));
        lineEdit = new QLineEdit(CreateUserWindow);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(120, 90, 151, 31));
        label_3 = new QLabel(CreateUserWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 150, 59, 14));
        lineEdit_2 = new QLineEdit(CreateUserWindow);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(120, 140, 151, 31));
        label_4 = new QLabel(CreateUserWindow);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(320, 50, 59, 14));
        lineEdit_3 = new QLineEdit(CreateUserWindow);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(380, 40, 131, 31));
        label_5 = new QLabel(CreateUserWindow);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(320, 100, 59, 14));
        lineEdit_4 = new QLineEdit(CreateUserWindow);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(380, 91, 131, 31));
        label_6 = new QLabel(CreateUserWindow);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(40, 200, 59, 14));
        radioButton = new QRadioButton(CreateUserWindow);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(120, 189, 111, 31));
        radioButton_2 = new QRadioButton(CreateUserWindow);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(120, 220, 100, 20));
        radioButton_3 = new QRadioButton(CreateUserWindow);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(120, 240, 101, 31));

        retranslateUi(CreateUserWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), CreateUserWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CreateUserWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(CreateUserWindow);
    } // setupUi

    void retranslateUi(QDialog *CreateUserWindow)
    {
        CreateUserWindow->setWindowTitle(QApplication::translate("CreateUserWindow", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("CreateUserWindow", "ID", Q_NULLPTR));
        enrollBtn->setText(QApplication::translate("CreateUserWindow", "Enroll finger", Q_NULLPTR));
        newMsg->setText(QString());
        label_2->setText(QApplication::translate("CreateUserWindow", "Password", Q_NULLPTR));
        label_3->setText(QApplication::translate("CreateUserWindow", "Name", Q_NULLPTR));
        label_4->setText(QApplication::translate("CreateUserWindow", "Address", Q_NULLPTR));
        label_5->setText(QApplication::translate("CreateUserWindow", "Phone", Q_NULLPTR));
        label_6->setText(QApplication::translate("CreateUserWindow", "Gender", Q_NULLPTR));
        radioButton->setText(QApplication::translate("CreateUserWindow", "Female", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("CreateUserWindow", "Male", Q_NULLPTR));
        radioButton_3->setText(QApplication::translate("CreateUserWindow", "Other", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CreateUserWindow: public Ui_CreateUserWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEUSERWINDOW_H
