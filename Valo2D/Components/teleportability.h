#ifndef TELEPORTABILITY_H
#define TELEPORTABILITY_H

#include <abilityinterface.h>
#include "datastore.h"
#include <QObject>
#include <QTimer>
#include "middleware.h"
class TeleportAbility : public AbilityInterface
{
    Q_OBJECT
    QTimer *eAbilityTimer = nullptr;
public:
    TeleportAbility();
    ~TeleportAbility();

    void executeAbility();
    int abilityType();

private slots:
    void eAbilityTimerTimeOutSlot();

    // AbilityInterface interface
public:
    QString abilityName();
    QString abilityDesc();
};


#endif // TELEPORTABILITY_H
