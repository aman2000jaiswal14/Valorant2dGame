#include "gunfactoryclass.h"


GunInterface *GunFactoryClass::createGun(int gunType)
{
    if(gunType == 1)
    {
        return new Gun1;
    }
    else if(gunType == 2)
    {
        return new Gun2;
    }
    return nullptr;
}
