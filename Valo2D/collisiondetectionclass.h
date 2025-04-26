#ifndef COLLISIONDETECTIONCLASS_H
#define COLLISIONDETECTIONCLASS_H

#include <QObject>
#include <QThread>
#include <QGraphicsItem>
#include <bulletinterface.h>
#include "datastore.h"

class CollisionDetectionClass : public QThread
{
    Q_OBJECT
public:
    CollisionDetectionClass();
    void run();

signals:
    void bulletHitsTheCurrentPlayerSignal(BulletInterface *);
};

#endif // COLLISIONDETECTIONCLASS_H
