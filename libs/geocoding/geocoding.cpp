#include "geocoding.h"

#include <QUrlQuery>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>

Geocoding::Geocoding(QObject *parent) : QObject(parent) {
    connect(&_manager, &QNetworkAccessManager::finished, this, &Geocoding::onReply);
}

void Geocoding::start(const QString &location) {
    QUrl url("https://photon.komoot.io/api");

    QUrlQuery query;
    query.addQueryItem("q", location);
    query.addQueryItem("limit", "1");
    query.addQueryItem("osm_tag", "place:city");
    query.addQueryItem("osm_tag", "place:town");

    url.setQuery(query);

    _manager.get(QNetworkRequest(url));
}

void Geocoding::onReply(QNetworkReply *reply) {
    connect(reply, &QNetworkReply::finished, reply, &QNetworkReply::deleteLater);

    if (reply->error() != QNetworkReply::NoError) {
        emit complete(reply->errorString(), 0.0, 0.0);
        return;
    }

    QByteArray response = reply->readAll();

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response, &parseError);

    if (parseError.error != QJsonParseError::NoError || !jsonDoc.isObject()) {
        emit complete("Parsing error", 0.0, 0.0);
        return;
    }

    QJsonObject root = jsonDoc.object();
    QJsonArray features = root["features"].toArray();

    if (features.isEmpty()) {
        emit complete("Features is empty", 0.0, 0.0);
        return;
    }

    QJsonObject firstFeature = features.first().toObject();
    QJsonObject geometry = firstFeature["geometry"].toObject();
    QJsonArray coords = geometry["coordinates"].toArray();

    if (coords.size() < 2) {
        emit complete("No coords", 0.0, 0.0);
        return;
    }

    double lon = coords.at(0).toDouble();
    double lat = coords.at(1).toDouble();

    emit complete(QString(), lon, lat);
}



