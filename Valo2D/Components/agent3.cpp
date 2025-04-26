#include "agent3.h"
#include "abilityfactoryclass.h"
Agent3::Agent3() {
    setEAbility(AbilityFactoryClass::createAbility(3));
}
int Agent3::getAgentId()
{
    return 3;
}

QString Agent3::getAgentName()
{
    return "Agent 3";
}

Agent3::~Agent3()
{

}

void Agent3::display(QPainter *painter, QRectF boundingRect)
{
    painter->save();
    painter->setPen(QPen(Qt::black,1));
    painter->setBrush(QBrush(Qt::blue));
    QRectF boundingRect2(boundingRect.width()/5,boundingRect.height()/5,3*boundingRect.width()/5,3*boundingRect.height()/5);
    painter->drawEllipse(boundingRect2);
    painter->restore();
}
