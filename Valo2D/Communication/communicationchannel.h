#ifndef COMMUNICATIONCHANNEL_H
#define COMMUNICATIONCHANNEL_H


#include <QObject>
#include <QByteArray>
#include <structures.h>
#include <messages.h>
#include <GlobalConstant.h>

class WebSocketClient;
class CommunicationChannel : public QObject
{
    Q_OBJECT
public:
    static CommunicationChannel& getInstance();
    void sendDataToServer(QByteArray data);
private:
    CommunicationChannel();
    WebSocketClient *webSocketClient = nullptr;

public slots:
    void serverDisconnectedSlot();
signals:
    void serverDisconnectedSignal();

};

#endif // COMMUNICATIONCHANNEL_H
