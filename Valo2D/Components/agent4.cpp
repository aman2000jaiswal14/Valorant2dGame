#include "agent4.h"
#include "abilityfactoryclass.h"

Agent4::Agent4() {

    setEAbility(AbilityFactoryClass::createAbility(4));
}

int Agent4::getAgentId()
{
    return 4;
}

QString Agent4::getAgentName()
{
    return "Agent 4";
}

Agent4::~Agent4()
{

}

void Agent4::display(QPainter *painter, QRectF boundingRect)
{
    painter->save();
    painter->setPen(QPen(Qt::black,1));
    painter->setBrush(QBrush(Qt::black));
    QPolygonF polyF;
    polyF<<QPointF(boundingRect.width()/5,4*boundingRect.height()/5);
    polyF<<QPointF(boundingRect.width()/2,boundingRect.height()/5);
    polyF<<QPointF(4*boundingRect.width()/5,4*boundingRect.height()/5);
    painter->drawPolygon(polyF);
    painter->restore();
}
