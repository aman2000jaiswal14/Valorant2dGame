#include "maingamepage.h"
#include "ui_maingamepage.h"
#include "gamescene.h"
#include "gameview.h"
#include <QDebug>
#include <QThread>
#include "datastore.h"
#include "middleware.h"

MainGamePage::  MainGamePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainGamePage)
{
    ui->setupUi(this);
    scene = new GameScene();
    view = new GameView();
    view->setScene(scene);
    map1 = MapFactoryClass::createMap(2);
    map1->setScene(scene);
    map1->setEyesightItem(&DataStore::getInstance().eyesightItem);


    ui->verticalLayout->addWidget(view);

    view->setMouseTracking(true);

    view->hide();

    connect(view,&GameView::sceneRotationAngleSignal,this,&MainGamePage::sceneRotationAngleSlot);
    connect(view,&GameView::gunFiredSignal,this,&MainGamePage::gunFiredSlot);
    connect(view,&GameView::removeBulletFromSceneSignal,this,&MainGamePage::removeBulletFromSceneSlot);
    connect(view,&GameView::bulletUpdatedSignal,this,&MainGamePage::bulletUpdatedSlot);
    connect(view,&GameView::capturePositionDisplaySignal,this,&MainGamePage::capturePositionDisplaySlot);
    connect(view,&GameView::capturePositionDisplayOffSignal,this,&MainGamePage::capturePositionDisplayOffSlot);

    ui->healthPb->setValue(DataStore::getInstance().getGamePlayer()->getHealth());
    ui->shieldPb->setValue(DataStore::getInstance().getGamePlayer()->getShield());

}

MainGamePage::~MainGamePage()
{
    delete ui;
}

void MainGamePage::connectCurrentPlayer()
{
    if(DataStore::getInstance().getGamePlayer())
    {
        connect(DataStore::getInstance().getGamePlayer(),&GamePlayerInterface::healthUpdatedSignal,this,&MainGamePage::healthUpdatedSlot);
        connect(DataStore::getInstance().getGamePlayer(),&GamePlayerInterface::gunChangeSignal,this,&MainGamePage::gunChangeSlot);
        connect(DataStore::getInstance().getGamePlayer(),&GamePlayerInterface::gamePlayerPositionChangeSignal,this,&MainGamePage::gamePlayerPositionChangeSlot);
        connect(DataStore::getInstance().getGamePlayer(),&GamePlayerInterface::eAbilitYUsedSignal,this,&MainGamePage::eAbilitYUsedSlot);

        setPlayerName(DataStore::getInstance().getGamePlayer()->player()->getName());
        // setPositionTransfrom();
    }



}

void MainGamePage::mainGamePreOpenConfiguration()
{

    map1->loadMap();
    if(DataStore::getInstance().getGamePlayer()->getTeam() == 1)
    {
        // up side down
        view->rotate(180);
    }
    eAbilitYUsedSlot();
    ui->systemMsglb->setText("");
    ui->frame_game->setFocus();
}

void MainGamePage::showView()
{

    view->show();
}

void MainGamePage::loadGame()
{

    showView();
}

MapInterFace *MainGamePage::getMap1() const
{
    return map1;
}

void MainGamePage::setMap1(MapInterFace *newMap1)
{
    map1 = newMap1;
}

