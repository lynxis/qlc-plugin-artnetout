#include "configureartnetoutdialog.h"
#include "ui_configureartnetoutdialog.h"

ConfigureArtNetOutDialog::ConfigureArtNetOutDialog(ArtNetOut* plugin, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigureartnetoutDialog)
{
    ASSERT(plugin != NULL);
    m_plugin = plugin;

    ui->setupUi(this);

    if (plugin->m_ip == QString("")) {
        printf("string is empty\n") ;
        m_deviceEdit->setText("");
    } else {
        m_deviceEdit->setText(plugin->m_ip);
    }

    updateStatus();
}

ConfigureArtNetOutDialog::~ConfigureArtNetOutDialog()
{
    delete ui;
}

QString ConfigureArtNetOutDialog::ip()
{
  return m_deviceEdit->text();
}

