#include "guninterface.h"


GunInterface::GunInterface() {

    reloadTimer = new QTimer;
    reloadTimer->setInterval(reloadTime);
    connect(reloadTimer,&QTimer::timeout,this,&GunInterface::reloadTimerTimeOutSlot);

}



BulletInterface* GunInterface::fire(double startPosX, double startPosY, double angle, int gamePlayerId)
{
    if(getIsReloading())
    {
        return NULL;
    }
    BulletInterface* bullet = getBulletBehav();
    return bullet->release(startPosX, startPosY, angle, gamePlayerId,getGunId());;
}

int GunInterface::getMagzine() const
{
    return magzine;
}

void GunInterface::setMagzine(int newMagzine)
{
    magzine = newMagzine;
    emit bulletStatusUpdatedSignal();
}

int GunInterface::getMagzineCap() const
{
    return magzineCap;
}

void GunInterface::setMagzineCap(int newMagzineCap)
{
    if(newMagzineCap>=0)
        magzineCap = newMagzineCap;
    emit bulletStatusUpdatedSignal();
}

int GunInterface::getReloadTime() const
{
    return reloadTime;
}

void GunInterface::setReloadTime(int newReloadTime)
{
    reloadTime = newReloadTime;
    reloadTimer->setInterval(newReloadTime);
}

int GunInterface::getBulletLeft() const
{
    return bulletLeft;
}

void GunInterface::setBulletLeft(int newBulletLeft)
{
    bulletLeft = newBulletLeft;
    emit bulletStatusUpdatedSignal();
}

int GunInterface::getMagzineLeft() const
{
    return magzineLeft;
}

void GunInterface::setMagzineLeft(int newMagzineLeft)
{
    magzineLeft = newMagzineLeft;
    emit bulletStatusUpdatedSignal();
}

bool GunInterface::getIsReloading() const
{
    return isReloading;
}

void GunInterface::setIsReloading(bool newIsReloading)
{
    isReloading = newIsReloading;
}

void GunInterface::startReloading()
{
    setIsReloading(true);
    reloadTimer->start();
}


void GunInterface::reloadTimerTimeOutSlot()
{
    if(getMagzineLeft() == 0) return;
    setMagzineLeft(getMagzineLeft()-1);
    setBulletLeft(getMagzineCap());
    setIsReloading(false);
}






