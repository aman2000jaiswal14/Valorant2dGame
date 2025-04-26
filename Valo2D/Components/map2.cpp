#include "map2.h"

Map2::Map2()
{
    mainBoundingRectangle.setRect(QRectF(0, 0, 2300,1540));

    int offset = 300;
    outSideBoundingRectangle.setRect(QRectF(mainBoundingRectangle.boundingRect().topLeft().x()-offset, mainBoundingRectangle.boundingRect().topLeft().x()-offset, mainBoundingRectangle.boundingRect().width()+2*offset,mainBoundingRectangle.boundingRect().height()+2*offset));
    outSideBoundingRectangle.setBrush(QBrush(QColor(0,0,0)));

    mainBoundingRectangle.setBrush(QBrush(QColor("#CDF0F0")));
    mainBoundingRectangle.setPen(QPen(QColor(Qt::green),1));

    walls[0].setRect(QRectF(0, 200, 800,20));
    walls[0].setBrush(QBrush(QColor(Qt::gray)));


    walls[1].setRect(QRectF(400, 420, 500,100));
    walls[1].setBrush(QBrush(QColor(Qt::gray)));


    walls[2].setRect(QRectF(800, 420, 100,700));
    walls[2].setBrush(QBrush(QColor(Qt::gray)));

    walls[3].setRect(QRectF(400, 1020, 500,100));
    walls[3].setBrush(QBrush(QColor(Qt::gray)));

    walls[4].setRect(QRectF(0, 1320, 800,20));
    walls[4].setBrush(QBrush(QColor(Qt::gray)));



    walls[5].setRect(QRectF(2200, 200, 100,420));
    walls[5].setBrush(QBrush(QColor(Qt::gray)));

    walls[6].setRect(QRectF(1500, 420, 400,10));
    walls[6].setBrush(QBrush(QColor(Qt::gray)));

    walls[7].setRect(QRectF(1900, 420, 10,100));
    walls[7].setBrush(QBrush(QColor(Qt::gray)));

    walls[8].setRect(QRectF(1500, 520, 400,10));
    walls[8].setBrush(QBrush(QColor(Qt::gray)));

    walls[9].setRect(QRectF(1500, 520, 10,500));
    walls[9].setBrush(QBrush(QColor(Qt::gray)));

    walls[10].setRect(QRectF(1500, 1020, 400,10));
    walls[10].setBrush(QBrush(QColor(Qt::gray)));

    walls[11].setRect(QRectF(1900, 1020, 10,100));
    walls[11].setBrush(QBrush(QColor(Qt::gray)));

    walls[12].setRect(QRectF(1500, 1120, 400,10));
    walls[12].setBrush(QBrush(QColor(Qt::gray)));


    walls[13].setRect(QRectF(2200, 920, 100,420));
    walls[13].setBrush(QBrush(QColor(Qt::gray)));


    siteARectangle.setRect(400,620,300,300);
    siteARectangle.setBrush(QBrush(QColor(125,255,125,32)));

    siteBRectangle.setRect(1600,620,300,300);
    siteBRectangle.setBrush(QBrush(QColor(125,255,125,32)));

    siteAText.setPlainText("SITE A");
    siteAText.setPos(520,740);
    siteAText.setOpacity(0.5);

    siteBText.setPlainText("SITE B");
    siteBText.setPos(1720,740);
    siteBText.setOpacity(0.5);


    siteATimer = new QTimer;
    siteATimer->setInterval(1000);
    connect(siteATimer,&QTimer::timeout,this,&Map2::siteATimerTimeOutSlot);

    siteBTimer = new QTimer;
    siteBTimer->setInterval(1000);
    connect(siteBTimer,&QTimer::timeout,this,&Map2::siteBTimerTimeOutSlot);
}

