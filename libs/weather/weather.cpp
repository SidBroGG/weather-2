#include "weather.h"

#include <QUrlQuery>

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
