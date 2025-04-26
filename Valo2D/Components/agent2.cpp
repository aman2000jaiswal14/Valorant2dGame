#include "agent2.h"
#include "abilityfactoryclass.h"
Agent2::Agent2() {
    setEAbility(AbilityFactoryClass::createAbility(2));
}
int Agent2::getAgentId()
{
    return 2;
}

QString Agent2::getAgentName()
{
    return "Agent 2";
}

Agent2::~Agent2()
{

}

void Agent2::display(QPainter *painter, QRectF boundingRect)
{
    painter->save();
    painter->setPen(QPen(Qt::black,1));
    painter->setBrush(QBrush(Qt::red));
    QRectF boundingRect2(boundingRect.width()/5,boundingRect.height()/5,3*boundingRect.width()/5,3*boundingRect.height()/5);
    painter->drawEllipse(boundingRect2);
    painter->restore();
}
