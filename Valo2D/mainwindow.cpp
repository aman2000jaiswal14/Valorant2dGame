#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginpage.h"
#include "signuppage.h"
#include "connecttoserverpage.h"
#include "agentselectionpage.h"
#include "maingamepage.h"
#include "waitingpage.h"
#include <communicationchannel.h>
#include <processthreadclass.h>
#include "bulletinterface.h"
#include <QPair>
#include <QMap>
#include "specialutils.h"
#include <itemstorepage.h>
#include "bulletfactoryclass.h"
#include <QScreen>

#include "middleware.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowFullScreen);
    communicationChannel = &CommunicationChannel::getInstance();
    ProcessThreadClass::getInstance().start();
    // collisionDetectionObj = new CollisionDetectionClass;
    // collisionDetectionObj->start();

    loginPage = new LoginPage(this);
    signUpPage = new SignupPage(this);
    connectToServerPage = new ConnectToServerPage(this);
    agentSelectionPage = new AgentSelectionPage(this);
    mainGamePage = new MainGamePage(this);
    waitingPage = new WaitingPage(this);
    itemStorePage = new ItemStorePage(this);

    stackWidget = new QStackedWidget;
    ui->verticalLayout_2->addWidget(stackWidget);
    stackWidget->addWidget(loginPage);
    stackWidget->addWidget(signUpPage);
    stackWidget->addWidget(connectToServerPage);
    stackWidget->addWidget(agentSelectionPage);
    stackWidget->addWidget(mainGamePage);
    stackWidget->addWidget(waitingPage);


    // Progress Bars
    QLabel *teamAlb = new QLabel("SITE A :- Team A :");
    QLabel *teamBlb = new QLabel(" | Team B :");
    teamAPb = new QProgressBar;
    teamBPb = new QProgressBar;
    teamAPb->setRange(0, 100); teamAPb->setValue(75);
    teamBPb->setRange(0, 100); teamBPb->setValue(45);
    teamAPb->setFixedWidth(100);
    teamBPb->setFixedWidth(100);
    teamAPb->setStyleSheet("QProgressBar::chunk { background: #3498db; }");
    teamBPb->setStyleSheet("QProgressBar::chunk { background: #e74c3c; }");

    // Progress Bars
    QLabel *teamASite2lb = new QLabel("SITE B :- Team A :");
    QLabel *teamBSite2lb = new QLabel(" | Team B :");
    teamASite2Pb = new QProgressBar;
    teamBSite2Pb = new QProgressBar;
    teamASite2Pb->setRange(0, 100); teamASite2Pb->setValue(75);
    teamBSite2Pb->setRange(0, 100); teamBSite2Pb->setValue(45);
    teamASite2Pb->setFixedWidth(100);
    teamBSite2Pb->setFixedWidth(100);
    teamASite2Pb->setStyleSheet("QProgressBar::chunk { background: #3498db; }");
    teamBSite2Pb->setStyleSheet("QProgressBar::chunk { background: #e74c3c; }");

    // Progress Bar Layout (top center)
    progressBarContainer = new QWidget(mainGamePage);
    // progressBarContainer->setStyleSheet("background-color:#662539");
    QVBoxLayout* progressLayout = new QVBoxLayout(progressBarContainer);

    QHBoxLayout *progressSite1Layout = new QHBoxLayout;
    QSpacerItem *spacerItem1 = new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Fixed);
    QSpacerItem *spacerItem2 = new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Fixed);
    progressSite1Layout->addSpacerItem(spacerItem1);
    progressSite1Layout->addWidget(teamAlb, 0, Qt::AlignHCenter);
    progressSite1Layout->addWidget(teamAPb, 0, Qt::AlignHCenter);
    progressSite1Layout->addWidget(teamBlb, 0, Qt::AlignHCenter);
    progressSite1Layout->addWidget(teamBPb, 0, Qt::AlignHCenter);
    progressSite1Layout->addSpacerItem(spacerItem2);
    progressSite1Layout->setContentsMargins(0, 0, 0, 0);


    QHBoxLayout *progressSite2Layout = new QHBoxLayout;
    QSpacerItem *spacerItem1Site2 = new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Fixed);
    QSpacerItem *spacerItem2Site2 = new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Fixed);
    progressSite2Layout->addSpacerItem(spacerItem1Site2);
    progressSite2Layout->addWidget(teamASite2lb, 0, Qt::AlignHCenter);
    progressSite2Layout->addWidget(teamASite2Pb, 0, Qt::AlignHCenter);
    progressSite2Layout->addWidget(teamBSite2lb, 0, Qt::AlignHCenter);
    progressSite2Layout->addWidget(teamBSite2Pb, 0, Qt::AlignHCenter);
    progressSite2Layout->addSpacerItem(spacerItem2Site2);
    progressSite2Layout->setContentsMargins(0, 0, 0, 0);

    progressLayout->addLayout(progressSite1Layout);
    progressLayout->addLayout(progressSite2Layout);

    progressBarContainer->setGeometry(QRect(0,0,this->screen()->availableGeometry().width(),100));
    progressBarContainer->raise();
    progressBarContainer->hide();


    // respawn in domination timer
    respawnTimer = new QTimer;
    respawnTimer->setInterval(5000);
    respawnTimer->setSingleShot(true);
    connect(respawnTimer,&QTimer::timeout,this,&MainWindow::respawnTimeOutSlot);


    connect(communicationChannel,&CommunicationChannel::serverDisconnectedSignal,this,&MainWindow::serverDisconnectedSlot);

    connect(mainGamePage,&MainGamePage::openCloseItemStoreSignal,this,&MainWindow::openCloseItemStoreSlot);

    connect(&MiddleWare::getInstance(),&MiddleWare::setCurrentPageSignal,this,&MainWindow::setCurrentPageSlot);
    connect(&ProcessThreadClass::getInstance(),&ProcessThreadClass::ackMessageSignal,this,&MainWindow::ackMessageSlot);
    connect(&ProcessThreadClass::getInstance(),&ProcessThreadClass::updatedRealPlayerSignal,this,&MainWindow::updatedRealPlayerSlot);
    connect(&ProcessThreadClass::getInstance(),&ProcessThreadClass::goToAgentSelectionPageSignal,this,&MainWindow::goToAgentSelectionPageSlot);
    connect(&ProcessThreadClass::getInstance(),&ProcessThreadClass::insertOnePlayerToAllGamePlayerSignal,this,&MainWindow::insertOnePlayerToAllGamePlayerSlot);

    connect(&ProcessThreadClass::getInstance(),&ProcessThreadClass::updateGamePlayerSignal,this,&MainWindow::updateGamePlayerSlot);
    connect(&ProcessThreadClass::getInstance(),&ProcessThreadClass::updateGamePlayerPositionSignal,this,&MainWindow::updateGamePlayerPositionSlot);
    connect(&ProcessThreadClass::getInstance(),&ProcessThreadClass::updateGamePlayerHeadRotationSignal,this,&MainWindow::updateGamePlayerHeadRotationSlot);
    connect(&ProcessThreadClass::getInstance(),&ProcessThreadClass::updateBulletInfoSignal,this,&MainWindow::updateBulletInfoSlot);
    connect(&ProcessThreadClass::getInstance(),&ProcessThreadClass::updateBulletHitPlayerSignal,this,&MainWindow::updateBulletHitPlayerSlot);
    connect(&ProcessThreadClass::getInstance(),&ProcessThreadClass::updateGunSelectedByPlayerSignal,this,&MainWindow::updateGunSelectedByPlayerSlot);
    connect(&ProcessThreadClass::getInstance(),&ProcessThreadClass::updateDominationScoreSignal,this,&MainWindow::updateDominationScoreSlot);
    connect(&ProcessThreadClass::getInstance(),&ProcessThreadClass::setHealthOfPlayerSignal,this,&MainWindow::setHealthOfPlayerSlot);


    connect(itemStorePage,&ItemStorePage::buyEAbilitYFromStoreSignal,this,&MainWindow::buyEAbilitYFromStoreSlot);


    // connect(collisionDetectionObj,&CollisionDetectionClass::bulletHitsTheCurrentPlayerSignal,this,&MainWindow::bulletHitsTheCurrentPlayerSlot);

}

