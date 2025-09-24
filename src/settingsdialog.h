#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "geocoding.h"

#include <QTimer>
#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

private slots:
    void on_lineEdit_textEdited(const QString &arg1);

private:
    Ui::SettingsDialog *ui;

    bool to_update = true;
    Geocoding *geocoding;
    QTimer *timer;
};

#endif // SETTINGSDIALOG_H
