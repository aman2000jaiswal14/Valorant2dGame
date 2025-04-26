#ifndef ABILITYINTERFACE_H
#define ABILITYINTERFACE_H
#include <QObject>
class AbilityInterface : public QObject
{
    Q_OBJECT
public:
    AbilityInterface();
    ~AbilityInterface();
    virtual void executeAbility()=0;
    virtual int abilityType()=0;
    virtual QString abilityName()=0;
    virtual QString abilityDesc()=0;



    int getAbilityLeftCount() const;
    void setAbilityLeftCount(int newAbilityLeftCount);

    int getAbilitydefaultCount() const;
    void setAbilitydefaultCount(int newAbilitydefaultCount);

    void decAbilityLeftCount();
    void incAbilityLeftCount();
private:
    int abilityLeftCount = 1;
    int abilitydefaultCount = 1;

};

#endif // ABILITYINTERFACE_H