MainWindow::~MainWindow()
{
    DataStore::getInstance().applicationClose = true;
    ProcessThreadClass::getInstance().wait();
    ProcessThreadClass::getInstance().deleteLater();

    delete ui;
}



void MainWindow::setCurrentPageSlot(int pageNo)
{
    if(pageNo == 2)
    {
        STRUCT_REQ msg;
        msg.msgHeader.messageId = D_S_PLAYER_INFO_REQ;
        msg.msgHeader.messageLen = 0;
        msg.msgHeader.userId = DataStore::getInstance().getRealPlayer()->getId();

        QByteArray data;
        data.resize(sizeof(msg));
        memcpy(data.data(),&msg,sizeof(msg));

        CommunicationChannel::getInstance().sendDataToServer(data);
    }
    else if(pageNo == 3)
    {
        agentSelectionPage->startAgentSelectionTimer();
        agentSelectionPage->updateAllPlayerDetail();
    }
    else if(pageNo == 4)
    {
        for(int i=0;i<DataStore::getInstance().getMaxPlayersCount();i++)
        {
            if(DataStore::getInstance().allGamePlayers[i]->player()->getId() == DataStore::getInstance().getRealPlayer()->getId())
            {
                DataStore::getInstance().setGamePlayer(DataStore::getInstance().allGamePlayers[i]);
                mainGamePage->connectCurrentPlayer();

                if(DataStore::getInstance().getGameMode() == GAME_MODE_DOMINATION)
                {
                    progressBarContainer->show();

                }
                else
                {
                    progressBarContainer->hide();
                }

                break;
            }
        }
        mainGamePage->loadGame();
    }

    stackWidget->setCurrentIndex(pageNo);

    // post setting
    if(pageNo == 4)
    {
        if(DataStore::getInstance().getGamePlayer()->getAgent() && DataStore::getInstance().getGamePlayer()->getAgent()->getEAbility()){
            itemStorePage->eAbilityName->setText(DataStore::getInstance().getGamePlayer()->getAgent()->getEAbility()->abilityName());
            itemStorePage->eAbilityDesc->setText(DataStore::getInstance().getGamePlayer()->getAgent()->getEAbility()->abilityDesc());
        }

        mainGamePage->mainGamePreOpenConfiguration();
    }


}

