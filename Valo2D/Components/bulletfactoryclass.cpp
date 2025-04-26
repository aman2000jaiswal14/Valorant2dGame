#include "bulletfactoryclass.h"



BulletInterface *BulletFactoryClass::createBullet(int bulletType)
{
    if(bulletType == 1)
    {
        return new Bullet1;
    }
    else if(bulletType == 2)
    {
        return new Bullet2;
    }
    return nullptr;
}
