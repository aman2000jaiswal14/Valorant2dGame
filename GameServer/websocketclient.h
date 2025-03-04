#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QWebSocket>
#include <QUrl>
#include <QDebug>
#include <Structures.h>
#include <QTimer>
#include "datastore.h"

class WebSocketClient : public QObject
{
    Q_OBJECT
public:
    bool clientState=false;
    WebSocketClient(const QUrl url);
    void openClientSocket();
    void sendByteDataToServer(QByteArray sendbyteArray);

signals:

private slots:
    void onConnected();
    void onTextMessageReceived(const QString message);
    void onBinaryMessageReceived(const QByteArray &message);
    void disconnected();
    void onErrorOccur();
    void clientToServerReconnectTimerSlot();


private:
    QUrl _url;
    int msec_reconnect_to_server=5000;
    QWebSocket *_client_socket;
    QTimer *clientToServerReconnectTimer;
    void printMessageHeader(STRUCT_MESSAGE_HEADER msg_header);
    void printExampleData(const QByteArray &data);
};

#endif // WEBSOCKETCLIENT_H
