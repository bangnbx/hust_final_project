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
    QLineEdit *leID;
    QPushButton *enrollBtn;
    QLabel *newMsg;
    QLabel *label_2;
    QLineEdit *lePass;
    QLabel *label_3;
    QLineEdit *leName;
    QLabel *label_4;
    QLineEdit *leAddress;
    QLabel *label_5;
    QLineEdit *lePhone;
    QLabel *label_6;
    QRadioButton *rbFemale;
    QRadioButton *rbMale;
    QRadioButton *rbOther;

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
        leID = new QLineEdit(CreateUserWindow);
        leID->setObjectName(QStringLiteral("leID"));
        leID->setGeometry(QRect(120, 44, 151, 31));
        enrollBtn = new QPushButton(CreateUserWindow);
        enrollBtn->setObjectName(QStringLiteral("enrollBtn"));
        enrollBtn->setGeometry(QRect(380, 140, 131, 51));
        newMsg = new QLabel(CreateUserWindow);
        newMsg->setObjectName(QStringLiteral("newMsg"));
        newMsg->setGeometry(QRect(230, 210, 221, 31));
        label_2 = new QLabel(CreateUserWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 100, 59, 14));
        lePass = new QLineEdit(CreateUserWindow);
        lePass->setObjectName(QStringLiteral("lePass"));
        lePass->setGeometry(QRect(120, 90, 151, 31));
        label_3 = new QLabel(CreateUserWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 150, 59, 14));
        leName = new QLineEdit(CreateUserWindow);
        leName->setObjectName(QStringLiteral("leName"));
        leName->setGeometry(QRect(120, 140, 151, 31));
        label_4 = new QLabel(CreateUserWindow);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(320, 50, 59, 14));
        leAddress = new QLineEdit(CreateUserWindow);
        leAddress->setObjectName(QStringLiteral("leAddress"));
        leAddress->setGeometry(QRect(380, 40, 131, 31));
        label_5 = new QLabel(CreateUserWindow);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(320, 100, 59, 14));
        lePhone = new QLineEdit(CreateUserWindow);
        lePhone->setObjectName(QStringLiteral("lePhone"));
        lePhone->setGeometry(QRect(380, 91, 131, 31));
        label_6 = new QLabel(CreateUserWindow);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(40, 200, 59, 14));
        rbFemale = new QRadioButton(CreateUserWindow);
        rbFemale->setObjectName(QStringLiteral("rbFemale"));
        rbFemale->setGeometry(QRect(120, 189, 111, 31));
        rbMale = new QRadioButton(CreateUserWindow);
        rbMale->setObjectName(QStringLiteral("rbMale"));
        rbMale->setGeometry(QRect(120, 220, 100, 20));
        rbOther = new QRadioButton(CreateUserWindow);
        rbOther->setObjectName(QStringLiteral("rbOther"));
        rbOther->setGeometry(QRect(120, 240, 101, 31));

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
        rbFemale->setText(QApplication::translate("CreateUserWindow", "Female", Q_NULLPTR));
        rbMale->setText(QApplication::translate("CreateUserWindow", "Male", Q_NULLPTR));
        rbOther->setText(QApplication::translate("CreateUserWindow", "Other", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CreateUserWindow: public Ui_CreateUserWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEUSERWINDOW_H
