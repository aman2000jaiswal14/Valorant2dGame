#include "agentselectionpage.h"
#include "ui_agentselectionpage.h"
#include <QThread>
AgentSelectionPage::AgentSelectionPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AgentSelectionPage)
{
    ui->setupUi(this);



    mGridLayout = new QGridLayout;
    ui->frame_pamain->setLayout(mGridLayout);
    for(int i=0;i<MAX_LIMIT_OF_PLAYER;i++)
    {
        mFrame[i] = new QFrame;
        mGridLayoutChild[i] = new QGridLayout;
        playerNameLabel[i] = new QLabel;
        playerNameLabel[i]->setText(QString("P%1").arg(i));
        playerAgentLabel[i] = new QLabel;
        playerAgentLabel[i]->setText(QString("--"));
        playerTeamLabel[i] = new QLabel;
        playerTeamLabel[i]->setText("");


        mFrame[i]->setLayout(mGridLayoutChild[i]);
        mGridLayoutChild[i]->addWidget(playerNameLabel[i],0,0);
        mGridLayoutChild[i]->addWidget(playerTeamLabel[i],0,1);
        mGridLayoutChild[i]->addWidget(playerAgentLabel[i],0,2);

        if(i%2 == 0)
        {
            mGridLayout->addWidget(mFrame[i],i/2,0);
        }
        else
        {
            mGridLayout->addWidget(mFrame[i],i/2,1);
        }

        mFrame[i]->setVisible(false);
    }

    ui->timeLeft->setText(QString::number(timeleft));
    agentSelectionTimer = new QTimer;
    agentSelectionTimer->setInterval(1000);

    connect(agentSelectionTimer,&QTimer::timeout,this,&AgentSelectionPage::agentSelectionTimerPerSecondSlot);

}

AgentSelectionPage::~AgentSelectionPage()
{
    delete ui;
}

void AgentSelectionPage::startAgentSelectionTimer()
{
    agentSelectionTimer->start();
}

void AgentSelectionPage::updateAllPlayerDetail()
{
    for(int i=0;i< DataStore::getInstance().getMaxPlayersCount();i++)
    {
        mFrame[i]->setVisible(true);
        if(DataStore::getInstance().allGamePlayers[i]->player()!=NULL)
        {
            playerNameLabel[i]->setText(DataStore::getInstance().allGamePlayers[i]->player()->getName());
            if(DataStore::getInstance().allGamePlayers[i]->getAgent() != NULL)
            {
                playerAgentLabel[i]->setText(DataStore::getInstance().allGamePlayers[i]->getAgent()->getAgentName());
            }
            if(DataStore::getInstance().allGamePlayers[i]->getTeam() == 1)
            {
                playerTeamLabel[i]->setText("TEAM A");
            }
            else if(DataStore::getInstance().allGamePlayers[i]->getTeam() == 2)
            {
                playerTeamLabel[i]->setText("TEAM B");
            }

        }
    }

}

void AgentSelectionPage::on_agent1_clicked()
{
    ui->agent1->setDisabled(true);
    ui->agent2->setDisabled(true);
    ui->agent3->setDisabled(true);
    STRUCT_AGENT_SELECTED msg;
    msg.msgHeader.messageId = D_S_AGENT_SELECTED;
    msg.msgHeader.messageLen = sizeof(msg)-sizeof(msg.msgHeader);
    msg.msgHeader.userId = DataStore::getInstance().getRealPlayer()->getId();
    msg.agentid = 1;

    QByteArray data;
    data.resize(sizeof(msg));
    memcpy(data.data(),&msg,sizeof(msg));

    CommunicationChannel::getInstance().sendDataToServer(data);
}



void AgentSelectionPage::agentSelectionTimerPerSecondSlot()
{
    if(timeleft==0)
    {
        agentSelectionTimer->stop();

        STRUCT_REQ msg;
        msg.msgHeader.messageId = D_S_START_THE_GAME;
        msg.msgHeader.messageLen = 0;
        msg.msgHeader.userId = DataStore::getInstance().getRealPlayer()->getId();

        QByteArray data;
        data.resize(sizeof(msg));
        memcpy(data.data(),&msg,sizeof(msg));

        CommunicationChannel::getInstance().sendDataToServer(data);
        return;

    }
    timeleft--;
    ui->timeLeft->setText(QString::number(timeleft));
}


void AgentSelectionPage::on_agent2_clicked()
{
    ui->agent1->setDisabled(true);
    ui->agent2->setDisabled(true);
    ui->agent3->setDisabled(true);
    STRUCT_AGENT_SELECTED msg;
    msg.msgHeader.messageId = D_S_AGENT_SELECTED;
    msg.msgHeader.messageLen = sizeof(msg)-sizeof(msg.msgHeader);
    msg.msgHeader.userId = DataStore::getInstance().getRealPlayer()->getId();
    msg.agentid = 2;

    QByteArray data;
    data.resize(sizeof(msg));
    memcpy(data.data(),&msg,sizeof(msg));

    CommunicationChannel::getInstance().sendDataToServer(data);
}


void AgentSelectionPage::on_agent3_clicked()
{
    ui->agent1->setDisabled(true);
    ui->agent2->setDisabled(true);
    ui->agent3->setDisabled(true);

    STRUCT_AGENT_SELECTED msg;
    msg.msgHeader.messageId = D_S_AGENT_SELECTED;
    msg.msgHeader.messageLen = sizeof(msg)-sizeof(msg.msgHeader);
    msg.msgHeader.userId = DataStore::getInstance().getRealPlayer()->getId();
    msg.agentid = 3;

    QByteArray data;
    data.resize(sizeof(msg));
    memcpy(data.data(),&msg,sizeof(msg));

    CommunicationChannel::getInstance().sendDataToServer(data);
}


void AgentSelectionPage::on_agent4_clicked()
{
    ui->agent1->setDisabled(true);
    ui->agent2->setDisabled(true);
    ui->agent3->setDisabled(true);

    STRUCT_AGENT_SELECTED msg;
    msg.msgHeader.messageId = D_S_AGENT_SELECTED;
    msg.msgHeader.messageLen = sizeof(msg)-sizeof(msg.msgHeader);
    msg.msgHeader.userId = DataStore::getInstance().getRealPlayer()->getId();
    msg.agentid = 4;

    QByteArray data;
    data.resize(sizeof(msg));
    memcpy(data.data(),&msg,sizeof(msg));

    CommunicationChannel::getInstance().sendDataToServer(data);
}

