#pragma once

#include <QQuickPaintedItem>
#include <QPoint>

#include "iboard.h"

class QmlBoard : public QQuickPaintedItem
{
    Q_OBJECT
public:
    QmlBoard(QQuickItem *parent = 0);

    void paint(QPainter *painter);

public slots:
    int step();
    void random();

private:
    virtual void toggleCell(bool first, QMouseEvent *event);
    virtual void pan(bool first, QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

    QPointF viewTopLeft();
    QPointF viewBottomRight ();

    IBoard::Ptr board;
    int viewZoom;
    QPointF viewCenter;
};
