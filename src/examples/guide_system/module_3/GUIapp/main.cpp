#include <QGuiApplication>
#include <QQmlApplicationEngine>


#include <shs_settings_private.h>
#include "shs_Engine.h"
#include <shs_SimpleFixed.h>

#include <QtQuickControls2>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);



    qmlRegisterType<Engine>("SHSengine", 1, 0, "SHSengine");


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
