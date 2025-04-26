#include "agentinterface.h"



AbilityInterface *AgentInterFace::getEAbility() const
{
    return eAbility;
}

void AgentInterFace::setEAbility(AbilityInterface *newEAbility)
{
    eAbility = newEAbility;
}
