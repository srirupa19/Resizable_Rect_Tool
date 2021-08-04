#include "circleinsquare.h"

CircleInSquare::CircleInSquare(QRectF rect, QGraphicsItem *parent) :
    QGraphicsRectItem(parent)
{
    this->setRect(rect);

    dxLeft = 0;
    dxRight = 0;
    dyTop = 0;
    dyBottom = 0;

    isPressed = false;
    resizeMode = false;
    isMoving = false;

    setFlag(ItemIsMovable);
    color = Qt::black;
    pen.setColor(color);
    pen.setWidth(5);
    setPen(pen);
}


void CircleInSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsRectItem::paint(painter, option, widget);
    painter->drawEllipse(rect());
    painter->setPen(Qt::DashLine);
    painter->drawRect(innerRect());
}


void CircleInSquare::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    dxLeft = 0;
    dxRight = 0;
    dyTop = 0;
    dyBottom = 0;

    isPressed = true;

    int mouseX = event->pos().x();
    int mouseY = event->pos().y();
    QRectF innerR = innerRect();

    int leftX = innerR.topLeft().x();
    int rightX = innerR.topRight().x();
    int topY = innerR.topLeft().y();
    int bottomY = innerR.bottomLeft().y();

    if (mouseX < leftX || mouseX > rightX || mouseY < topY || mouseY > bottomY) {
        resizeMode = true;

        if (mouseX < leftX) {
            dxLeft = mouseX - leftX;
        } else if (mouseX > rightX) {
            dxRight = mouseX - rightX;
        }

        if (mouseY < topY) {
            dyTop = mouseY - topY;
        } else if (mouseY > bottomY) {
            dyBottom = mouseY - bottomY;
        }
    }

    if(!resizeMode) {
        QGraphicsItem::mousePressEvent(event);
    }
}

void CircleInSquare::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    isMoving = true;
    QPointF point = event->pos();

    if (resizeMode && isPressed) {
        resize(point);
    } else {
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void CircleInSquare::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    isPressed = false;
    QPointF point = event->pos();

    if (resizeMode && isMoving) {
        resize(point);
        resizeMode = false;
        isMoving = false;
    } else {
        QGraphicsItem::mouseReleaseEvent(event);
    }
}

bool CircleInSquare::smallestRect(QRectF rect)
{
    if (rect.width() < 50 || rect.height() < 50) {
        return false;
    }
    return true;
}

QRectF CircleInSquare::innerRect() const
{
    int border = 20;
    return rect().adjusted(border, border, -border, -border);
}

void CircleInSquare::resize(QPointF mouse)
{
    bool checkTop = 0;
    bool checkLeft = 0;

    int rightX = innerRect().bottomRight().x();
    int bottomY = innerRect().bottomRight().y();
    int topY = innerRect().topLeft().y();
    int leftX = innerRect().topLeft().x();

    int mouseX = mouse.x();
    int mouseY = mouse.y();

    int height = rect().height();
    int width = rect().width();

    if (dxLeft != 0) {
        checkLeft = true;
        width = width + (leftX - mouseX);
    } else if (dxRight != 0) {
        width = width + (mouseX - rightX);
    }

    if (dyTop != 0) {
        checkTop = true;
        height = height + (topY - mouseY);
    } else if (dyBottom != 0) {
        height = height + (mouseY - bottomY);
    }


    QRectF newRect(rect().topLeft().x(), rect().topLeft().y(), width, height);

    if (newRect != rect() && smallestRect(newRect)) {
        prepareGeometryChange();
        if (checkLeft && checkTop) {
            newRect.translate(mouseX - leftX, mouseY - topY);
        } else if (checkTop) {
            newRect.translate(0, mouseY - topY);
        } else if (checkLeft) {
            newRect.translate(mouseX - leftX, 0);
        }

        setRect(newRect);
    }
}

