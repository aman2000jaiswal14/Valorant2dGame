#ifndef BULLET2_H
#define BULLET2_H

#include "bulletinterface.h"
#include <QPainter>
#include <QPen>
#include <QObject>
#include <QTimer>

class Bullet2 : public BulletInterface
{
public:
    Bullet2();
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    // BulletInterface interface
public:
    int getBulletId();
    BulletInterface* release(double startPosX, double startPosY, double angle, int gamePlayerId, int gunId);
};

#endif // BULLET2_H
