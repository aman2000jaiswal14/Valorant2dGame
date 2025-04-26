#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "datastore.h"
int main(int argc, char *argv[])
{
    if(argc==2)
    {
        DataStore::getInstance().setServerIp(argv[1]);
    }
    else
    {
        qDebug()<<"Invalid Server Ip";
        ::exit(1);
    }

    QApplication a(argc, argv);
    qRegisterMetaType<STRUCT_ACK>("STRUCT_ACK");
    qRegisterMetaType<STRUCT_POSITION_MSG>("STRUCT_POSITION_MSG");
    qRegisterMetaType<STRUCT_AGENT_SELECTED>("STRUCT_AGENT_SELECTED");
    qRegisterMetaType<STRUCT_PLAYER_POSITION>("STRUCT_PLAYER_POSITION");
    qRegisterMetaType<STRUCT_PLAYER_CONNECTED>("STRUCT_PLAYER_CONNECTED");
    qRegisterMetaType<STRUCT_PLAYER_AGENT_SERVER>("STRUCT_PLAYER_AGENT_SERVER");
    qRegisterMetaType<STRUCT_PLAYER_INFO>("STRUCT_PLAYER_INFO");
    qRegisterMetaType<STRUCT_PLAYER_INFO>("STRUCT_BULLET_INFO");
    qRegisterMetaType<STRUCT_PLAYER_INFO>("STRUCT_BULLET_INFO_MSG");
    qRegisterMetaType<STRUCT_PLAYER_INFO>("STRUCT_HEAD_ROTATION_MSG");

    MainWindow w;
    w.show();
    return a.exec();
}
