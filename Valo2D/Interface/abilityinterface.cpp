#include "abilityinterface.h"

AbilityInterface::AbilityInterface() {}

AbilityInterface::~AbilityInterface()
{

}

int AbilityInterface::getAbilityLeftCount() const
{
    return abilityLeftCount;
}

void AbilityInterface::setAbilityLeftCount(int newAbilityLeftCount)
{
    abilityLeftCount = newAbilityLeftCount;
}

int AbilityInterface::getAbilitydefaultCount() const
{
    return abilitydefaultCount;
}

void AbilityInterface::setAbilitydefaultCount(int newAbilitydefaultCount)
{
    abilitydefaultCount = newAbilitydefaultCount;
}

void AbilityInterface::decAbilityLeftCount()
{
    setAbilityLeftCount(qMax(abilityLeftCount-1,0));
}

void AbilityInterface::incAbilityLeftCount()
{
    setAbilityLeftCount(qMin(abilityLeftCount+1,abilitydefaultCount));
}
