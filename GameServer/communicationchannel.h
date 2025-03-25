#ifndef COMMUNICATIONCHANNEL_H
#define COMMUNICATIONCHANNEL_H
#include <QObject>    // Ensure QObject is included
#include <QByteArray> // Include necessary Qt headers

#include "MessageId.h"
#include "structures.h"
#include <QTimer>

class WebSocketServer; // Forward declaration of WebSocketServer class

class CommunicationChannel : public QObject  // Ensure the class derives from QObject
{
    Q_OBJECT  // Add the Q_OBJECT macro

public:
    // Get the single instance of the class
    static CommunicationChannel& instance()
    {
        static CommunicationChannel instance; // This ensures only one instance is created
        return instance;
    }

    // Delete copy constructor and assignment operator to prevent copies
    CommunicationChannel(const CommunicationChannel&) = delete;
    CommunicationChannel& operator=(const CommunicationChannel&) = delete;

    // Destructor
    ~CommunicationChannel();

private:
    // Private constructor to prevent external instantiation
    CommunicationChannel();

    WebSocketServer* webSocketServer;  // The WebSocketServer instance (assumed to be a pointer)
    QTimer *positionTimer;
    QTimer *processMessagesTimer;
    QList<QByteArray> recvByteArrayListCopy;
public slots:
    void processMessagesSlot(QByteArray message);


    void positionTimeOutSlot();
    void processMessageTimeOutSlot();
};


#endif // COMMUNICATIONCHANNEL_H