void MainGamePage::keyPressEvent(QKeyEvent *event)
{
    STRUCT_PLAYER_POSITION pos;
    GamePlayerInterface *playerObj = DataStore::getInstance().getGamePlayer();
    STRUCT_PLAYER_POSITION diffpos ;
    pos.xpos = playerObj->getPositionX();
    pos.ypos = playerObj->getPositionY();

    diffpos.xpos = playerObj->getPositionX();
    diffpos.ypos = playerObj->getPositionY();

    int rotateSign = 1;
    if(DataStore::getInstance().getGamePlayer()->getTeam() == 1)
    {
        rotateSign = -1;
    }

    bool flg = false;


    if(DataStore::getInstance().getGamePlayer()->getHealth() >0)
    {
        if(event->key() == Qt::Key_W)
        {

            flg  =true;
            // playerObj->setPositionY(playerObj->getPositionY()-playerObj->getSpeed());
            pos.ypos = playerObj->getPositionY()-playerObj->getSpeed()*rotateSign;
        }
        if(event->key() == Qt::Key_A)
        {
            flg  =true;
            // playerObj->setPositionX(playerObj->getPositionX()-playerObj->getSpeed());
            pos.xpos = playerObj->getPositionX()-playerObj->getSpeed()*rotateSign;
        }
        if(event->key() == Qt::Key_D)
        {
            flg  =true;
            // playerObj->setPositionX(playerObj->getPositionX()+playerObj->getSpeed());
            pos.xpos = playerObj->getPositionX()+playerObj->getSpeed()*rotateSign;
        }
        if(event->key() == Qt::Key_S)
        {
            flg  =true;
            // playerObj->setPositionY(playerObj->getPositionY()+playerObj->getSpeed());
            pos.ypos = playerObj->getPositionY()+playerObj->getSpeed()*rotateSign;
        }
        if(event->key() == Qt::Key_E)
        {
            if(DataStore::getInstance().getGamePlayer())
            {
                DataStore::getInstance().getGamePlayer()->useEAbility();
            }

        }
    }



    if(event->key() == Qt::Key_B)
    {
        emit openCloseItemStoreSignal();
    }

    if(flg)
    {
        if(!map1->isPositionValid(QPointF(pos.xpos,pos.ypos))){

        }
        else if(!map1->isPositionValid(QPointF(pos.xpos+DataStore::getInstance().getGamePlayer()->boundingRect().width(),pos.ypos))){

        }
        else if(!map1->isPositionValid(QPointF(pos.xpos,pos.ypos+DataStore::getInstance().getGamePlayer()->boundingRect().height()))){

        }
        else if(!map1->isPositionValid(QPointF(pos.xpos+DataStore::getInstance().getGamePlayer()->boundingRect().width(),pos.ypos+DataStore::getInstance().getGamePlayer()->boundingRect().height()))){

        }
        else if(!map1->isPositionValid(QPointF(pos.xpos+DataStore::getInstance().getGamePlayer()->boundingRect().width()/2,pos.ypos+DataStore::getInstance().getGamePlayer()->boundingRect().height()/2))){

        }
        else {

            MiddleWare::getInstance().sendPlayerPositionMsg(pos);



            /*  // incremental update of position no effect

            double diffX = pos.xpos - playerObj->getPositionX()  ;
            double diffY = pos.ypos - playerObj->getPositionY();
            int xSign=1;
            int ySign =1;
            if(diffX<0){
                xSign = -1;
                diffX = -diffX;
            }
            if(diffY<0)
            {
                ySign = -1;
                diffY = -diffY;

            }
            while(diffX>=1)
            {
                diffpos.xpos+=xSign;
                MiddleWare::getInstance().sendPlayerPositionMsg(diffpos);
                diffX-=1;
            }
            if(diffX>0)
            {
                diffpos.xpos+=(xSign)*diffX;
                MiddleWare::getInstance().sendPlayerPositionMsg(diffpos);
                diffX = 0;
            }

            while(diffY>=1)
            {
                diffpos.ypos+=ySign;
                MiddleWare::getInstance().sendPlayerPositionMsg(diffpos);
                diffY-=1;
            }
            if(diffY>0)
            {
                diffpos.ypos+=(ySign)*diffY;
                MiddleWare::getInstance().sendPlayerPositionMsg(diffpos);
                diffY = 0;
            }
            */

        }


    }
}

void MainGamePage::keyReleaseEvent(QKeyEvent *event)
{

}

void MainGamePage::addPlayer(GamePlayerInterface *player)
{
    scene->addItem(player);
}


void MainGamePage::removePlayer(GamePlayerInterface *player)
{
    scene->removeItem(player);
}

void MainGamePage::addBullet(BulletInterface *bullet)
{
    scene->addItem(bullet);

}

void MainGamePage::removeBullet(BulletInterface *bullet)
{

    scene->removeItem(bullet);

}

void MainGamePage::setPlayerName(QString pName)
{
    ui->playerName->setText(pName);
}

void MainGamePage::addAllPlayerToScene()
{
    for(int i=0;i<DataStore::getInstance().getMaxPlayersCount();i++)
    {
        addPlayer(DataStore::getInstance().allGamePlayers[i]);

    }
}

void MainGamePage::setPositionTransfrom()
{
    // qDebug()<<DataStore::getInstance().getGamePlayer()->getPositionX()<<DataStore::getInstance().getGamePlayer()->getPositionY();
    if(DataStore::getInstance().getGamePlayer())
    {
        view->centerOn(DataStore::getInstance().getGamePlayer()->x(),DataStore::getInstance().getGamePlayer()->y());
    }




}

void MainGamePage::eAbilityBuy()
{
    ui->eAbilityLeft->setText(QString::number(DataStore::getInstance().getGamePlayer()->getAgent()->getEAbility()->getAbilityLeftCount()));

}

void MainGamePage::sceneRotationAngleSlot(double rotation)
{
    MiddleWare::getInstance().sendHeadRotationMsg(rotation);
}

void MainGamePage::gunFiredSlot(BulletInterface *bullet)
{
    addBullet(bullet);

}

void MainGamePage::removeBulletFromSceneSlot(BulletInterface *bullet)
{
    scene->removeItem(bullet);
    // qDebug()<<"bullet removed";
}

