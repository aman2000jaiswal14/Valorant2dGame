#ifndef AGENTFACTORYCLASS_H
#define AGENTFACTORYCLASS_H

#include "agent1.h"
#include "agent2.h"
#include "agent3.h"
#include "agent4.h"
class AgentFactoryClass
{
public:
    static AgentInterFace *createAgent(int agentType);
};

#endif // AGENTFACTORYCLASS_H
