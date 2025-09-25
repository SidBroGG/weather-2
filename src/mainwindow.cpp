#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "settingsdialog.h"

#include <QSettings>
#include <QDebug>

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

void MainWindow::settings_updated()
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

    settings.beginGroup("General");
    settings.setValue("cityName", _cityName);
    settings.setValue("lon", _lon);
    settings.setValue("lat", _lat);
    settings.endGroup();

    settings_updated();
}

void MainWindow::loadSettings()
{
    QSettings settings("sidbro", "weather-2");

    qDebug() << "Loading settings from" << settings.fileName();

    settings.beginGroup("General");
    _cityName = settings.value("cityName", QString()).toString();
    _lon = settings.value("lon", 0.0).toDouble();
    _lat = settings.value("lat", 0.0).toDouble();
    settings.endGroup();

    settings_updated();
}

