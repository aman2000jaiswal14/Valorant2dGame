#include "processthreadclass.h"

ProcessThreadClass::ProcessThreadClass()
{

}

bool ProcessThreadClass::checkBulletHitThePlayer(STRUCT_BULLET_INFO_MSG data)
{

    bool toCheck = false;
    if(data.bullet_info.playerId  != DataStore::getInstance().getGamePlayer()->player()->getId())
    {
        int ithPlayer = DataStore::getInstance().playerIdToIMap[data.bullet_info.playerId ];
        if(DataStore::getInstance().getGameMode() == GAME_MODE_DOMINATION && DataStore::getInstance().allGamePlayers[ithPlayer]->getTeam() != DataStore::getInstance().getGamePlayer()->getTeam())
        {
            toCheck = true;
        }
    }
    if(!toCheck)
    {
        return false;
    }
    int uqno = data.bullet_info.uniqueNo;
    int userId = data.bullet_info.playerId;
    QPair<int,int> bullet_key = {uqno,userId};

    // if(data.)
    bool hitThePlayer = false;
    if(DataStore::getInstance().bulletInfoMap.contains(bullet_key))
    {
        if(data.bullet_info.destroyed == true)
        {

        }
        else
        {
            BulletInterface *bullet = DataStore::getInstance().bulletInfoMap[bullet_key];
            double xpos = data.bullet_info.posX;
            double ypos = data.bullet_info.posY;


            // bullet path tracing check;
            int checkCount = 50;

            double diffX = xpos - bullet->getPosX();
            double diffY = ypos - bullet->getPosY();

            double distance = qSqrt(diffX*diffX+diffY*diffY);


            int pxGap = 5;
            checkCount = qFloor(distance/pxGap);

            for(int i=1;i<checkCount;i++)
            {
                double checkX = bullet->getPosX() + pxGap*i*qCos(qDegreesToRadians(data.bullet_info.angle)) + bullet->boundingRect().width()/2;
                double checkY = bullet->getPosY() + pxGap*i*qSin(qDegreesToRadians(data.bullet_info.angle)) + bullet->boundingRect().height()/2;

                QRectF rectf = QRectF(DataStore::getInstance().getGamePlayer()->getPositionX(),DataStore::getInstance().getGamePlayer()->getPositionY(),DataStore::getInstance().getGamePlayer()->boundingRect().width(),DataStore::getInstance().getGamePlayer()->boundingRect().height());
                // qDebug()<<DataStore::getInstance().getGamePlayer()->childrenBoundingRect()<<DataStore::getInstance().getGamePlayer()->boundingRect();
                // rectf.setX(rectf.x()+DataStore::getInstance().getGamePlayer()->getPositionX());
                // rectf.setY(rectf.y()+DataStore::getInstance().getGamePlayer()->getPositionY());

                if(rectf.contains(QPointF(checkX,checkY)))
                {
                    hitThePlayer = true;
                    return hitThePlayer;
                }
            }

            double checkX = data.bullet_info.posX + bullet->boundingRect().width()/2;
            double checkY = data.bullet_info.posY + bullet->boundingRect().height()/2;

            QRectF rectf = QRectF(DataStore::getInstance().getGamePlayer()->getPositionX(),DataStore::getInstance().getGamePlayer()->getPositionY(),DataStore::getInstance().getGamePlayer()->boundingRect().width(),DataStore::getInstance().getGamePlayer()->boundingRect().height());

            if(rectf.contains(QPointF(checkX,checkY)))
            {
                hitThePlayer = true;
                return hitThePlayer;
            }

        }
    }
    else
    {
        if(data.bullet_info.destroyed == true)
        {

        }
        else
        {

        }
    }

    return hitThePlayer;
}

ProcessThreadClass &ProcessThreadClass::getInstance()
{
    static ProcessThreadClass processThreadobj;
    return processThreadobj;
}

