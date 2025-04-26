#ifndef AGENTSELECTIONPAGE_H
#define AGENTSELECTIONPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QMessageBox>
#include "middleware.h"
#include "datastore.h"
#include "communicationchannel.h"
#include "messages.h"
#include "GlobalConstant.h"
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include "datastore.h"
namespace Ui {
class AgentSelectionPage;
}

class AgentSelectionPage : public QWidget
{
    Q_OBJECT
    QTimer *agentSelectionTimer;


public:
    int timeleft = 10;
    explicit AgentSelectionPage(QWidget *parent = nullptr);
    ~AgentSelectionPage();
    void startAgentSelectionTimer();


    void setP1Detial();
    void setA1Detail();
    void setP2Detail();
    void setA2Detail();
    void updateAllPlayerDetail();

private slots:
    void on_agent1_clicked();

    void agentSelectionTimerPerSecondSlot();

    void on_agent2_clicked();

    void on_agent3_clicked();

    void on_agent4_clicked();

private:
    Ui::AgentSelectionPage *ui;
    QGridLayout *mGridLayout = nullptr;
    QFrame *mFrame[MAX_LIMIT_OF_PLAYER];
    QGridLayout *mGridLayoutChild[MAX_LIMIT_OF_PLAYER];
    QLabel *playerNameLabel[MAX_LIMIT_OF_PLAYER];
    QLabel *playerAgentLabel[MAX_LIMIT_OF_PLAYER];
    QLabel *playerTeamLabel[MAX_LIMIT_OF_PLAYER];

};

#endif // AGENTSELECTIONPAGE_H
