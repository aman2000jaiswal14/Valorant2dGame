#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QCoreApplication>
#include <QWebSocket>
#include <QTimer>
#include <QDebug>
#include "structures.h"
#include "MessageId.h"



class WebSocketClient : public QObject
{
    Q_OBJECT
public:
    bool clientState=false;
    WebSocketClient(const QUrl url);
    void openClientSocket();
    void sendByteDataToServer(QByteArray sendbyteArray);
    void sendPlayerConnectedMessage() {
        // Fill the structure with data
        P_S_CONNECTION_MESSAGE msg;
        msg.player_header.player_id = 1;  // Example player ID
        msg.player_header.message_id = P_S_CONNECTION_MESSAGE_ID;
        msg.player_header.v1 = 1;
        msg.player_header.v2 = 0;
        msg.player_header.v3 = 0;
        char buffer[sizeof(msg)];
        memcpy(buffer,&msg,sizeof(msg));
        QByteArray data(buffer,sizeof(msg));

        sendByteDataToServer(data);
    }
signals:
    void updatePlayersPositionSignal(STRUCT_ALL_PLAYER_POSITION_INFO players_pos_info);

private slots:
    void onConnected();
    void onTextMessageReceived(const QString message);
    void onBinaryMessageReceived(const QByteArray &message);
    void disconnected();
    void onErrorOccur();
    void clientToServerReconnectTimerSlot();


private:
    QUrl _url;
    int msec_reconnect_to_server=1000;
    QWebSocket *_client_socket;
    QTimer *clientToServerReconnectTimer;
};

// class WebSocketClient : public QWebSocket {
//     Q_OBJECT

// public:
//     WebSocketClient(QObject *parent = nullptr)
//         : QWebSocket() {
//         // Connect signals to corresponding slots
//         connect(this, &QWebSocket::connected, this, &WebSocketClient::onConnected);
//         connect(this, &QWebSocket::disconnected, this, &WebSocketClient::onDisconnected);
//         connect(this, &QWebSocket::textMessageReceived, this, &WebSocketClient::onTextMessageReceived);
//         connect(this, &QWebSocket::binaryMessageReceived, this, &WebSocketClient::onBinaryMessageReceived);

//         // Initialize the timer for reconnection
//         reconnectTimer = new QTimer(this);
//         reconnectTimer->setInterval(2000); // 2 seconds
//         connect(reconnectTimer, &QTimer::timeout, this, &WebSocketClient::attemptReconnect);
//     }

//     void connectToServer(const QString &serverUrl) {
//         this->serverUrl = serverUrl;
//         qDebug() << "Connecting to server..." << serverUrl;
//         this->open(QUrl(serverUrl));
//     }

//     void sendMessageToServer(QByteArray message);

// private slots:
//     void onConnected() {
//         qDebug() << "Connected to the server!";
//         reconnectTimer->stop(); // Stop reconnection attempts once connected

//         // Send a message to the server once connected (optional)
//         sendTextMessage("Hello, test server!");
//         sendPlayerConnectedMessage();
//     }

//     void onDisconnected() {
//         qDebug() << "Disconnected from the server!";
//         reconnectTimer->start(); // Start reconnecting every 2 seconds
//     }

//     void attemptReconnect() {
//         qDebug() << "Attempting to reconnect...";
//         this->open(QUrl(serverUrl)); // Try reconnecting to the server
//     }

//     void onTextMessageReceived(const QString &message) {
//         qDebug() << "Message from server:" << message;
//         // Handle received message from the server
//     }
//     void onBinaryMessageReceived(const QByteArray &message) {
//         // emit processMessagesSignal(message);
//         qDebug()<<"message recv";

//         STRUCT_SERVER_HEADER serverHeader;
//         memcpy(&serverHeader,message.data(),sizeof(STRUCT_SERVER_HEADER));
//         if(serverHeader.message_id == S_P_POSITION_MESSAGE_ID)
//         {
//             S_P_POSITION_MESSAGE msg;
//             memcpy(&msg,message.data(),sizeof(S_P_POSITION_MESSAGE));
//             updatePlayersPositionSignal(msg.players_pos_info);
//         }

//     }

// private:
//     QTimer *reconnectTimer; // Timer to attempt reconnection
//     QString serverUrl;      // Store the server URL for reconnection




// };




#endif // WEBSOCKETCLIENT_H
