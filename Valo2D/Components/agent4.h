#ifndef AGENT4_H
#define AGENT4_H

#include "agentinterface.h"

class Agent4 : public AgentInterFace
{

public:
    Agent4();
    int getAgentId();
    QString getAgentName();

    ~Agent4();

    // AgentInterFace interface
public:
    void display(QPainter *painter, QRectF boundingRect);
};

#endif // AGENT4_H