void MainWindow::ackMessageSlot(STRUCT_ACK ack)
{
    switch(ack.status)
    {
    case USER_ALREADY_EXIST:
    {
        QMessageBox::information(this,"USER_ALREADY_EXIST","USER_ALREADY_EXIST");
    }
    break;
    case USER_SUCCESSFUL_SIGNUP:
    {
        QMessageBox::information(this,"USER_SUCCESSFUL_SIGNUP","USER_SUCCESSFUL_SIGNUP");
        emit MiddleWare::getInstance().setCurrentPageSignal(0);
    }
    break;
    case USER_SUCCESSFUL_LOGIN:
    {
        // QMessageBox::information(this,"USER_SUCCESSFUL_LOGIN","USER_SUCCESSFUL_LOGIN");
        DataStore::getInstance().getRealPlayer()->setId(ack.msgHeader.userId);
        emit MiddleWare::getInstance().setCurrentPageSignal(2);
    }
    break;
    case USER_NOT_FOUND:
    {
        QMessageBox::information(this,"USER_NOT_FOUND","USER_NOT_FOUND");
    }
    break;
    case INVALID_CREDENTIAL:
    {
        QMessageBox::information(this,"INVALID_CREDENTIAL","INVALID_CREDENTIAL");
    }
    break;
    case CONTINUE_GAME:
    {
        emit MiddleWare::getInstance().setCurrentPageSignal(4);
    }
    break;
    case PLAYER_LIMIT_EXCEED:
    {
        QMessageBox::information(this,"PLAYER_LIMIT_EXCEED","PLAYER_LIMIT_EXCEED");
        emit MiddleWare::getInstance().setCurrentPageSignal(0);
    }
    break;
    case PLAYER_COUNT:
    {
        DataStore::getInstance().setMaxPlayersCount(ack.value);
        //testing
        if(ack.value ==1)
            agentSelectionPage->timeleft = 1;
        //
        qDebug()<<"Player counts : "<<ack.value;
    }
    break;
    case START_THE_GAME:
    {
        emit MiddleWare::getInstance().setCurrentPageSignal(4);
    }
    break;
    }
}

void MainWindow::updatedRealPlayerSlot()
{
    connectToServerPage->setPlayerName(DataStore::getInstance().getRealPlayer()->getName());
    connectToServerPage->setPlayerXP(DataStore::getInstance().getRealPlayer()->getRankXp());

}

void MainWindow::goToAgentSelectionPageSlot()
{
    setCurrentPageSlot(3);
}

void MainWindow::insertOnePlayerToAllGamePlayerSlot(STRUCT_PLAYER_CONNECTED data)
{
    DataStore::getInstance().insertOnePlayerToAllGamePlayer(data.pas);
}

void MainWindow::updateGamePlayerSlot()
{
    agentSelectionPage->updateAllPlayerDetail();
}

void MainWindow::updateGamePlayerPositionSlot(STRUCT_POSITION_MSG data)
{
    DataStore::getInstance().updatePlayerPosition(data);
}

