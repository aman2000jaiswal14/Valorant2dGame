#ifndef AGENTINTERFACE_H
#define AGENTINTERFACE_H
#include <QString>
#include <QRectF>
#include <QPainter>
#include "abilityinterface.h"
class AgentInterFace
{
public:
    AgentInterFace(){}

    virtual ~AgentInterFace(){}
    virtual int getAgentId() = 0;
    virtual QString getAgentName() = 0;
    virtual void display(QPainter * painter,QRectF boundingRect) = 0;


    AbilityInterface *getEAbility() const;
    void setEAbility(AbilityInterface *newEAbility);

private:
    AbilityInterface *eAbility = nullptr;



};

#endif // AGENTINTERFACE_H
