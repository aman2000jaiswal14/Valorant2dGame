#ifndef DOUBLESPEEDABILITY_H
#define DOUBLESPEEDABILITY_H



#include <abilityinterface.h>
#include "datastore.h"
#include <QObject>
#include <QTimer>
class DoubleSpeedAbility : public AbilityInterface
{
    Q_OBJECT
    QTimer *eAbilityTimer = nullptr;
public:
    DoubleSpeedAbility();
    ~DoubleSpeedAbility();

    void executeAbility();
    int abilityType();

private slots:
    void eAbilityTimerTimeOutSlot();

    // AbilityInterface interface
public:
    QString abilityName();
    QString abilityDesc();
};


#endif // DOUBLESPEEDABILITY_H
