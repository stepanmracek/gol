#include "qmlboard.h"

#include <iostream>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTime>

#include "infiniteboard.h"
#include "infiniteboard2.h"
#include "boundedboard.h"

QmlBoard::QmlBoard(QQuickItem *parent):
    QQuickPaintedItem(parent),
    viewZoom(20),
    viewCenter(10.5, 10.5)
{
    //board.reset(new InfiniteBoard({2, 3}, {3}));
    //board.reset(new InfiniteBoard2({2, 3}, {3}));
    board.reset(new BoundedBoard(250, 250, {2, 3}, {3}));
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
}

QPointF QmlBoard::viewTopLeft() {
    auto br = boundingRect();
    return QPointF(viewCenter.x() - br.width() / viewZoom / 2, viewCenter.y() - br.height() / viewZoom / 2);
}

QPointF QmlBoard::viewBottomRight() {
    auto br = boundingRect();
    return QPointF(viewCenter.x() + br.width() / viewZoom / 2, viewCenter.y() + br.height() / viewZoom / 2);
}

void QmlBoard::paint(QPainter *painter) {
    QPointF topLeft = viewTopLeft();
    QPointF bottomRight = viewBottomRight();
    painter->setPen(Qt::black);
    IBoard::Cells cells = board->getCellsInArea(topLeft.x(), topLeft.y(),
                                               bottomRight.x() - topLeft.x(),
                                               bottomRight.y() - topLeft.y());
    for (const IBoard::Cell & cell : cells) {
        painter->fillRect(QRectF((cell.first - topLeft.x()) * viewZoom,
                                 (cell.second - topLeft.y()) * viewZoom,
                                 viewZoom, viewZoom), Qt::SolidPattern);
    }
}

int QmlBoard::step() {
    auto now = QTime::currentTime();
    board->step();
    int elapsed = now.elapsed();
    update();
    return elapsed;
}

void QmlBoard::random() {
    auto tl = viewTopLeft();
    auto br = viewBottomRight();
    QRectF area(tl, br);
    int c = area.width() * area.height() * 0.1;
    for (int i = 0; i < c; i++) {
        int x = (rand() % (int)(br.x() - tl.x())) + tl.x();
        int y = (rand() % (int)(br.y() - tl.y())) + tl.y();
        board->setValue(x, y, !board->getValue(x, y));
    }
    update();
}

void QmlBoard::mousePressEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        toggleCell(true, event);
    }
    if (event->buttons() & Qt::RightButton) {
        pan(true, event);
    }
}

void QmlBoard::mouseReleaseEvent(QMouseEvent *event) {

}

void QmlBoard::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        toggleCell(false, event);
    }
    if (event->buttons() & Qt::RightButton) {
        pan(false, event);
    }
}

void QmlBoard::toggleCell(bool first, QMouseEvent *event) {
    auto topLeft = viewTopLeft();
    int x = event->pos().x() / viewZoom + topLeft.x();
    int y = event->pos().y() / viewZoom + topLeft.y();
    QPoint newPos(x, y);
    static QPoint lastPos(INT_MAX, INT_MAX);
    static int drawCellValue = 1;
    if (first) {
        drawCellValue = !board->getValue(x, y);
    }
    if (lastPos != newPos) {
        lastPos = newPos;
        board->setValue(x, y, drawCellValue);
        update();
    }
}

void QmlBoard::pan(bool first, QMouseEvent *event) {
    static QPoint panStart;
    static QPointF originalViewCenter;
    if (first) {
        panStart = event->pos();
        originalViewCenter = viewCenter;
    } else {
        QPoint delta = event->pos() - panStart;
        viewCenter = originalViewCenter - delta/viewZoom;
        update();
    }
}

void QmlBoard::wheelEvent(QWheelEvent *event) {
    viewZoom += event->delta() > 0 ? 1 : -1;
    if (viewZoom < 1) viewZoom = 1;
    std::cout << viewZoom << std::endl;
    update();
}
