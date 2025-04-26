#ifndef AGENT3_H
#define AGENT3_H

#include "agentinterface.h"
class Agent3: public AgentInterFace
{
public:
    Agent3();
    int getAgentId();
    QString getAgentName();

    ~Agent3();

    // AgentInterFace interface
public:
    void display(QPainter *painter, QRectF boundingRect);
};

#endif // AGENT3_H
