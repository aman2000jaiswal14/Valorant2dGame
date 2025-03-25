#ifndef COMMUNICATIONCHANNEL_H
#define COMMUNICATIONCHANNEL_H
#include "structures.h"
#include "MessageId.h"
#include <QObject>
class WebSocketClient;
class structures;
class CommunicationChannel : public QObject
{
    Q_OBJECT
public:
    static CommunicationChannel& instance()
    {
        static CommunicationChannel instance;
        return instance;
    }
    void updateCurrentPlayerPosition(STRUCT_PLAYER_POSITION_INFO pos_info);

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
public slots:
    void updatePlayerPositionSlot(STRUCT_ALL_PLAYER_POSITION_INFO players_pos_info);


public:
    STRUCT_ALL_PLAYER_POSITION_INFO allPlayerPosition;


};

#endif // COMMUNICATIONCHANNEL_H
