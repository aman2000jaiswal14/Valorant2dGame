#ifndef AGENT2_H
#define AGENT2_H
#include "agentinterface.h"
class Agent2: public AgentInterFace
{
public:
    Agent2();
    int getAgentId();
    QString getAgentName();

    ~Agent2();

    // AgentInterFace interface
public:
    void display(QPainter *painter, QRectF boundingRect);
};

#endif // AGENT2_H
