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

    QString res_cityName() const;
    double res_lon() const;
    double res_lat() const;

private slots:
    void on_lineEdit_textEdited(const QString &arg1);

private:
    void handleGeocodingComplete(const QString &errorString, const QString &cityName, double lon, double lat);
    void startGeocoding();

    Ui::SettingsDialog *ui;
    Geocoding *geocoding;
    QTimer *timer;
    QString lastQuery;

    QString _res_cityName;
    double _res_lon;
    double _res_lat;
};

#endif // SETTINGSDIALOG_H
