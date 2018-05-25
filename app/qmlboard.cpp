#include "qmlboard.h"

#include <iostream>
#include <QPainter>
#include <QMouseEvent>
#include <QHoverEvent>

QmlBoard::QmlBoard(QQuickItem *parent) : QQuickPaintedItem(parent), board(50, 50, {2,3}, {3}), lastPos(INT_MAX, INT_MAX) {
    setAcceptedMouseButtons(Qt::LeftButton);

    /*for (int i = 0; i < board.getWidth() * board.getHeight() * 0.2; i++) {
        board.random();
    }*/
}

void QmlBoard::paint(QPainter *painter) {
    int boardWidth = board.getWidth();
    int boardHeight = board.getHeight();
    painter->setPen(Qt::black);
    qreal cellWidth = boundingRect().width() / boardWidth;
    qreal cellHeight = boundingRect().height() / boardHeight;
    for (int y = 0; y < boardWidth; y++) {
        for (int x = 0; x < boardHeight; x++) {
            if (board.getValue(x, y)) {
                painter->fillRect(QRectF(x * cellWidth, y * cellHeight, cellWidth, cellHeight), Qt::SolidPattern);
            }
        }
    }
}

void QmlBoard::step() {
    board.step();
    update();
}


void QmlBoard::mousePressEvent(QMouseEvent *event) {
    std::cout << "press " << event->pos().x() << " " << event->pos().y() << std::endl;
    toggleCell(event);
}

void QmlBoard::mouseReleaseEvent(QMouseEvent *event) {
    std::cout << "release " << event->pos().x() << " " << event->pos().y() << std::endl;
    lastPos = QPoint(INT_MAX, INT_MAX);
}

void QmlBoard::mouseMoveEvent(QMouseEvent *event) {
    std::cout << "move " << event->pos().x() << " " << event->pos().y() << std::endl;
    toggleCell(event);
}

void QmlBoard::toggleCell(QMouseEvent *event) {
    int boardWidth = board.getWidth();
    int boardHeight = board.getHeight();
    qreal cellWidth = boundingRect().width() / boardWidth;
    qreal cellHeight = boundingRect().height() / boardHeight;
    int x = event->pos().x() / cellWidth;
    int y = event->pos().y() / cellHeight;
    QPoint newPos(x, y);
    if (lastPos != newPos) {
        lastPos = newPos;
        if (x >= 0 && x < boardWidth && y >= 0 && y < boardHeight) {
            board.setValue(x, y, !board.getValue(x, y));
            update();
        }
    }
}
