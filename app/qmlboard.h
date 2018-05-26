#pragma once

#include <QQuickPaintedItem>
#include <QPoint>

#include "infiniteboard.h"

class QmlBoard : public QQuickPaintedItem
{
    Q_OBJECT
public:
    QmlBoard(QQuickItem *parent = 0);

    void paint(QPainter *painter);

    Q_INVOKABLE void step();

private:
    virtual void toggleCell(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

    InfiniteBoard board;
    QPoint lastPos;
};
