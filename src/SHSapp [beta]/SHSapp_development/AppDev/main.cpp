#include <QHostAddress>

#define SHS_SET_DEFAULT_BROADCAST_IP QHostAddress::Broadcast //"192.168.1.174" //QHostAddress::Broadcast

#include <QGuiApplication>
#include <QQmlApplicationEngine>


#include <shs_settings_private.h>
#include "SwitchHandler.h"
#include "shs.h"
#include "timer.h"
#include <shs_SimpleFixed.h>

#include <QtQuickControls2>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);




    qmlRegisterType<SHS>("SHSengine", 1, 0, "SHSengine");
    qmlRegisterType<Timer>("shs_timer", 1, 0, "Timer");


    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);



    return app.exec();
}
