#include "abilityfactoryclass.h"



AbilityInterface *AbilityFactoryClass::createAbility(int abilityType)
{
    if(abilityType == 1)
    {
        return new RangeRadiusAbility;
    }
    else if(abilityType == 2)
    {
        return new FullAngleEyeAbility;
    }
    else if(abilityType == 3)
    {
        return new TeleportAbility;
    }
    else if(abilityType == 4)
    {
        return new DoubleSpeedAbility;
    }
    return nullptr;
}
