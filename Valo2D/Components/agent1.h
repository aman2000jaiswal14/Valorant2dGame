#ifndef AGENT1_H
#define AGENT1_H

#include "agentinterface.h"

class Agent1 : public AgentInterFace
{

public:
    Agent1();
    int getAgentId();
    QString getAgentName();

    ~Agent1();

    // AgentInterFace interface
public:
    void display(QPainter *painter, QRectF boundingRect);
};

#endif // AGENT1_H
