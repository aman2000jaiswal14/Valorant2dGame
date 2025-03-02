#include <QCoreApplication>
#include "communicationchannel.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug()<<"Game Server is running ....";
    CommunicationChannel::instance();
    return a.exec();
}
