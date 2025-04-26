#include "doublespeedability.h"


DoubleSpeedAbility::DoubleSpeedAbility() {

    eAbilityTimer = new QTimer;
    eAbilityTimer->setInterval(3000);
    eAbilityTimer->setSingleShot(true);
    connect(eAbilityTimer,&QTimer::timeout,this,&DoubleSpeedAbility::eAbilityTimerTimeOutSlot);

    setAbilityLeftCount(2);
    setAbilitydefaultCount(2);
}

DoubleSpeedAbility::~DoubleSpeedAbility()
{

}

void DoubleSpeedAbility::executeAbility()
{

    if(DataStore::getInstance().getGamePlayer() && getAbilityLeftCount()>0)
    {
        DataStore::getInstance().getGamePlayer()->setSpeed(4*DataStore::getInstance().getGamePlayer()->getDefaultSpeed());
        this->decAbilityLeftCount();
    }

    eAbilityTimer->start();
}

int DoubleSpeedAbility::abilityType()
{
    return 4;
}

void DoubleSpeedAbility::eAbilityTimerTimeOutSlot()
{
    if(DataStore::getInstance().getGamePlayer())
    {
        DataStore::getInstance().getGamePlayer()->setSpeed(DataStore::getInstance().getGamePlayer()->getDefaultSpeed());

    }
}

QString DoubleSpeedAbility::abilityName()
{
    return "E Ability";
}

QString DoubleSpeedAbility::abilityDesc()
{
    return "4 Times Speed";
}
