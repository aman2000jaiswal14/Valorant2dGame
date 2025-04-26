#ifndef GUNFACTORYCLASS_H
#define GUNFACTORYCLASS_H


#include "gun1.h"
#include "gun2.h"

class GunFactoryClass
{
public:
    static GunInterface * createGun(int gunType);
};

#endif // GUNFACTORYCLASS_H
