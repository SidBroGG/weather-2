#ifndef WEATHER_H
#define WEATHER_H

#include <QObject>
#include <QNetworkAccessManager>

class Weather : public QObject
{
    Q_OBJECT

public:
    explicit Weather(QObject *parent = nullptr);

public slots:
    void start(double lon, double lat);

private slots:
    void onReply(QNetworkReply *reply);

signals:
    void complete(double temp, const QString &desc);

private:
    QNetworkAccessManager _manager;
};

#endif
