#include "agentfactoryclass.h"



AgentInterFace *AgentFactoryClass::createAgent(int agentType)
{
    if(agentType == 1 )
    {
        return new Agent1;
    }
    else if(agentType == 2)
    {
        return new Agent2;
    }
    else if(agentType == 3)
    {
        return new Agent3;
    }
    else if(agentType == 4)
    {
        return new Agent4;
    }
    return nullptr;
}
