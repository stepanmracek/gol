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

    /*typedef std::pair<int, int> Cell;
    typedef std::set<Cell> Cells;
    Cell x {1,3};
    Cells cells({{1,1},{0,1},{1,3},{1,4}});
    Cells cells2({{0,1},{1,3}});

    if (cells.find(x) != cells.end())
        std::cout << "is there" << std::endl;
    else
        std::cout << "not there" << std::endl;

    Cells diff;
    std::set_difference(cells.begin(), cells.end(), cells2.begin(), cells2.end(), std::inserter(diff, diff.end()));
    for (const auto &c : diff) {
        std::cout << c.first << "," << c.second << ", ";
    }
    std::cout << std::endl;*/
}

