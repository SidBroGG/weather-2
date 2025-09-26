#include "weather.h"

#include <QUrlQuery>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QMap>

Weather::Weather(QObject *parent)
    : QObject(parent)
{
    connect(&_manager, &QNetworkAccessManager::finished, this, &Weather::onReply);
}

void Weather::start(double lon, double lat)
{
    QUrl url("https://api.open-meteo.com/v1/forecast");

    QUrlQuery query;
    query.addQueryItem("latitude", QString::number(lat));
    query.addQueryItem("longitude", QString::number(lon));
    query.addQueryItem("current", "temperature_2m,weather_code");

    url.setQuery(query);

    _manager.get(QNetworkRequest(url));
}

void Weather::onReply(QNetworkReply *reply)
{
    connect(reply, &QNetworkReply::finished, reply, &QNetworkReply::deleteLater);

    if (reply->error() != QNetworkReply::NoError) {
        emit complete(reply->errorString(), 0.0, QString());
        return;
    }

    QByteArray response = reply->readAll();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(response, &parseError);

    if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
        emit complete("Parsing error", 0.0, QString());
        return;
    }

    QJsonObject rootObj = doc.object();
    QJsonObject current = rootObj["current"].toObject();

    if (!current.contains("temperature_2m") || !current.contains("weather_code")) {
        emit complete("Json error", 0.0, QString());
        return;
    }

    double temp = current["temperature_2m"].isDouble();

    int weather_code = current["weather_code"].toInt();
    QString desc = weatherDesc(weather_code);

    emit complete(QString(), temp, desc);
}

QString Weather::weatherDesc(int code)
{
    static const QMap<int, QString> weatherCodes = {
        {0, "Clear sky"},
        {1, "Mainly clear"},
        {2, "Partly cloudy"},
        {3, "Overcast"},
        {45, "Fog"},
        {48, "Depositing rime fog"},
        {51, "Drizzle: Light"},
        {53, "Drizzle: Moderate"},
        {55, "Drizzle: Dense intensity"},
        {56, "Freezing Drizzle: Light"},
        {57, "Freezing Drizzle: Dense intensity"},
        {61, "Rain: Slight"},
        {63, "Rain: Moderate"},
        {65, "Rain: Heavy intensity"},
        {66, "Freezing Rain: Light"},
        {67, "Freezing Rain: Heavy"},
        {71, "Snow fall: Slight"},
        {73, "Snow fall: Moderate"},
        {75, "Snow fall: Heavy"},
        {77, "Snow grains"},
        {80, "Rain showers: Slight"},
        {81, "Rain showers: Moderate"},
        {82, "Rain showers: Violent"},
        {85, "Snow showers: Slight"},
        {86, "Snow showers: Heavy"},
        {95, "Thunderstorm: Slight or moderate"},
        {96, "Thunderstorm with slight hail"},
        {99, "Thunderstorm with heavy hail"}
    };

    return weatherCodes.value(code, "Unknown weather code");
}
