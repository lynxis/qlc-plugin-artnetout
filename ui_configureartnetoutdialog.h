/********************************************************************************
** Form generated from reading UI file 'configureartnetoutdialog.ui'
**
** Created: Mon Apr 25 18:41:24 2011
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGUREARTNETOUTDIALOG_H
#define UI_CONFIGUREARTNETOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ConfigureArtNetOutDialog
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ConfigureArtNetOutDialog)
    {
        if (ConfigureArtNetOutDialog->objectName().isEmpty())
            ConfigureArtNetOutDialog->setObjectName(QString::fromUtf8("ConfigureArtNetOutDialog"));
        ConfigureArtNetOutDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(ConfigureArtNetOutDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(ConfigureArtNetOutDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ConfigureArtNetOutDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ConfigureArtNetOutDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ConfigureArtNetOutDialog);
    } // setupUi

    void retranslateUi(QDialog *ConfigureArtNetOutDialog)
    {
        ConfigureArtNetOutDialog->setWindowTitle(QApplication::translate("ConfigureArtNetOutDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConfigureArtNetOutDialog: public Ui_ConfigureArtNetOutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGUREARTNETOUTDIALOG_H
