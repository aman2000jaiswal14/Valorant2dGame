#ifndef FULLANGLEEYEABILITY_H
#define FULLANGLEEYEABILITY_H


#include <abilityinterface.h>
#include "datastore.h"
#include <QObject>
#include <QTimer>

class FullAngleEyeAbility : public AbilityInterface
{
    Q_OBJECT
    QTimer *eAbilityTimer = nullptr;
public:
    FullAngleEyeAbility();

    ~FullAngleEyeAbility();


    void executeAbility();
    int abilityType();

private slots:
    void eAbilityTimerTimeOutSlot();


    // AbilityInterface interface
public:
    QString abilityName();
    QString abilityDesc();
};

#endif // FULLANGLEEYEABILITY_H
