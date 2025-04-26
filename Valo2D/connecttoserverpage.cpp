#include "connecttoserverpage.h"
#include "ui_connecttoserverpage.h"
#include "middleware.h"
#include "structures.h"
#include "messages.h"
#include "GlobalConstant.h"
#include "datastore.h"
#include "communicationchannel.h"

ConnectToServerPage::ConnectToServerPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ConnectToServerPage)
{
    ui->setupUi(this);
    ui->teamComboBox->addItem("Team A");
    ui->teamComboBox->addItem("Team B");
}

ConnectToServerPage::~ConnectToServerPage()
{
    delete ui;
}

void ConnectToServerPage::setPlayerName(QString playerName)
{
    ui->playerName->setText(playerName);
}

void ConnectToServerPage::setPlayerXP(int rankXp)
{
    ui->rankXp->setText(QString::number(rankXp));
}

void ConnectToServerPage::on_playBtn_clicked()
{

    STRUCT_REQ msg;
    msg.msgHeader.messageId = D_S_PLAY_REQ;
    msg.msgHeader.messageLen = 0;
    msg.msgHeader.userId = DataStore::getInstance().getRealPlayer()->getId();

    QByteArray data;
    data.resize(sizeof(msg));
    memcpy(data.data(),&msg,sizeof(msg));

    CommunicationChannel::getInstance().sendDataToServer(data);

    emit MiddleWare::getInstance().setCurrentPageSignal(5);

}


void ConnectToServerPage::on_playDominationBtn_clicked()
{
    DataStore::getInstance().setGameMode(GAME_MODE_DOMINATION);
    STRUCT_REQ msg;
    msg.msgHeader.messageId = D_S_PLAY_DOMINATION_REQ;
    msg.msgHeader.messageLen = 0;
    msg.msgHeader.userId = DataStore::getInstance().getRealPlayer()->getId();

    msg.req_val = ui->teamComboBox->currentIndex()+1;
    QByteArray data;
    data.resize(sizeof(msg));
    memcpy(data.data(),&msg,sizeof(msg));

    CommunicationChannel::getInstance().sendDataToServer(data);
    emit MiddleWare::getInstance().setCurrentPageSignal(5);
}

