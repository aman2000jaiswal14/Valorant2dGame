#include "signuppage.h"
#include "ui_signuppage.h"
#include "middleware.h"
#include "structures.h"
#include "GlobalConstant.h"
#include "communicationchannel.h"
#include "messages.h"

SignupPage::SignupPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignupPage)
{
    ui->setupUi(this);
}

SignupPage::~SignupPage()
{
    delete ui;
}

void SignupPage::on_signupBtn_clicked()
{

    STRUCT_PLAYER_SINGUP msg;
    msg.msgHeader.messageId = D_S_SIGNUP;
    msg.msgHeader.messageLen = sizeof(msg) - sizeof(msg.msgHeader);
    QString name = ui->name->text();
    QString username = ui->username->text();
    QString password = ui->password->text();

    memcpy(msg.name,name.toStdString().c_str(),sizeof(msg.name));
    memcpy(msg.username,username.toStdString().c_str(),sizeof(msg.username));
    memcpy(msg.password,password.toStdString().c_str(),sizeof(msg.password));

    QByteArray data;
    data.resize(sizeof(msg));
    memcpy(data.data(),&msg,sizeof(msg));

    CommunicationChannel::getInstance().sendDataToServer(data);


}


void SignupPage::on_backBtn_clicked()
{
    emit MiddleWare::getInstance().setCurrentPageSignal(0);
}

