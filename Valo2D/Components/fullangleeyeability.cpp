#include "fullangleeyeability.h"

FullAngleEyeAbility::FullAngleEyeAbility() {

    eAbilityTimer = new QTimer;
    eAbilityTimer->setInterval(3000);
    eAbilityTimer->setSingleShot(true);
    connect(eAbilityTimer,&QTimer::timeout,this,&FullAngleEyeAbility::eAbilityTimerTimeOutSlot);

    setAbilityLeftCount(4);
    setAbilitydefaultCount(4);
}


FullAngleEyeAbility::~FullAngleEyeAbility()
{

}

void FullAngleEyeAbility::executeAbility()
{

    if(DataStore::getInstance().getGamePlayer() && getAbilityLeftCount()>0)
    {

        DataStore::getInstance().getGamePlayer()->setEyeSightAngle(360);
        DataStore::getInstance().checkVisibilityCheckToAllPlayer();
        decAbilityLeftCount();
    }

    eAbilityTimer->start();
}

int FullAngleEyeAbility::abilityType()
{
    return 2;
}

void FullAngleEyeAbility::eAbilityTimerTimeOutSlot()
{
    if(DataStore::getInstance().getGamePlayer())
    {
        DataStore::getInstance().getGamePlayer()->setEyeSightAngle(DataStore::getInstance().getGamePlayer()->getDefaultEyeSightAngle());
        DataStore::getInstance().checkVisibilityCheckToAllPlayer();
    }
}

QString FullAngleEyeAbility::abilityName()
{
    return "E Ability";
}

QString FullAngleEyeAbility::abilityDesc()
{
    return "360 degree View";
}

