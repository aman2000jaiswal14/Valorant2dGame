#include "loginpage.h"
#include "ui_loginpage.h"
#include "middleware.h"
#include "structures.h"
#include "GlobalConstant.h"
#include "messages.h"
#include "communicationchannel.h"
LoginPage::LoginPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);
}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::on_loginBtn_clicked()
{
    STRUCT_PLAYER_LOGIN msg;
    msg.msgHeader.messageId = D_S_LOGIN;
    msg.msgHeader.messageLen = sizeof(msg) - sizeof(msg.msgHeader);

    QString username = ui->username->text();
    QString password = ui->password->text();


    memcpy(msg.username,username.toStdString().c_str(),sizeof(msg.username));
    memcpy(msg.password,password.toStdString().c_str(),sizeof(msg.password));

    QByteArray data;
    data.resize(sizeof(msg));
    memcpy(data.data(),&msg,sizeof(msg));

    CommunicationChannel::getInstance().sendDataToServer(data);
}


void LoginPage::on_signupBtn_clicked()
{
    emit MiddleWare::getInstance().setCurrentPageSignal(1);
}

