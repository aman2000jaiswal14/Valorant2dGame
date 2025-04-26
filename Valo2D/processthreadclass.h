#ifndef PROCESSTHREADCLASS_H
#define PROCESSTHREADCLASS_H

#include <QObject>
#include <QThread>
#include "datastore.h"
#include "structures.h"
#include "GlobalConstant.h"
#include "messages.h"
class ProcessThreadClass : public QThread
{
    Q_OBJECT
public:
    static ProcessThreadClass&  getInstance();
    void run() override;
private:
    QList<QByteArray> recvByteArrayListProcess;
    void processAckMessages(STRUCT_ACK ack);
    ProcessThreadClass();

    bool checkBulletHitThePlayer(STRUCT_BULLET_INFO_MSG data);

public:

signals:
    void ackMessageSignal(STRUCT_ACK ack);
    void updatedRealPlayerSignal();
    void goToAgentSelectionPageSignal();
    void insertOnePlayerToAllGamePlayerSignal(STRUCT_PLAYER_CONNECTED);
    void updateGamePlayerSignal();
    void updateGamePlayerPositionSignal(STRUCT_POSITION_MSG data);
    void updateGamePlayerHeadRotationSignal(STRUCT_HEAD_ROTATION_MSG data);
    void updateBulletInfoSignal(STRUCT_BULLET_INFO_MSG data, bool hitThePlayer);
    void updateBulletHitPlayerSignal(STRUCT_BULLET_INFO_MSG data);
    void updateGunSelectedByPlayerSignal(STRUCT_GUN_SELECTED data);
    void updateDominationScoreSignal(STRUCT_DOMINATION_SCORE_MSG data);
    void setHealthOfPlayerSignal(STRUCT_SET_HEALTH_OF_PLAYER_MSG);

};

#endif // PROCESSTHREADCLASS_H
