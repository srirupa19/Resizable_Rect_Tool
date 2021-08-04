#ifndef CIRCLEINSQUARE_H
#define CIRCLEINSQUARE_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneHoverEvent>
#include<QHoverEvent>
#include<QCursor>

#include <QApplication>
#include <QColor>
#include <QPen>


class CircleInSquare : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    CircleInSquare(QRectF rect, QGraphicsItem *parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QColor color;
    QPen pen;
    QBrush brush;

private:
    qreal dxLeft;
    qreal dxRight;
    qreal dyTop;
    qreal dyBottom;
    bool isPressed;    
    bool resizeMode;
    bool isMoving;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    bool smallestRect(QRectF rect);
    QRectF innerRect() const;
    void resize(QPointF mouse);

};

#endif // CIRCLEINSQUARE_H
