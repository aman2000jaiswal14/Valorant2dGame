#ifndef GUN1_H
#define GUN1_H

#include "guninterface.h"

#include <QObject>

class Gun1 : public GunInterface
{
    Q_OBJECT
public:
    Gun1();
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

#endif // GUN1_H
