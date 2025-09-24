#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "settingsdialog.h"

#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_settingsButton_clicked()
{
    SettingsDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        _cityName = dialog.res_cityName();
        _lon = dialog.res_lon();
        _lat = dialog.res_lat();

        saveSettings();
    }
}

void MainWindow::on_settings_updated()
{
    if (_cityName.isEmpty()) {
        ui->cityLabel->setText("Select a city");
    } else {
        ui->cityLabel->setText(_cityName);
    }
}

void MainWindow::saveSettings()
{
    QSettings settings("sidbro", "weather-2");

    settings.beginGroup("general");
    settings.setValue("cityName", _cityName);
    settings.setValue("lon", _lon);
    settings.setValue("lat", _lat);
    settings.endGroup();

    emit on_settings_updated();
}

void MainWindow::loadSettings()
{
    QSettings settings("sidbro", "weather-2");

    settings.beginGroup("general");
    _cityName = settings.value("cityName", QString()).toString();
    _lon = settings.value("lon", 0.0).toDouble();
    _lat = settings.value("lat", 0.0).toDouble();
    settings.endGroup();

    emit on_settings_updated();
}

