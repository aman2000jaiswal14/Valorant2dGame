#ifndef BULLETFACTORYCLASS_H
#define BULLETFACTORYCLASS_H

#include "bullet1.h"
#include "bullet2.h"
class BulletFactoryClass
{
public:
    static BulletInterface *createBullet(int bulletType);
};

#endif // BULLETFACTORYCLASS_H
