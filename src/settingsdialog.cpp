#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "geocoding.h"

#include <QTimer>
#include <QFont>
#include <QPalette>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
    , geocoding(new Geocoding(this))
    , timer(new QTimer(this))
{
    ui->setupUi(this);
    connect(timer, &QTimer::timeout, this, [this] { to_update = true; });
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_lineEdit_textEdited(const QString &arg1)
{
    if (!to_update) return;

    to_update = false;

    QPalette loading_palette;
    loading_palette.setColor(QPalette::WindowText, QColor(Qt::black));

    QFont loading_font(ui->successLabel->font());
    loading_font.setItalic(true);

    ui->successLabel->setText("Loading...");
    ui->successLabel->setPalette(loading_palette);
    ui->successLabel->setFont(loading_font);

    connect(geocoding, &Geocoding::complete, this, [this] (const QString &errorString, double lon, double lat) {
        QFont font(ui->successLabel->font());
        font.setItalic(false);
        ui->successLabel->setFont(font);

        if (errorString.isEmpty()) {
            ui->successLabel->setText("City found");

            QPalette palette;
            palette.setColor(QPalette::WindowText, QColor(Qt::green));
            ui->successLabel->setPalette(palette);
        } else {
            ui->successLabel->setText("City not found");

            QPalette palette;
            palette.setColor(QPalette::WindowText, QColor(Qt::red));
            ui->successLabel->setPalette(palette);
        }
    });

    geocoding->start(arg1);
    timer->start(1000);
}

