#ifndef GUN2_H
#define GUN2_H

#include <QObject>
#include "guninterface.h"
class Gun2: public GunInterface
{
    Q_OBJECT
public:
    Gun2();
    int getGunId();
    QString getName();
    QString getDesc();
    BulletInterface* fire(double startPosX, double startPosY, double angle, int gamePlayerId);
    // GunInterface interface
public:
    void display(QPainter *painter, QRectF boundingRect);
    void configureGun();

    // GunInterface interface
public:
    BulletInterface *getBulletBehav();
};

#endif // GUN2_H