void ProcessThreadClass::run()
{
    while (!DataStore::getInstance().applicationClose) {
        while(DataStore::getInstance().recvByteArrayList.size())
        {
            DataStore::getInstance().clientMutex.lock();
            recvByteArrayListProcess = DataStore::getInstance().recvByteArrayList;
            DataStore::getInstance().recvByteArrayList.clear();
            DataStore::getInstance().clientMutex.unlock();

            for(QByteArray recvdBytes : recvByteArrayListProcess)
            {
                QByteArray msg = recvdBytes;

                STRUCT_MESSAGE_HEADER msgHeader;
                memcpy(&msgHeader,msg.data(),sizeof(msgHeader));

                if(msgHeader.messageId == S_D_ACK){
                    STRUCT_ACK data;
                    memcpy(&data,msg.data(),sizeof(data));
                    emit ackMessageSignal(data);
                }
                else if(msgHeader.messageId == S_D_PLAYER_INFO){
                    STRUCT_PLAYER_INFO data;
                    memcpy(&data,msg.data(),sizeof(data));

                    DataStore::getInstance().getRealPlayer()->setId(msgHeader.userId);
                    QString username=QString(data.username);
                    QString name=QString(data.name);
                    DataStore::getInstance().getRealPlayer()->setUsername(username);
                    DataStore::getInstance().getRealPlayer()->setName(name);
                    DataStore::getInstance().getRealPlayer()->setRankXp(data.rankXp);
                    emit updatedRealPlayerSignal();

                }
                else if(msgHeader.messageId == S_AD_GO_TO_AGENT_SELECTION){
                    emit goToAgentSelectionPageSignal();
                }
                else if(msgHeader.messageId == S_AD_PLAYER_ID_CONNECTED){
                    STRUCT_PLAYER_CONNECTED data;
                    memcpy(&data,msg.data(),sizeof(data));
                    emit insertOnePlayerToAllGamePlayerSignal(data);


                }
                else if(msgHeader.messageId == S_AD_PLAYER_AGENT_SELECTED){
                    STRUCT_PLAYER_CONNECTED data;
                    memcpy(&data,msg.data(),sizeof(data));
                    emit insertOnePlayerToAllGamePlayerSignal(data);
                    emit updateGamePlayerSignal();

                }
                else if(msgHeader.messageId == S_D_POSITION_UPDATE){
                    STRUCT_POSITION_MSG data;
                    memcpy(&data,msg.data(),sizeof(data));
                    emit updateGamePlayerPositionSignal(data);
                }
                else if(msgHeader.messageId == S_D_HEAD_ROTATION_UPDATE){
                    STRUCT_HEAD_ROTATION_MSG data;
                    memcpy(&data,msg.data(),sizeof(data));
                    emit updateGamePlayerHeadRotationSignal(data);
                }

                else if(msgHeader.messageId == S_D_BULLET_INFO){
                    STRUCT_BULLET_INFO_MSG data;
                    memcpy(&data,msg.data(),sizeof(data));

                    bool hitThePlayer = checkBulletHitThePlayer(data);
                    emit updateBulletInfoSignal(data,hitThePlayer);
                }
                else if(msgHeader.messageId == S_D_BULLET_HIT_THE_PLAYER){
                    STRUCT_BULLET_INFO_MSG data;
                    memcpy(&data,msg.data(),sizeof(data));
                    emit updateBulletHitPlayerSignal(data);
                }
                else if(msgHeader.messageId == S_D_GUN_SELECTED){
                    STRUCT_GUN_SELECTED data;
                    memcpy(&data,msg.data(),sizeof(data));
                    emit updateGunSelectedByPlayerSignal(data);
                }
                else if(msgHeader.messageId == S_D_DOMINATION_SCORE){
                    STRUCT_DOMINATION_SCORE_MSG data;
                    memcpy(&data,msg.data(),sizeof(data));
                    emit updateDominationScoreSignal(data);
                }
                else if(msgHeader.messageId == S_D_SET_HEALTH_MSG){
                    STRUCT_SET_HEALTH_OF_PLAYER_MSG data;
                    memcpy(&data,msg.data(),sizeof(data));
                    emit setHealthOfPlayerSignal(data);
                }
            }
        }
    }

}

