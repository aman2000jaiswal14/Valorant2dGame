#ifndef REALPLAYER_H
#define REALPLAYER_H

#include "playerinterface.h"

class RealPlayer : public PlayerInterface
{
public:
    RealPlayer();
    ~RealPlayer();

    void calculateRankXp();
};

#endif // REALPLAYER_H
