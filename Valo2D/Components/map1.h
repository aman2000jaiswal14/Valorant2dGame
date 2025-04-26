#ifndef MAP1_H
#define MAP1_H

#include "mapinterface.h"
#include "QGraphicsRectItem"
#include "datastore.h"
class Map1 : public MapInterFace
{
public:
    Map1();

    // MapInterFace interface
public:
    void loadMap();
    int getMapId();

private:
    QGraphicsRectItem mainBoundingRectangle;
    QGraphicsRectItem outSideBoundingRectangle;
    QGraphicsRectItem walls[3];

    // MapInterFace interface
public:
    bool isPositionValid(QPointF pos);
};

#endif // MAP1_H
