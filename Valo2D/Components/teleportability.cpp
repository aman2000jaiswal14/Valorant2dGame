#include "teleportability.h"

#include <QThread>
TeleportAbility::TeleportAbility() {


    eAbilityTimer = new QTimer;
    // eAbilityTimer->setInterval(3000);
    // eAbilityTimer->setSingleShot(true);
    // connect(eAbilityTimer,&QTimer::timeout,this,&TeleportAbility::eAbilityTimerTimeOutSlot);

    setAbilityLeftCount(1);
    setAbilitydefaultCount(1);
}

TeleportAbility::~TeleportAbility()
{

}

void TeleportAbility::executeAbility()
{
    if(DataStore::getInstance().getGamePlayer() && getAbilityLeftCount()>0)
    {
        if(DataStore::getInstance().validCapturePositionFlag)
        {
            STRUCT_PLAYER_POSITION pos;
            pos.xpos = DataStore::getInstance().validCapturePositionDisplay.x() - DataStore::getInstance().getGamePlayer()->boundingRect().width()/2;
            pos.ypos = DataStore::getInstance().validCapturePositionDisplay.y() - DataStore::getInstance().getGamePlayer()->boundingRect().height()/2;
            MiddleWare::getInstance().sendPlayerPositionMsg(pos);
            decAbilityLeftCount();

        }
        else
        {

        }

    }

}

int TeleportAbility::abilityType()
{
    return 3;
}

void TeleportAbility::eAbilityTimerTimeOutSlot()
{
    if(DataStore::getInstance().getGamePlayer())
    {
        DataStore::getInstance().getGamePlayer()->setEyeSightRadius(DataStore::getInstance().getGamePlayer()->getDefaultEyeSightRadius());
        DataStore::getInstance().checkVisibilityCheckToAllPlayer();
    }
}

QString TeleportAbility::abilityName()
{
    return "E Ability";
}

QString TeleportAbility::abilityDesc()
{
    return "Teleport Anywhere";
}
