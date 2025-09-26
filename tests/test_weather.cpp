#include "weather/weather.h"

#include <QTest>
#include <QSignalSpy>

class TestWeather : public QObject {
    Q_OBJECT

private slots:
    void normalTest();
};

void TestWeather::normalTest() {
    Weather weather;

    QSignalSpy spy(&weather, &Weather::complete);

    weather.start(27.5667, 53.9);

    QVERIFY(spy.wait(1000));

    QList<QVariant> args = spy.takeFirst();

    QString error = args.at(0).toString();
    double temp = args.at(1).toDouble();
    QString desc = args.at(2).toString();

    QVERIFY2(error.isEmpty(), error.toUtf8().data());
}


QTEST_MAIN(TestWeather)
#include "test_weather.moc"
