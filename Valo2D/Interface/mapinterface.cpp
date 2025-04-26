#include "mapinterface.h"

MapInterFace::MapInterFace() {
    capturePointItem = new QGraphicsEllipseItem(QRectF(0,0,6,6));
}

QGraphicsScene *MapInterFace::getScene() const
{
    return scene;
}

void MapInterFace::setScene(QGraphicsScene *newScene)
{
    scene = newScene;
}

QGraphicsEllipseItem *MapInterFace::getEyesightItem() const
{
    return eyesightItem;
}

void MapInterFace::setEyesightItem(QGraphicsEllipseItem *newEyesightItem)
{
    eyesightItem = newEyesightItem;
}

void MapInterFace::showCapturePoint(QPointF pos,QColor col)
{
    QBrush brush(col);
    capturePointItem->setBrush(brush);
    capturePointItem->setPos(pos);
    capturePointItem->show();

}

void MapInterFace::hideCapturePoint()
{
   capturePointItem->hide();
}

QGraphicsEllipseItem *MapInterFace::getCapturePointItem() const
{
    return capturePointItem;
}