void Map2::loadMap()
{
    if(getScene()){

        for(QGraphicsItem* item : getScene()->items())
        {
            getScene()->removeItem(item);
        }
    }
    // getScene()->clear();
    else
        return;
    getScene()->setSceneRect(mainBoundingRectangle.boundingRect());
    // qDebug()<<getScene()->sceneRect();

    // getScene()->addItem(&outSideBoundingRectangle);


    getScene()->addItem(&mainBoundingRectangle);
    getScene()->addLine(0,200,2300,200,QPen(Qt::white));
    getScene()->addLine(0,1340,2300,1340,QPen(Qt::white));
    getScene()->addItem(&siteARectangle);
    getScene()->addItem(&siteBRectangle);
    getScene()->addItem(&siteAText);
    getScene()->addItem(&siteBText);
    if(getEyesightItem())
    {
        getScene()->addItem(getEyesightItem());
    }


    for(int i=0;i<14;i++)
    {
        getScene()->addItem(&walls[i]);
    }



    for(int i=0;i<DataStore::getInstance().getMaxPlayersCount();i++)
    {
        getScene()->addItem(DataStore::getInstance().allGamePlayers[i]);

    }

    if(DataStore::getInstance().getGameMode() == GAME_MODE_DOMINATION)
    {
        siteATimer->start();
        siteBTimer->start();
    }

    getScene()->addItem(this->getCapturePointItem());

}

int Map2::getMapId()
{
    return 2;
}

bool Map2::isPositionValid(QPointF pos)
{
    if(!mainBoundingRectangle.contains(pos))
    {
        return false;
    }
    for(int i=0;i<14;i++)
    {
        if(walls[i].boundingRect().contains(pos))
        {
            return false;
        }
    }
    return true;
}

void Map2::siteATimerTimeOutSlot()
{
    if(siteARectangle.collidesWithItem(DataStore::getInstance().getGamePlayer()))
    {

        int othercounter = 0;
        for(int i=0;i<DataStore::getInstance().getMaxPlayersCount();i++)
        {
            if(DataStore::getInstance().allGamePlayers[i]->getTeam() != DataStore::getInstance().getGamePlayer()->getTeam()){
                if(siteARectangle.collidesWithItem(DataStore::getInstance().allGamePlayers[i]))
                {
                    othercounter++;
                    break;
                }
            }
        }

        if(othercounter ==0)
        {
            STRUCT_DOMINATION_TEAM_COUNTER_MSG msg;
            msg.msgHeader.messageId = D_S_DOMINATION_TEAM_COUNTER;
            msg.msgHeader.messageLen = sizeof(msg)-sizeof(msg.msgHeader);
            msg.msgHeader.userId = DataStore::getInstance().getRealPlayer()->getId();
            msg.siteNo = 1;
            msg.team = DataStore::getInstance().getGamePlayer()->getTeam();

            QByteArray data;
            data.resize(sizeof(msg));
            memcpy(data.data(),&msg,sizeof(msg));

            CommunicationChannel::getInstance().sendDataToServer(data);
        }
    }
}
void Map2::siteBTimerTimeOutSlot()
{
    if(siteBRectangle.collidesWithItem(DataStore::getInstance().getGamePlayer()))
    {

        int othercounter = 0;
        for(int i=0;i<DataStore::getInstance().getMaxPlayersCount();i++)
        {
            if(DataStore::getInstance().allGamePlayers[i]->getTeam() != DataStore::getInstance().getGamePlayer()->getTeam()){
                if(siteBRectangle.collidesWithItem(DataStore::getInstance().allGamePlayers[i]))
                {
                    othercounter++;
                    break;
                }
            }
        }

        if(othercounter ==0)
        {
            STRUCT_DOMINATION_TEAM_COUNTER_MSG msg;
            msg.msgHeader.messageId = D_S_DOMINATION_TEAM_COUNTER;
            msg.msgHeader.messageLen = sizeof(msg)-sizeof(msg.msgHeader);
            msg.msgHeader.userId = DataStore::getInstance().getRealPlayer()->getId();
            msg.siteNo = 2;
            msg.team = DataStore::getInstance().getGamePlayer()->getTeam();

            QByteArray data;
            data.resize(sizeof(msg));
            memcpy(data.data(),&msg,sizeof(msg));

            CommunicationChannel::getInstance().sendDataToServer(data);
        }
    }
}
