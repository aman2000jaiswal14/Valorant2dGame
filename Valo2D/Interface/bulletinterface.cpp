#include "bulletinterface.h"
#include <QThread>
#include <QtMath>
BulletInterface::BulletInterface() {

    bulletTimer = new QTimer(this);
    connect(bulletTimer,&QTimer::timeout,this,&BulletInterface::bulletTimerTimeOutSlot);
}



double BulletInterface::getPosX() const
{
    return posX;
}

void BulletInterface::setPosX(double newPosX)
{
    posX = newPosX;
    tempX = newPosX;
    this->setX(posX);
}

double BulletInterface::getPosY() const
{
    return posY;
}

void BulletInterface::setPosY(double newPosY)
{
    posY = newPosY;
    tempY = newPosY;
    this->setY(posY);
}

double BulletInterface::getStartPosX() const
{
    return startPosX;
}

void BulletInterface::setStartPosX(double newStartPosX)
{
    startPosX = newStartPosX;
    this->setPosX(newStartPosX);
}

double BulletInterface::getStartPoxY() const
{
    return startPoxY;
}

void BulletInterface::setStartPoxY(double newStartPoxY)
{
    startPoxY = newStartPoxY;
    this->setPosY(startPoxY);
}

double BulletInterface::getRange() const
{
    return range;
}

int BulletInterface::getGamePlayerId() const
{
    return gamePlayerId;
}

void BulletInterface::setGamePlayerId(int newGamePlayerId)
{
    gamePlayerId = newGamePlayerId;
}

int BulletInterface::getGunId() const
{
    return gunId;
}

void BulletInterface::setGunId(int newGunId)
{
    gunId = newGunId;
}

double BulletInterface::getSpeed() const
{
    return speed;
}



double BulletInterface::getAngle() const
{
    return angle;
}

void BulletInterface::setAngle(double newAngle)
{
    angle = newAngle;
}

void BulletInterface::startBulletTimer()
{
    emit bulletUpdatedSignal(this,getPosX(),getPosY());
    bulletTimer->start(5000/getSpeed());
}

void BulletInterface::stopBulletTimer()
{

    bulletTimer->stop();
    emit bulletDestroyedSignal(this);
}

void BulletInterface::setRange(double newRange)
{
    range = newRange;
}

void BulletInterface::setSpeed(double newSpeed)
{
    speed = newSpeed;
}

bool BulletInterface::setBulletTimer(int val)
{
    bulletTimer->setInterval(val);
}

bool BulletInterface::getVisibleToPlayer() const
{
    return visibleToPlayer;
}

void BulletInterface::setVisibleToPlayer(bool newVisibleToPlayer)
{
    visibleToPlayer = newVisibleToPlayer;
    if(visibleToPlayer)
    {
        this->setOpacity(100);

    }
    else
    {
        this->setOpacity(0);
        // this->setFlag(QGraphicsItem::ItemHasNoContents);
    }

}

int BulletInterface::getDamage() const
{
    return damage;
}

void BulletInterface::setDamage(int newDamage)
{
    damage = newDamage;
}


int BulletInterface::getUniqueNo() const
{
    return uniqueNo;
}

void BulletInterface::setUniqueNo(int newUniqueNo)
{
    uniqueNo = newUniqueNo;
}

void BulletInterface::bulletTimerTimeOutSlot()
{
    double newX = tempX + this->getSpeed()*qCos(qDegreesToRadians(getAngle()));
    double newY = tempY + this->getSpeed()*qSin(qDegreesToRadians(getAngle()));

    double sqDistance = qPow(newX - this->getStartPosX(),2) + qPow(newY - this->getStartPoxY(),2);

    // qDebug()<<"newX : "<<newX<<" newY : "<<newY<<" sqDistance : "<<sqDistance;
    if(sqDistance <=  qPow(this->getRange(),2))
    {
        // this->setPosX(newX);
        // this->setPosY(newY);
        tempX = newX;
        tempY = newY;
        // qDebug()<<newX<<" - - -- - -  "<<newY<<"----";
        emit bulletUpdatedSignal(this,newX,newY);
    }
    else{
        this->stopBulletTimer();
    }
}



