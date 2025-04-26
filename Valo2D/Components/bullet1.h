#ifndef BULLET1_H
#define BULLET1_H

#include "bulletinterface.h"
#include <QPainter>
#include <QPen>
#include <QObject>
#include <QTimer>

class Bullet1 : public BulletInterface
{
public:
    Bullet1();

public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    // BulletInterface interface
public:
    int getBulletId();
    BulletInterface* release(double startPosX, double startPosY, double angle, int gamePlayerId, int gunId);

    // BulletInterface interface



};

#endif // BULLET1_H
