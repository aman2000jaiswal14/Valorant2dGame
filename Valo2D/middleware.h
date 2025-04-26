#ifndef MIDDLEWARE_H
#define MIDDLEWARE_H

#include <QObject>
#include "communicationchannel.h"
#include "structures.h"
#include "messages.h"
#include "GlobalConstant.h"
#include "datastore.h"


class MiddleWare : public QObject
{
    Q_OBJECT
public:
    static MiddleWare& getInstance();

private:
    MiddleWare();


public:
    void sendPlayerPositionMsg(STRUCT_PLAYER_POSITION pos);
    void sendHeadRotationMsg(double rotation);
    void sendBulletInfoMsg(STRUCT_BULLET_INFO bullet_info);
    void sendBulletHitThePlayerMsg(STRUCT_BULLET_INFO bullet_info);
    void sendGunChangeMsg(int gunId);
    void sendResetPlayerPositionMsg();
    void sendSetHealthMsg(STRUCT_SET_HEALTH_OF_PLAYER_MSG healthMsg);


signals:
    void setCurrentPageSignal(int pageNo);

};

#endif // MIDDLEWARE_H
