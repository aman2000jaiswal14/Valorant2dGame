#include "collisiondetectionclass.h"
#include <QDebug>
CollisionDetectionClass::CollisionDetectionClass() {}

void CollisionDetectionClass::run()
{
    while(1)
    {
        msleep(200);
        // collision

        QList<QGraphicsItem *> collidingItems = DataStore::getInstance().getGamePlayer()->collidingItems();

        for(QGraphicsItem *cItem : collidingItems)
        {

            BulletInterface *b1 = dynamic_cast<BulletInterface *>(cItem);
            if(b1){
                // qDebug() << "Bullet hits! : "<<b1->getBulletId()<< " :unique : "<<b1->getUniqueNo()<<" :player Id: "<<b1->getGamePlayerId()<<"  :gunId:  "<<b1->getGunId() ;
                if(b1->getGamePlayerId() != DataStore::getInstance().getGamePlayer()->player()->getId() )
                {
                    if(DataStore::getInstance().getGameMode()== GAME_MODE_DOMINATION && DataStore::getInstance().allGamePlayers[DataStore::getInstance().playerIdToIMap[b1->getGamePlayerId()]]->getTeam() == DataStore::getInstance().getGamePlayer()->getTeam()){

                    }
                    else
                    {
                        emit bulletHitsTheCurrentPlayerSignal(b1);
                    }
                }

            }
        }
    }
}
