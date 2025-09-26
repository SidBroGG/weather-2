#include "geocoding/geocoding.h"

#include <QtTest/QtTest>
#include <QList>
#include <QVariant>

class TestGeocoding : public QObject {
    Q_OBJECT

private slots:
    void minskTest();
};

void TestGeocoding::minskTest() {
    Geocoding geocoding;

    QSignalSpy spy(&geocoding, &Geocoding::complete);

    geocoding.start("Belarus, Minsk");

    QVERIFY(spy.wait(1000));

    QList<QVariant> args = spy.takeFirst();

    QString error = args.at(0).toString();
    double lon = args.at(1).toDouble();
    double lat = args.at(2).toDouble();

    QVERIFY2(error.isEmpty(), error.toUtf8().data());
}

QTEST_MAIN(TestGeocoding)
#include "test_geocoding.moc"
