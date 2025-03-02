#include "websocketclient.h"



void WebSocketClient::sendMessageToServer(QByteArray message) {

    sendBinaryMessage(message);
}
