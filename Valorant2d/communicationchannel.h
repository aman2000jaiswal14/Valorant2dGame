#ifndef COMMUNICATIONCHANNEL_H
#define COMMUNICATIONCHANNEL_H
#include "structures.h"
#include "MessageId.h"

class WebSocketClient;
class structures;
class CommunicationChannel
{
public:
    static CommunicationChannel& instance()
    {
        static CommunicationChannel instance;
        return instance;
    }
    void updatePlayerPosition(STRUCT_PLAYER_POSITION_INFO pos_info);

private:
    WebSocketClient *webSocketClient;
    // Private constructor to prevent instantiation
    CommunicationChannel();

    // Delete copy constructor and assignment operator to prevent copying
    CommunicationChannel(const CommunicationChannel&) = delete;
    CommunicationChannel& operator=(const CommunicationChannel&) = delete;

    // Destructor to clean up the WebSocketClient
    ~CommunicationChannel() {
        delete webSocketClient;
    }



};

#endif // COMMUNICATIONCHANNEL_H
