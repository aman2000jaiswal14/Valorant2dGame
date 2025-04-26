#ifndef MAP2_H
#define MAP2_H

#include "mapinterface.h"
#include "QGraphicsRectItem"
#include "datastore.h"
#include <QObject>
#include <communicationchannel.h>
#include <messages.h>
#include <GlobalConstant.h>
class Map2 : public MapInterFace
{
    Q_OBJECT
    QTimer *siteATimer;
    QTimer *siteBTimer;
public:
    Map2();

    // MapInterFace interface
public:
    void loadMap();
    int getMapId();

private:
    QGraphicsRectItem mainBoundingRectangle;
    QGraphicsRectItem outSideBoundingRectangle;
    QGraphicsRectItem walls[14];
    QGraphicsRectItem siteARectangle;
    QGraphicsRectItem siteBRectangle;
    QGraphicsTextItem siteAText;
    QGraphicsTextItem siteBText;


    // MapInterFace interface
public:
    bool isPositionValid(QPointF pos);
    void siteATimerTimeOutSlot();
    void siteBTimerTimeOutSlot();

};

#endif // MAP2_H
