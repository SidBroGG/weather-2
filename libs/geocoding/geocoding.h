#ifndef GEOCODING_H
#define GEOCODING_H

#include <QObject>
#include <QNetworkAccessManager>

class Geocoding : public QObject {
    Q_OBJECT

private:
    QNetworkAccessManager _manager;

public:
    explicit Geocoding(QObject *parent = nullptr);

public slots:
    void start(const QString &location);

private slots:
    void onReply(QNetworkReply *reply);

signals:
    void complete(const QString &errorString, const QString &cityName, double lon, double lat);
};

#endif
