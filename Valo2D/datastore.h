#ifndef DATASTORE_H
#define DATASTORE_H

#include "realplayer.h"
#include "gameplayer.h"
#include "GlobalConstant.h"
#include "structures.h"
#include "agent1.h"
#include "gun1.h"
#include "gun2.h"
#include <QMutex>
#include <bulletinterface.h>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>


class DataStore
{
public:
    QList<QByteArray> recvByteArrayList;
    QMutex clientMutex;
    static DataStore&  getInstance();
    RealPlayer *getRealPlayer() const;
    void setRealPlayer(RealPlayer *newRealPlayer);

    GamePlayer *getGamePlayer() const;
    void setGamePlayer(GamePlayer *newGamePlayer);
    bool applicationClose = false;

    RealPlayer* allRealPlayers[MAX_LIMIT_OF_PLAYER];
    GamePlayer* allGamePlayers[MAX_LIMIT_OF_PLAYER];
    QMap<int,int> playerIdToIMap;

    void insertOnePlayerToAllGamePlayer(STRUCT_PLAYER_AGENT_SERVER data);
    void updatePlayerPosition(STRUCT_POSITION_MSG data);
    void updatePlayerHeadRotation(STRUCT_HEAD_ROTATION_MSG data);



    QMap<QPair<int,int>,BulletInterface *> bulletInfoMap;

    QGraphicsEllipseItem eyesightItem;
    // QGraphicsEllipseItem ellipseItem;
    QString getServerIp() const;
    void setServerIp(const QString &newServerIp);

    int getMaxPlayersCount() const;
    void setMaxPlayersCount(int newMaxPlayersCount);

    void checkVisibilityCheckToAllPlayer();

    QPointF mouseMovementCursorPosition;

    QPointF capturePosition;
    QPointF capturePositionDisplay;
    QPointF validCapturePositionDisplay;
    bool validCapturePositionFlag = false;



    int getGameMode() const;
    void setGameMode(int newGameMode);

private:
    DataStore();
    RealPlayer *realPlayer;
    GamePlayer *gamePlayer;
    QString serverIp="";
    int maxPlayersCount = 1;
    int gameMode = 0;


};

#endif // DATASTORE_H
