#include "gun2.h"
#include "bulletfactoryclass.h"
Gun2::Gun2() {
    setReloadTime(5000);
    configureGun();
}

int Gun2::getGunId()
{
    return 2;
}

QString Gun2::getName()
{
    return "SNIPER";
}

QString Gun2::getDesc()
{
    return "RANGE - 500";
}

BulletInterface *Gun2::fire(double startPosX, double startPosY, double angle, int gamePlayerId)
{
    if(getBulletLeft() == 0)
    {
        if(getMagzineLeft() == 0)
        {
            return NULL;
        }
        else
        {
            if(!getIsReloading())
                startReloading();

        }
    }
    else
    {
        setBulletLeft(getBulletLeft()-1);
    }
    // qDebug()<<"bullet left : "<<getBulletLeft()<<"mag left : "<<getMagzineLeft();
    return GunInterface::fire(startPosX,startPosY,angle,gamePlayerId);
}

void Gun2::display(QPainter *painter, QRectF boundingRect)
{
    painter->save();
    painter->setPen(QPen(Qt::red,5));
    painter->setBrush(QBrush(Qt::red));
    QPolygonF polyF;
    polyF<<QPointF(boundingRect.width()/2,boundingRect.height()/5);
    polyF<<QPointF(boundingRect.width()/2,0);
    painter->drawPolygon(polyF);
    painter->restore();
}

void Gun2::configureGun()
{
    setMagzineLeft(5);
    setMagzineCap(1);
    setBulletLeft(1);

}

BulletInterface *Gun2::getBulletBehav()
{
    BulletInterface * bullet = BulletFactoryClass::createBullet(2);
    return bullet;
}

