#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QCoreApplication>
#include <QWebSocket>
#include <QTimer>
#include <QDebug>
#include "structures.h"
#include "MessageId.h"
class WebSocketClient : public QWebSocket {
    Q_OBJECT

public:
    WebSocketClient(QObject *parent = nullptr)
        : QWebSocket() {
        // Connect signals to corresponding slots
        connect(this, &QWebSocket::connected, this, &WebSocketClient::onConnected);
        connect(this, &QWebSocket::disconnected, this, &WebSocketClient::onDisconnected);
        connect(this, &QWebSocket::textMessageReceived, this, &WebSocketClient::onTextMessageReceived);
        connect(this, &QWebSocket::binaryMessageReceived, this, &WebSocketClient::onBinaryMessageReceived);

        // Initialize the timer for reconnection
        reconnectTimer = new QTimer(this);
        reconnectTimer->setInterval(2000); // 2 seconds
        connect(reconnectTimer, &QTimer::timeout, this, &WebSocketClient::attemptReconnect);
    }

    void connectToServer(const QString &serverUrl) {
        this->serverUrl = serverUrl;
        qDebug() << "Connecting to server..." << serverUrl;
        this->open(QUrl(serverUrl));
    }

    void sendMessageToServer(QByteArray message);

private slots:
    void onConnected() {
        qDebug() << "Connected to the server!";
        reconnectTimer->stop(); // Stop reconnection attempts once connected

        // Send a message to the server once connected (optional)
        sendTextMessage("Hello, test server!");
        sendPlayerConnectedMessage();
    }

    void onDisconnected() {
        qDebug() << "Disconnected from the server!";
        reconnectTimer->start(); // Start reconnecting every 2 seconds
    }

    void attemptReconnect() {
        qDebug() << "Attempting to reconnect...";
        this->open(QUrl(serverUrl)); // Try reconnecting to the server
    }

    void onTextMessageReceived(const QString &message) {
        qDebug() << "Message from server:" << message;
        // Handle received message from the server
    }
    void onBinaryMessageReceived(const QByteArray &message) {
        // emit processMessagesSignal(message);
        qDebug()<<"message recv";
    }

private:
    QTimer *reconnectTimer; // Timer to attempt reconnection
    QString serverUrl;      // Store the server URL for reconnection

    void sendPlayerConnectedMessage() {
        // Fill the structure with data
        P_S_CONNECTION_MESSAGE msg;
        msg.player_header.player_id = 1;  // Example player ID
        msg.player_header.message_id = P_S_CONNECTION_MESSAGE_ID;
        msg.player_header.v1 = 1;
        msg.player_header.v2 = 0;
        msg.player_header.v3 = 0;
        char buffer[sizeof(msg)];
        memcpy(&buffer,&msg,sizeof(msg));
        QByteArray data(buffer);

        sendMessageToServer(data);
    }


};




#endif // WEBSOCKETCLIENT_H
