/********************************************************************************
** Form generated from reading UI file 'configureartnetout.ui'
**
** Created: Mon Apr 25 02:11:24 2011
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGUREARTNETOUT_H
#define UI_CONFIGUREARTNETOUT_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_UI_ConfigureArtNetOut
{
public:
    QGroupBox *m_deviceGroup;
    QLineEdit *m_deviceEdit;
    QGroupBox *m_statusGroup;
    QLabel *m_statusLabel;
    QPushButton *m_activate;
    QPushButton *m_ok;
    QPushButton *m_cancel;

    void setupUi(QDialog *UI_ConfigureArtNetOut)
    {
        if (UI_ConfigureArtNetOut->objectName().isEmpty())
            UI_ConfigureArtNetOut->setObjectName(QString::fromUtf8("UI_ConfigureArtNetOut"));
        UI_ConfigureArtNetOut->resize(269, 194);
        m_deviceGroup = new QGroupBox(UI_ConfigureArtNetOut);
        m_deviceGroup->setObjectName(QString::fromUtf8("m_deviceGroup"));
        m_deviceGroup->setGeometry(QRect(10, 10, 250, 60));
        m_deviceEdit = new QLineEdit(m_deviceGroup);
        m_deviceEdit->setObjectName(QString::fromUtf8("m_deviceEdit"));
        m_deviceEdit->setGeometry(QRect(10, 20, 230, 22));
        m_statusGroup = new QGroupBox(UI_ConfigureArtNetOut);
        m_statusGroup->setObjectName(QString::fromUtf8("m_statusGroup"));
        m_statusGroup->setGeometry(QRect(10, 80, 250, 60));
        m_statusLabel = new QLabel(m_statusGroup);
        m_statusLabel->setObjectName(QString::fromUtf8("m_statusLabel"));
        m_statusLabel->setGeometry(QRect(10, 20, 140, 22));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        m_statusLabel->setFont(font);
        m_statusLabel->setFrameShape(QFrame::StyledPanel);
        m_statusLabel->setFrameShadow(QFrame::Sunken);
        m_statusLabel->setAlignment(Qt::AlignCenter);
        m_statusLabel->setWordWrap(false);
        m_activate = new QPushButton(m_statusGroup);
        m_activate->setObjectName(QString::fromUtf8("m_activate"));
        m_activate->setGeometry(QRect(160, 20, 80, 22));
        m_ok = new QPushButton(UI_ConfigureArtNetOut);
        m_ok->setObjectName(QString::fromUtf8("m_ok"));
        m_ok->setGeometry(QRect(80, 160, 80, 22));
        m_ok->setDefault(true);
        m_cancel = new QPushButton(UI_ConfigureArtNetOut);
        m_cancel->setObjectName(QString::fromUtf8("m_cancel"));
        m_cancel->setGeometry(QRect(170, 160, 80, 22));
        QWidget::setTabOrder(m_cancel, m_deviceEdit);
        QWidget::setTabOrder(m_deviceEdit, m_activate);
        QWidget::setTabOrder(m_activate, m_ok);

        retranslateUi(UI_ConfigureArtNetOut);
        QObject::connect(m_cancel, SIGNAL(clicked()), UI_ConfigureArtNetOut, SLOT(reject()));
        QObject::connect(m_ok, SIGNAL(clicked()), UI_ConfigureArtNetOut, SLOT(accept()));
        QObject::connect(m_activate, SIGNAL(clicked()), UI_ConfigureArtNetOut, SLOT(slotActivateClicked()));

        QMetaObject::connectSlotsByName(UI_ConfigureArtNetOut);
    } // setupUi

    void retranslateUi(QDialog *UI_ConfigureArtNetOut)
    {
        UI_ConfigureArtNetOut->setWindowTitle(QApplication::translate("UI_ConfigureArtNetOut", "Configure ArtNet Plugin", 0, QApplication::UnicodeUTF8));
        m_deviceGroup->setTitle(QApplication::translate("UI_ConfigureArtNetOut", "IP:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        m_deviceEdit->setToolTip(QApplication::translate("UI_ConfigureArtNetOut", "The IP Address to bind to, empty will use the first non-loopback address", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        m_statusGroup->setTitle(QApplication::translate("UI_ConfigureArtNetOut", "Status", 0, QApplication::UnicodeUTF8));
        m_statusLabel->setText(QApplication::translate("UI_ConfigureArtNetOut", "Not Active", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        m_activate->setToolTip(QApplication::translate("UI_ConfigureArtNetOut", "Activate the interface. Pressing this button also saves settings.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        m_activate->setText(QApplication::translate("UI_ConfigureArtNetOut", "&Activate", 0, QApplication::UnicodeUTF8));
        m_ok->setText(QApplication::translate("UI_ConfigureArtNetOut", "&OK", 0, QApplication::UnicodeUTF8));
        m_cancel->setText(QApplication::translate("UI_ConfigureArtNetOut", "&Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UI_ConfigureArtNetOut: public Ui_UI_ConfigureArtNetOut {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGUREARTNETOUT_H
