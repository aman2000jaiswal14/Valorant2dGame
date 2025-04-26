#include "mapfactoryclass.h"


MapInterFace *MapFactoryClass::createMap(int mapId)
{
    if(mapId == 1)
    {
        return new Map1;
    }
    else if(mapId == 2){
        return new Map2;
    }
    return nullptr;
}
