#include "datastore.h"
#include <QDebug>
#include "gunfactoryclass.h"
#include "agentfactoryclass.h"
DataStore& DataStore::getInstance()
{
    static DataStore datastoreObj;
    return datastoreObj;
}

DataStore::DataStore() {
    realPlayer = new RealPlayer;
    gamePlayer = new GamePlayer(realPlayer);
    for(int i=0;i<MAX_LIMIT_OF_PLAYER;i++)
    {
        allRealPlayers[i] = new RealPlayer();
        allGamePlayers[i] = new GamePlayer(allRealPlayers[i]);
        allGamePlayers[i]->setPositionX((i+1)*100);
        allGamePlayers[i]->setPositionY((i+1)*100);
    }
    // allGamePlayers[0]->setPositionX(300);
    // allGamePlayers[0]->setPositionY(300);
    eyesightItem.setSpanAngle((15) * 16);
    eyesightItem.setSpanAngle((175) * 16);
    eyesightItem.setRect(QRectF(0, 0, 300, 300));
    eyesightItem.setPen(QPen(Qt::black,0));
    eyesightItem.setBrush(QBrush(QColor(255,0,0,15)));



}

int DataStore::getGameMode() const
{
    return gameMode;
}

void DataStore::setGameMode(int newGameMode)
{
    gameMode = newGameMode;
}

int DataStore::getMaxPlayersCount() const
{
    return maxPlayersCount;
}

void DataStore::setMaxPlayersCount(int newMaxPlayersCount)
{
    maxPlayersCount = newMaxPlayersCount;
}

void DataStore::checkVisibilityCheckToAllPlayer()
{
    for(int i=0;i<DataStore::getInstance().getMaxPlayersCount();i++)
    {
        if(DataStore::getInstance().getGamePlayer()->player()->getId() == allGamePlayers[i]->player()->getId())
        {
            continue;
        }
        QRectF itemRect(allGamePlayers[i]->getPositionX(),allGamePlayers[i]->getPositionY(),allGamePlayers[i]->boundingRect().width(),allGamePlayers[i]->boundingRect().height());
        if(DataStore::getInstance().getGamePlayer()->checkItemInEyeSightRange(itemRect)){
            allGamePlayers[i]->setVisible(true);
        }
        else
        {
            allGamePlayers[i]->setVisible(false);
        }
    }
}

QString DataStore::getServerIp() const
{
    return serverIp;
}

void DataStore::setServerIp(const QString &newServerIp)
{
    serverIp = newServerIp;
}

GamePlayer *DataStore::getGamePlayer() const
{
    return gamePlayer;
}

void DataStore::setGamePlayer(GamePlayer *newGamePlayer)
{
    gamePlayer = newGamePlayer;
    gamePlayer->setEyeSightItem(&eyesightItem);

}

void DataStore::insertOnePlayerToAllGamePlayer(STRUCT_PLAYER_AGENT_SERVER data)
{
    for(int i=0;i<DataStore::getInstance().getMaxPlayersCount();i++){
        if(allGamePlayers[i]->player()->getId() == data.player_id)
        {
            allGamePlayers[i]->player()->setId(data.player_id);
            allGamePlayers[i]->player()->setName(QString(data.name));
            allGamePlayers[i]->player()->setUsername(QString(data.username));
            allGamePlayers[i]->player()->setRankXp(data.rankXp);
            allGamePlayers[i]->setTeam(data.team);

            AgentInterFace *agent = AgentFactoryClass::createAgent(data.agent_id);
            allGamePlayers[i]->setAgent(agent);

            GunInterface *gun = GunFactoryClass::createGun(data.gun_id);
            allGamePlayers[i]->setGun(gun);
            return;
        }
    }
    for(int i=0;i<DataStore::getInstance().getMaxPlayersCount();i++){
        if(allGamePlayers[i]->player()->getId() == 0)
        {
            playerIdToIMap[data.player_id] = i;
            allGamePlayers[i]->player()->setId(data.player_id);
            allGamePlayers[i]->player()->setName(QString(data.name));
            allGamePlayers[i]->player()->setUsername(QString(data.username));
            allGamePlayers[i]->player()->setRankXp(data.rankXp);
            allGamePlayers[i]->setTeam(data.team);
            AgentInterFace *agent = AgentFactoryClass::createAgent(data.agent_id);
            allGamePlayers[i]->setAgent(agent);

            GunInterface *gun = GunFactoryClass::createGun(data.gun_id);
            allGamePlayers[i]->setGun(gun);
            return;

        }
    }
}

void DataStore::updatePlayerPosition(STRUCT_POSITION_MSG data)
{
    for(int i=0;i<DataStore::getInstance().getMaxPlayersCount();i++)
    {
        if(allGamePlayers[i]->player()->getId() == data.msgHeader.userId)
        {

            // allGamePlayers[i]->setPositionX(data.playerPosition.xpos);
            // allGamePlayers[i]->setPositionY(data.playerPosition.ypos);
            allGamePlayers[i]->setSmoothPosition(data.playerPosition.xpos,data.playerPosition.ypos);

            // qDebug()<<allGamePlayers[i]->pos();
            break;
        }
    }

    // visibility check
    checkVisibilityCheckToAllPlayer();

}

void DataStore::updatePlayerHeadRotation(STRUCT_HEAD_ROTATION_MSG data)
{
    for(int i=0;i<DataStore::getInstance().getMaxPlayersCount();i++)
    {
        if(allGamePlayers[i]->player()->getId() == data.msgHeader.userId)
        {
            allGamePlayers[i]->setHeadPosition(data.rotation);
            // qDebug()<<allGamePlayers[i]->player()->getId()<<" rot : "<<allGamePlayers[i]->getHeadPosition();
            break;
        }
    }

    // visibility check
    checkVisibilityCheckToAllPlayer();
}



RealPlayer *DataStore::getRealPlayer() const
{
    return realPlayer;
}

void DataStore::setRealPlayer(RealPlayer *newRealPlayer)
{
    realPlayer = newRealPlayer;
}