void MainGamePage::healthUpdatedSlot(GamePlayerInterface* player)
{
    if(player->player()->getId() == DataStore::getInstance().getGamePlayer()->player()->getId())
    {
        ui->healthPb->setValue(DataStore::getInstance().getGamePlayer()->getHealth());
        ui->shieldPb->setValue(DataStore::getInstance().getGamePlayer()->getShield());
    }

}

void MainGamePage::gunChangeSlot()
{
    if(DataStore::getInstance().getGamePlayer()->getGun())
    {
        ui->gunName->setText(DataStore::getInstance().getGamePlayer()->getGun()->getName());
        connect(DataStore::getInstance().getGamePlayer()->getGun(),&GunInterface::bulletStatusUpdatedSignal,this,&MainGamePage::bulletStatusUpdatedSlot);
        DataStore::getInstance().getGamePlayer()->getGun()->configureGun();
    }

    bulletStatusUpdatedSlot();
}

void MainGamePage::bulletStatusUpdatedSlot()
{
    ui->bulletCount->setText(QString::number(DataStore::getInstance().getGamePlayer()->getGun()->getBulletLeft()));
    ui->magzineCount->setText(QString::number(DataStore::getInstance().getGamePlayer()->getGun()->getMagzineLeft()));
}

void MainGamePage::bulletUpdatedSlot(BulletInterface *bullet, double xpos, double ypos)
{
    bool isValidFlag = false;
    if(!map1->isPositionValid(QPointF(xpos,ypos))){

    }
    else if(!map1->isPositionValid(QPointF(xpos+bullet->boundingRect().width(),ypos))){

    }
    else if(!map1->isPositionValid(QPointF(xpos,ypos+bullet->boundingRect().height()))){

    }
    else if(!map1->isPositionValid(QPointF(xpos+bullet->boundingRect().width(),ypos+bullet->boundingRect().height()))){

    }
    else if(!map1->isPositionValid(QPointF(xpos+bullet->boundingRect().width()/2,ypos+bullet->boundingRect().height()/2))){

    }
    else {

        isValidFlag = true;
        // bullet path tracing check;
        int checkCount = 100;

        double diffX = xpos - bullet->getPosX();
        double diffY = ypos - bullet->getPosY();

        checkCount = qMin(qFloor(qMax(diffX,diffY)),checkCount);
        for(int i=1;i<checkCount;i++)
        {
            double checkX = bullet->getPosX() + (i*diffX)/checkCount;
            double checkY = bullet->getPosY() + (i*diffY)/checkCount;

            if(!map1->isPositionValid(QPointF(checkX,checkY)))
            {
                isValidFlag = false;
                break;
            }
        }

        //


    }
    if(!isValidFlag)
    {
        bullet->stopBulletTimer();
        return;
    }
    STRUCT_BULLET_INFO bullet_info;
    bullet_info.uniqueNo = bullet->getUniqueNo();
    bullet_info.bulletId = bullet->getBulletId();
    bullet_info.startPosX = bullet->getStartPosX();
    bullet_info.startPosY = bullet->getStartPoxY();
    bullet_info.posX = xpos;
    bullet_info.posY = ypos;
    bullet_info.angle = bullet->getAngle();
    bullet_info.playerId = bullet->getGamePlayerId();
    bullet_info.gunId = bullet->getGunId();


    MiddleWare::getInstance().sendBulletInfoMsg(bullet_info);
}

void MainGamePage::gamePlayerPositionChangeSlot()
{
    setPositionTransfrom();
}

void MainGamePage::eAbilitYUsedSlot()
{
    if(DataStore::getInstance().getGamePlayer()->getAgent() && DataStore::getInstance().getGamePlayer()->getAgent()->getEAbility())
    {
        ui->eAbilityLeft->setText(QString::number(DataStore::getInstance().getGamePlayer()->getAgent()->getEAbility()->getAbilityLeftCount()));
    }
}

void MainGamePage::capturePositionDisplaySlot()
{
    DataStore::getInstance().validCapturePositionFlag = false;
    QColor col = QColor(0,255,0,255);
    if(map1->isPositionValid(DataStore::getInstance().capturePositionDisplay))
    {
        DataStore::getInstance().validCapturePositionDisplay = DataStore::getInstance().capturePositionDisplay;
        DataStore::getInstance().validCapturePositionFlag = true;
        col = QColor(0,255,0,255);

    }
    else
    {
        col = QColor(255,0,0,255);
    }

    map1->showCapturePoint(DataStore::getInstance().capturePositionDisplay,col);
    ui->systemMsglb->setText("Released Position Marked");
}

void MainGamePage::capturePositionDisplayOffSlot()
{
    map1->hideCapturePoint();
    DataStore::getInstance().validCapturePositionFlag = false;
    ui->systemMsglb->setText("");
}


