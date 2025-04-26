#include "specialutils.h"

SpecialUtils &SpecialUtils::getInstance()
{
    static SpecialUtils obj;
    return obj;
}

SpecialUtils::SpecialUtils() {}

int SpecialUtils::idGenerator()
{
    for(int i=0;i<1000;i++)
    {
        if(!ids[i])
        {
            ids[i] = true;
            return i;
        }
    }
    return -1;
}

void SpecialUtils::freeId(int id)
{
    ids[id] = false;
}
