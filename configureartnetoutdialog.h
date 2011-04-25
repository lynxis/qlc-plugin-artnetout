#ifndef CONFIGUREARTNETOUTDIALOG_H
#define CONFIGUREARTNETOUTDIALOG_H

#include <QDialog>

namespace Ui {
    class ConfigureArtNetOutDialog;
}

class ConfigureArtNetOutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigureArtNetOutDialog(ArtNetOut* plugin, QWidget *parent = 0);
    ~ConfigureArtNetOutDialog();
    QString ip();
private:
    Ui::ConfigureArtNetOutDialog *ui;
};

#endif // CONFIGUREARTNETOUTDIALOG_H
