#include "waitingpage.h"
#include "ui_waitingpage.h"

WaitingPage::WaitingPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WaitingPage)
{
    ui->setupUi(this);
}

WaitingPage::~WaitingPage()
{
    delete ui;
}
