#include "rangeradiusability.h"
#include <QThread>
RangeRadiusAbility::RangeRadiusAbility() {


    eAbilityTimer = new QTimer;
    eAbilityTimer->setInterval(3000);
    eAbilityTimer->setSingleShot(true);
    connect(eAbilityTimer,&QTimer::timeout,this,&RangeRadiusAbility::eAbilityTimerTimeOutSlot);

    setAbilityLeftCount(2);
    setAbilitydefaultCount(2);
}

RangeRadiusAbility::~RangeRadiusAbility()
{

}

void RangeRadiusAbility::executeAbility()
{

    if(DataStore::getInstance().getGamePlayer() && getAbilityLeftCount()>0)
    {
        DataStore::getInstance().getGamePlayer()->setEyeSightRadius(2*DataStore::getInstance().getGamePlayer()->getDefaultEyeSightRadius());
        DataStore::getInstance().checkVisibilityCheckToAllPlayer();
        decAbilityLeftCount();
    }

    eAbilityTimer->start();
}

int RangeRadiusAbility::abilityType()
{
    return 1;
}

void RangeRadiusAbility::eAbilityTimerTimeOutSlot()
{
    if(DataStore::getInstance().getGamePlayer())
    {
        DataStore::getInstance().getGamePlayer()->setEyeSightRadius(DataStore::getInstance().getGamePlayer()->getDefaultEyeSightRadius());
        DataStore::getInstance().checkVisibilityCheckToAllPlayer();
    }
}

QString RangeRadiusAbility::abilityName()
{
    return "E Ability";
}

QString RangeRadiusAbility::abilityDesc()
{
    return "Double Radius Eye";
}
