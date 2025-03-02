#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QByteArray>
#include <QDataStream>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QDebug>
#include <QList>
#include <QObject>
#include "structures.h"
#include "datastore.h"
#include "MessageId.h"
class WebSocketServer : public QWebSocketServer {
    Q_OBJECT

public:
    WebSocketServer(const QString &serverName, QObject *parent = nullptr)
        : QWebSocketServer(serverName, QWebSocketServer::NonSecureMode, parent),
        maxClients(6) {
    }

    bool startServer(const QHostAddress &address, quint16 port) {
        if (this->listen(address, port)) {
            qDebug() << "Server started on" << address.toString() << ":" << port;
            // Connect the newConnection signal to our slot
            connect(this, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);
            return true;
        } else {
            qWarning() << "Failed to start server!";
            return false;
        }
    }

private slots:
    void onNewConnection() {
        if (clients.count() >= maxClients) {
            qWarning() << "Maximum client limit reached, rejecting new connection!";
            return;
        }

        QWebSocket *socket = this->nextPendingConnection();

        if (!socket) {
            qWarning() << "Failed to establish connection!";
            return;
        }

        // Connect necessary signals to slots
        connect(socket, &QWebSocket::textMessageReceived, this, &WebSocketServer::onTextMessageReceived);
        connect(socket, &QWebSocket::binaryMessageReceived, this, &WebSocketServer::onBinaryMessageReceived);
        connect(socket, &QWebSocket::disconnected, this, &WebSocketServer::onClientDisconnected);

        // Add the new client to the list
        clients.append(socket);
        qDebug() << "New client connected, total clients:" << clients.count();
    }

    void onTextMessageReceived(const QString &message) {
        qDebug() << "Message received:" << message;
        // Echo message back to all clients
        for (QWebSocket *client : clients) {
            client->sendTextMessage(message);
        }
    }

    void onBinaryMessageReceived(const QByteArray &message) {
        emit processMessagesSignal(message);
    }

    void onClientDisconnected() {
        QWebSocket *socket = qobject_cast<QWebSocket *>(sender());
        if (socket) {
            clients.removeAll(socket);
            socket->deleteLater();
            qDebug() << "Client disconnected, total clients:" << clients.count();
        }
    }

public:
    void sendPositionToAllClients(const S_P_POSITION_MESSAGE &message) {


        // Send the message to all clients
        char buffer[sizeof(message)];
        memcpy(buffer,&message,sizeof(message));
        QByteArray data(buffer,sizeof(message));
        for (QWebSocket *client : clients) {
            client->sendBinaryMessage(data);
        }
    }

signals:
    void processMessagesSignal(QByteArray message);

private:
    QList<QWebSocket *> clients; // Stores connected clients
    const int maxClients; // Maximum number of clients allowed
};

#endif // WEBSOCKETSERVER_H
