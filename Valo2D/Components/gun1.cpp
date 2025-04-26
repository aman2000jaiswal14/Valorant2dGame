#include "gun1.h"
#include "bulletfactoryclass.h"
Gun1::Gun1() {

    setReloadTime(2000);
    Gun1::configureGun();
}

int Gun1::getGunId()
{
    return 1;
}

QString Gun1::getName()
{
    return "CLASSIC";
}

QString Gun1::getDesc()
{
    return "Range - 100";
}

BulletInterface *Gun1::fire(double startPosX, double startPosY, double angle, int gamePlayerId)
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

void Gun1::display(QPainter *painter, QRectF boundingRect)
{
    painter->save();
    painter->setPen(QPen(Qt::black,5));
    painter->setBrush(QBrush(Qt::green));
    QPolygonF polyF;
    polyF<<QPointF(boundingRect.width()/2,boundingRect.height()/5);
    polyF<<QPointF(boundingRect.width()/2,0);
    painter->drawPolygon(polyF);
    painter->restore();
}

void Gun1::configureGun()
{
    setMagzineLeft(1);
    setMagzineCap(6);
    setBulletLeft(6);

}

BulletInterface *Gun1::getBulletBehav()
{
    BulletInterface * bullet = BulletFactoryClass::createBullet(1);
    return bullet;
}