void MainWindow::updateGamePlayerHeadRotationSlot(STRUCT_HEAD_ROTATION_MSG data)
{
    DataStore::getInstance().updatePlayerHeadRotation(data);

}

void MainWindow::updateBulletInfoSlot(STRUCT_BULLET_INFO_MSG data, bool hitThePlayer)
{
    int uqno = data.bullet_info.uniqueNo;
    int userId = data.bullet_info.playerId;
    QPair<int,int> bullet_key = {uqno,userId};



    if(DataStore::getInstance().bulletInfoMap.contains(bullet_key))
    {
        if(data.bullet_info.destroyed == true)
        {
            mainGamePage->removeBullet(DataStore::getInstance().bulletInfoMap[bullet_key]);
            DataStore::getInstance().bulletInfoMap[bullet_key]->deleteLater();
            DataStore::getInstance().bulletInfoMap.remove(bullet_key);
            if(DataStore::getInstance().getGamePlayer()->player()->getId() == userId)
                SpecialUtils::getInstance().freeId(uqno);
        }
        else
        {
            DataStore::getInstance().bulletInfoMap[bullet_key]->setPosX(data.bullet_info.posX);
            DataStore::getInstance().bulletInfoMap[bullet_key]->setPosY(data.bullet_info.posY);

            if(hitThePlayer)
            {
                bulletHitsTheCurrentPlayerSlot(DataStore::getInstance().bulletInfoMap[bullet_key]);
            }


        }
    }
    else
    {
        if(data.bullet_info.destroyed == true)
        {
            if(DataStore::getInstance().getGamePlayer()->player()->getId() == userId)
                SpecialUtils::getInstance().freeId(uqno);
        }
        else
        {

            BulletInterface *bullet = BulletFactoryClass::createBullet(data.bullet_info.bulletId);
            bullet->setUniqueNo(data.bullet_info.uniqueNo);
            bullet->setStartPosX(data.bullet_info.startPosX);
            bullet->setStartPoxY(data.bullet_info.startPosY);
            bullet->setPosX(data.bullet_info.posX);
            bullet->setPosY(data.bullet_info.posY);
            bullet->setAngle(data.bullet_info.angle);
            bullet->setGamePlayerId(data.bullet_info.playerId);
            bullet->setGunId(data.bullet_info.gunId);
            DataStore::getInstance().bulletInfoMap[bullet_key]= bullet;
            mainGamePage->addBullet(bullet);



            if(bullet->getGamePlayerId() != DataStore::getInstance().getGamePlayer()->player()->getId())
            {
                int ithPlayer = DataStore::getInstance().playerIdToIMap[bullet->getGamePlayerId()];
                if(DataStore::getInstance().getGameMode() == GAME_MODE_DOMINATION && DataStore::getInstance().allGamePlayers[ithPlayer]->getTeam() != DataStore::getInstance().getGamePlayer()->getTeam())
                {
                    // check bullet hit one time
                    double checkX = data.bullet_info.posX + bullet->boundingRect().width()/2;
                    double checkY = data.bullet_info.posY + bullet->boundingRect().height()/2;
                    QRectF rectf = QRectF(DataStore::getInstance().getGamePlayer()->getPositionX(),DataStore::getInstance().getGamePlayer()->getPositionY(),DataStore::getInstance().getGamePlayer()->boundingRect().width(),DataStore::getInstance().getGamePlayer()->boundingRect().height());

                    if(rectf.contains(QPointF(checkX,checkY)))
                    {
                        bulletHitsTheCurrentPlayerSlot(DataStore::getInstance().bulletInfoMap[bullet_key]);
                    }
                }
            }
        }
    }

    // visibility check (as bullet updated do not need to check it on any ability)
    if(DataStore::getInstance().bulletInfoMap.contains(bullet_key))
    {
        if(DataStore::getInstance().getGamePlayer()->player()->getId() == DataStore::getInstance().bulletInfoMap[bullet_key]->getGamePlayerId())
        {

        }
        else
        {
            QRectF itemRect(DataStore::getInstance().bulletInfoMap[bullet_key]->getPosX(),DataStore::getInstance().bulletInfoMap[bullet_key]->getPosY(),DataStore::getInstance().bulletInfoMap[bullet_key]->boundingRect().width(),DataStore::getInstance().bulletInfoMap[bullet_key]->boundingRect().height());

            if(DataStore::getInstance().getGamePlayer()->checkItemInEyeSightRange(itemRect)){
                DataStore::getInstance().bulletInfoMap[bullet_key]->setVisibleToPlayer(true);
            }
            else
            {
                DataStore::getInstance().bulletInfoMap[bullet_key]->setVisibleToPlayer(false);
            }

        }
    }

}

