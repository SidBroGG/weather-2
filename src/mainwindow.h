#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "weather/weather.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_settingsButton_clicked();
    void settings_updated();
    void weather_updated(const QString &errorString, double temp, const QString &desc);

    void on_updateButton_clicked();

private:
    void saveSettings();
    void loadSettings();

    Ui::MainWindow *ui;

    Weather *_weather;

    QString _cityName;
    double _lon;
    double _lat;
};
#endif // MAINWINDOW_H
