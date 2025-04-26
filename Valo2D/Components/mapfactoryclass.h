#ifndef MAPFACTORYCLASS_H
#define MAPFACTORYCLASS_H

#include "map1.h"
#include "map2.h"
class MapFactoryClass
{
public:
    static MapInterFace *createMap(int mapId);

};

#endif // MAPFACTORYCLASS_H
