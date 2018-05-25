#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "qmlboard.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    qmlRegisterType<QmlBoard>("GameOfLife", 1, 0, "QmlBoard");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));

    return app.exec();
}
