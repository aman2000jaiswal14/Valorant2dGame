#ifndef ABILITYFACTORYCLASS_H
#define ABILITYFACTORYCLASS_H

#include "rangeradiusability.h"
#include "fullangleeyeability.h"
#include "teleportability.h"
#include "doublespeedability.h"
class AbilityFactoryClass
{
public:
    static AbilityInterface* createAbility(int abilityType);
};

#endif // ABILITYFACTORYCLASS_H
