#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "geocoding.h"

#include <QTimer>
#include <QFont>
#include <QPalette>
#include <QPushButton>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
    , geocoding(new Geocoding(this))
    , timer(new QTimer(this))
{
    ui->setupUi(this);

    _res_cityName = QString();
    _res_lat = 0.0;
    _res_lon = 0.0;

    timer->setInterval(1000);
    timer->setSingleShot(true);

    connect(timer, &QTimer::timeout, this, &SettingsDialog::startGeocoding);

    connect(geocoding, &Geocoding::complete, this, &SettingsDialog::handleGeocodingComplete);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

QString SettingsDialog::res_cityName() const { return _res_cityName; }
double SettingsDialog::res_lon() const { return _res_lon; }
double SettingsDialog::res_lat() const { return _res_lat; }

void SettingsDialog::on_lineEdit_textEdited(const QString &arg1)
{
    if (arg1 == lastQuery) return;

    lastQuery = arg1;

    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    if (okButton) {
        okButton->setEnabled(false);
    }

    timer->stop();
    timer->start();
}

void SettingsDialog::startGeocoding()
{
    QPalette loading_palette;
    loading_palette.setColor(QPalette::WindowText, QColor(Qt::black));

    QFont loading_font(ui->successLabel->font());
    loading_font.setItalic(true);

    ui->successLabel->setText("Loading...");
    ui->successLabel->setPalette(loading_palette);
    ui->successLabel->setFont(loading_font);

    geocoding->start(lastQuery);
}

void SettingsDialog::handleGeocodingComplete(
    const QString &errorString, const QString &cityName, double lon, double lat
)
{
    QFont font(ui->successLabel->font());
    font.setItalic(false);
    ui->successLabel->setFont(font);

    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    if (okButton) {
        okButton->setEnabled(true);
    }

    if (errorString.isEmpty()) {
        ui->successLabel->setText("City found");

        QPalette palette;
        palette.setColor(QPalette::WindowText, QColor(Qt::green));
        ui->successLabel->setPalette(palette);

        _res_cityName = cityName;
        _res_lat = lat;
        _res_lon = lon;
    } else {
        ui->successLabel->setText("City not found");

        QPalette palette;
        palette.setColor(QPalette::WindowText, QColor(Qt::red));
        ui->successLabel->setPalette(palette);

        _res_cityName = QString();
        _res_lat = 0.0;
        _res_lon = 0.0;
    }
}

