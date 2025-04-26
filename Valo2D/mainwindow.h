#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QDebug>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "datastore.h"
#include "middleware.h"
#include "structures.h"
#include "GlobalConstant.h"
#include <QMessageBox>
#include <collisiondetectionclass.h>
#include <QProgressBar>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class CommunicationChannel;
class LoginPage;
class SignupPage;
class ConnectToServerPage;
class AgentSelectionPage;
class MainGamePage;
class WaitingPage;
class BulletInterface;
class SpecialUtils;
class ItemStorePage;
class MainWindow : public QMainWindow
{
    Q_OBJECT


    QTimer *respawnTimer;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    CommunicationChannel *communicationChannel;
    CollisionDetectionClass *collisionDetectionObj;
    QWidget* progressBarContainer;
    QProgressBar* teamAPb;
    QProgressBar* teamBPb;
    QProgressBar* teamASite2Pb;
    QProgressBar* teamBSite2Pb;


    QStackedWidget *stackWidget;
    LoginPage *loginPage;
    SignupPage *signUpPage;
    ConnectToServerPage *connectToServerPage;
    AgentSelectionPage *agentSelectionPage;
    MainGamePage *mainGamePage;
    WaitingPage *waitingPage;
    ItemStorePage *itemStorePage;
public slots:
    void setCurrentPageSlot(int pageNo);
    void ackMessageSlot(STRUCT_ACK ack);
    void updatedRealPlayerSlot();
    void goToAgentSelectionPageSlot();
    void insertOnePlayerToAllGamePlayerSlot(STRUCT_PLAYER_CONNECTED data);
    void updateGamePlayerSlot();
    void updateGamePlayerPositionSlot(STRUCT_POSITION_MSG data);
    void updateGamePlayerHeadRotationSlot(STRUCT_HEAD_ROTATION_MSG data);
    void updateBulletInfoSlot(STRUCT_BULLET_INFO_MSG data,bool hitThePlayer);
    void updateBulletHitPlayerSlot(STRUCT_BULLET_INFO_MSG data);
    void updateGunSelectedByPlayerSlot(STRUCT_GUN_SELECTED data);
    void updateDominationScoreSlot(STRUCT_DOMINATION_SCORE_MSG data);
    void bulletHitsTheCurrentPlayerSlot(BulletInterface *bullet);
    void serverDisconnectedSlot();
    void openCloseItemStoreSlot();
    void setHealthOfPlayerSlot(STRUCT_SET_HEALTH_OF_PLAYER_MSG data);
    void buyEAbilitYFromStoreSlot();

private slots:
    void on_pbClose_clicked();
    void respawnTimeOutSlot();


};
#endif // MAINWINDOW_H