void MainWindow::updateBulletHitPlayerSlot(STRUCT_BULLET_INFO_MSG data){

    // destroy bullet

    int uqno = data.bullet_info.uniqueNo;
    int userId = data.bullet_info.playerId;
    QPair<int,int> bullet_key = {uqno,userId};
    if(DataStore::getInstance().bulletInfoMap.contains(bullet_key))
    {


        // reduce health
        int i = DataStore::getInstance().playerIdToIMap[data.msgHeader.userId];
        DataStore::getInstance().allGamePlayers[i]->reducePlayerHealth(DataStore::getInstance().bulletInfoMap[bullet_key]->getDamage());

        // remove bullet
        mainGamePage->removeBullet(DataStore::getInstance().bulletInfoMap[bullet_key]);
        DataStore::getInstance().bulletInfoMap[bullet_key]->deleteLater();
        DataStore::getInstance().bulletInfoMap.remove(bullet_key);
        if(DataStore::getInstance().getGamePlayer()->player()->getId() == userId)
            SpecialUtils::getInstance().freeId(uqno);

        // respawn in domination
        if(DataStore::getInstance().getGameMode() == GAME_MODE_DOMINATION && DataStore::getInstance().getGamePlayer()->player()->getId() == data.msgHeader.userId && DataStore::getInstance().getGamePlayer()->getHealth() == 0){

            MiddleWare::getInstance().sendResetPlayerPositionMsg();
            respawnTimer->start();
        }

    }


}

void MainWindow::updateGunSelectedByPlayerSlot(STRUCT_GUN_SELECTED data)
{
    itemStorePage->gunSelectionOfPlayer(data);
}

void MainWindow::updateDominationScoreSlot(STRUCT_DOMINATION_SCORE_MSG data)
{
    teamAPb->setValue(data.scoreAA);
    teamBPb->setValue(data.scoreAB);
    teamASite2Pb->setValue(data.scoreBA);
    teamBSite2Pb->setValue(data.scoreBB);



}
void MainWindow::bulletHitsTheCurrentPlayerSlot(BulletInterface *bullet)
{
    STRUCT_BULLET_INFO bullet_info;
    bullet_info.uniqueNo = bullet->getUniqueNo();
    bullet_info.bulletId = bullet->getBulletId();
    bullet_info.startPosX = bullet->getStartPosX();
    bullet_info.startPosY = bullet->getStartPoxY();
    bullet_info.posX = bullet->getPosX();
    bullet_info.posY = bullet->getPosY();
    bullet_info.angle = bullet->getAngle();
    bullet_info.playerId = bullet->getGamePlayerId();
    bullet_info.gunId = bullet->getGunId();
    MiddleWare::getInstance().sendBulletHitThePlayerMsg(bullet_info);
}

void MainWindow::serverDisconnectedSlot()
{
    QMessageBox::critical(this,"CONNECTION FAILED","UNABLE TO CONNECT WITH SERVER");
    setCurrentPageSlot(0);
}

void MainWindow::openCloseItemStoreSlot()
{
    if(itemStorePage->isVisible())
    {
        itemStorePage->hide();
    }
    else{
        itemStorePage->show();
    }
}

void MainWindow::setHealthOfPlayerSlot(STRUCT_SET_HEALTH_OF_PLAYER_MSG data)
{
    int index = DataStore::getInstance().playerIdToIMap[data.msgHeader.userId];
    DataStore::getInstance().allGamePlayers[index]->setHealth(data.health);
    DataStore::getInstance().allGamePlayers[index]->setShield(data.shield);
}

void MainWindow::buyEAbilitYFromStoreSlot()
{
    if(DataStore::getInstance().getGamePlayer()->getAgent() && DataStore::getInstance().getGamePlayer()->getAgent()->getEAbility())
    {
        DataStore::getInstance().getGamePlayer()->getAgent()->getEAbility()->incAbilityLeftCount();
        mainGamePage->eAbilityBuy();
    }

}

void MainWindow::on_pbClose_clicked()
{
    QApplication::exit(0);

}

void MainWindow::respawnTimeOutSlot()
{
    STRUCT_SET_HEALTH_OF_PLAYER_MSG data;
    data.health = DataStore::getInstance().getGamePlayer()->getDefaultHealth();
    data.shield = DataStore::getInstance().getGamePlayer()->getDefaultShield();
    MiddleWare::getInstance().sendSetHealthMsg(data);

}

