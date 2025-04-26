#include "itemstorepage.h"
#include "ui_itemstorepage.h"
#include "gunfactoryclass.h"
ItemStorePage::ItemStorePage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ItemStorePage)
{
    ui->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint);
    // setWindowFlag(Qt::SubWindow);
    gunFrame = new QFrame;
    ui->verticalLayout->addWidget(gunFrame);
    gunFrameLayout = new QGridLayout;

    gunFrame->setLayout(gunFrameLayout);

    // gun1
    gun1Frame = new QFrame;
    gun1Frame->setStyleSheet("QFrame {border : 1px solid black;}");
    gun1Frame->setMaximumSize(QSize(150,150));
    gun1FrameLayout = new QGridLayout;
    gun1Frame->setLayout(gun1FrameLayout);

    Gun1 tgun1;
    gun1Name = new QLabel;
    gun1Name->setText(tgun1.getName());
    gun1Desc = new QLabel;
    gun1Desc->setText(tgun1.getDesc());
    gun1Button = new QPushButton("Select");

    gun1FrameLayout->addWidget(gun1Name,0,0);
    gun1FrameLayout->addWidget(gun1Desc,1,0);
    gun1FrameLayout->addWidget(gun1Button,2,0);

    gunFrameLayout->addWidget(gun1Frame,0,0);



    // gun 2
    gun2Frame = new QFrame;
    gun2Frame->setStyleSheet("QFrame {border : 1px solid black;}");
    gun2Frame->setMaximumSize(QSize(150,150));
    gun2FrameLayout = new QGridLayout;
    gun2Frame->setLayout(gun2FrameLayout);

    Gun2 tgun2;
    gun2Name = new QLabel;
    gun2Name->setText(tgun2.getName());
    gun2Desc = new QLabel;
    gun2Desc->setText(tgun2.getDesc());
    gun2Button = new QPushButton("Select");

    gun2FrameLayout->addWidget(gun2Name,0,0);
    gun2FrameLayout->addWidget(gun2Desc,1,0);
    gun2FrameLayout->addWidget(gun2Button,2,0);

    gunFrameLayout->addWidget(gun2Frame,0,1);

    //
    eAbilityFrame = new QFrame;
    eAbilityFrame->setStyleSheet("QFrame {border : 1px solid black;}");
    eAbilityFrame->setMaximumSize(QSize(150,150));
    eAbilityFrameLayout = new QGridLayout;
    eAbilityFrame->setLayout(eAbilityFrameLayout);


    eAbilityName = new QLabel;
    eAbilityName->setText("E Ability");
    eAbilityDesc = new QLabel;
    eAbilityDesc->setText("E Ability");
    eAbilityButton = new QPushButton("+1");

    eAbilityFrameLayout->addWidget(eAbilityName,0,0);
    eAbilityFrameLayout->addWidget(eAbilityDesc,1,0);
    eAbilityFrameLayout->addWidget(eAbilityButton,2,0);

    gunFrameLayout->addWidget(eAbilityFrame,0,2);
    //

    // redundant
    for(int i=3;i<9;i++)
    {
        redundantFrame[i] = new QFrame;
        redundantFrame[i]->setStyleSheet("QFrame{border : 1px solid black}");
        redundantFrame[i]->setMaximumSize(QSize(150,150));
        gunFrameLayout->addWidget(redundantFrame[i],(i)/3,i%3);
    }

    connect(gun1Button,&QPushButton::clicked,this,&ItemStorePage::gun1ButtonClickedSlot);
    connect(gun2Button,&QPushButton::clicked,this,&ItemStorePage::gun2ButtonClickedSlot);
    connect(eAbilityButton,&QPushButton::clicked,this,&ItemStorePage::eAbilityButtonClickedSlot);

}

ItemStorePage::~ItemStorePage()
{
    delete ui;
}

void ItemStorePage::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_B)
    {
        this->hide();
    }
    QDialog::keyPressEvent(event);
}

void ItemStorePage::gunSelectionOfPlayer(STRUCT_GUN_SELECTED data)
{
    for(int i=0;i<DataStore::getInstance().getMaxPlayersCount();i++)
    {
        if(DataStore::getInstance().allGamePlayers[i]->player()->getId() == data.msgHeader.userId)
        {
            GunInterface* prevGun = DataStore::getInstance().allGamePlayers[i]->getGun();
            GunInterface *currentGun = GunFactoryClass::createGun(data.gunId);


            DataStore::getInstance().allGamePlayers[i]->setGun(currentGun);
            if(prevGun)
                prevGun->deleteLater();

            break;

        }

    }
}

void ItemStorePage::gun1ButtonClickedSlot()
{
    MiddleWare::getInstance().sendGunChangeMsg(1);
}

void ItemStorePage::gun2ButtonClickedSlot()
{
    MiddleWare::getInstance().sendGunChangeMsg(2);
}

void ItemStorePage::eAbilityButtonClickedSlot()
{
    emit buyEAbilitYFromStoreSignal();
}
