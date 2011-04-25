#include "configureartnetoutdialog.h"
#include "ui_configureartnetoutdialog.h"

#include "artnetout.h"

ConfigureArtNetOutDialog::ConfigureArtNetOutDialog(ArtNetOut * plugin, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigureArtNetOutDialog)
{
    m_plugin = plugin;

    ui->setupUi(this);

    if (plugin->m_ip == QString("")) {
        qDebug("string is empty\n") ;
        ui-> m_deviceEdit->setText("");
    } else {
        ui->m_deviceEdit->setText(plugin->m_ip);
    }
    connect(ui->m_activate, SIGNAL(clicked()), this, SLOT(activateButtonClicked()));

    updateStatus();
}

ConfigureArtNetOutDialog::~ConfigureArtNetOutDialog()
{
    delete ui;
}

void ConfigureArtNetOutDialog::activateButtonClicked() {
    m_plugin->m_ip = ui->m_deviceEdit->text();
    m_plugin->activate();

    ::usleep(10);  // Allow the activation signal get passed to doc

    updateStatus();
}
QString ConfigureArtNetOutDialog::ip()
{
  return ui->m_deviceEdit->text();
}

void ConfigureArtNetOutDialog::updateStatus()
{
  if (m_plugin->isOpen())
    {
      ui->m_statusLabel->setText("Active");
      ui->m_deviceEdit->setEnabled(false);
      ui->m_activate->setEnabled(false);
    }
  else
    {
      ui->m_statusLabel->setText("Not Active");
      ui->m_deviceEdit->setEnabled(true);
      ui->m_activate->setEnabled(true);
    }
}
