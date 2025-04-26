#include "agent1.h"

#include "abilityfactoryclass.h"
Agent1::Agent1() {

    setEAbility(AbilityFactoryClass::createAbility(1));
}

int Agent1::getAgentId()
{
    return 1;
}

QString Agent1::getAgentName()
{
    return "Agent 1";
}

Agent1::~Agent1()
{

}

void Agent1::display(QPainter *painter, QRectF boundingRect)
{
    painter->save();
    painter->setPen(QPen(Qt::black,1));
    painter->setBrush(QBrush(Qt::green));
    QPolygonF polyF;
    polyF<<QPointF(boundingRect.width()/5,4*boundingRect.height()/5);
    polyF<<QPointF(boundingRect.width()/2,boundingRect.height()/5);
    polyF<<QPointF(4*boundingRect.width()/5,4*boundingRect.height()/5);
    painter->drawPolygon(polyF);
    painter->restore();
}
