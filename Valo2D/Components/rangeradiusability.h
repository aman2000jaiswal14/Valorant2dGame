#ifndef RANGERADIUSABILITY_H
#define RANGERADIUSABILITY_H

#include <abilityinterface.h>
#include "datastore.h"
#include <QObject>
#include <QTimer>
class RangeRadiusAbility : public AbilityInterface
{
    Q_OBJECT
    QTimer *eAbilityTimer = nullptr;
public:
    RangeRadiusAbility();
    ~RangeRadiusAbility();

    void executeAbility();
    int abilityType();

private slots:
    void eAbilityTimerTimeOutSlot();

    // AbilityInterface interface
public:
    QString abilityName();
    QString abilityDesc();
};

#endif // RANGERADIUSABILITY_H
