#include "map1.h"


Map1::Map1()
{
    mainBoundingRectangle.setRect(QRectF(-100, -100, 2000,1200));

    int offset = 300;
    outSideBoundingRectangle.setRect(QRectF(mainBoundingRectangle.boundingRect().topLeft().x()-offset, mainBoundingRectangle.boundingRect().topLeft().x()-offset, mainBoundingRectangle.boundingRect().width()+2*offset,mainBoundingRectangle.boundingRect().height()+2*offset));
    outSideBoundingRectangle.setBrush(QBrush(QColor(0,0,0)));

    mainBoundingRectangle.setBrush(QBrush(QColor("#CDF0F0")));
    mainBoundingRectangle.setPen(QPen(QColor(Qt::green),1));

    walls[0].setRect(QRectF(300, 300, 100,100));
    walls[0].setBrush(QBrush(QColor(Qt::gray)));


    walls[1].setRect(QRectF(800, 300, 50,500));
    walls[1].setBrush(QBrush(QColor(Qt::gray)));


    walls[2].setRect(QRectF(350, 800, 300,50));
    walls[2].setBrush(QBrush(QColor(Qt::gray)));

}

void Map1::loadMap()
{
    if(getScene()){

        for(QGraphicsItem* item : getScene()->items())
        {
            getScene()->removeItem(item);
        }
    }
        // getScene()->clear();
    else
        return;
    getScene()->setSceneRect(mainBoundingRectangle.boundingRect());
    // qDebug()<<getScene()->sceneRect();

    // getScene()->addItem(&outSideBoundingRectangle);

    getScene()->addItem(&mainBoundingRectangle);

    if(getEyesightItem())
    {
        getScene()->addItem(getEyesightItem());
    }


    for(int i=0;i<3;i++)
    {
        getScene()->addItem(&walls[i]);
    }



    for(int i=0;i<DataStore::getInstance().getMaxPlayersCount();i++)
    {
        getScene()->addItem(DataStore::getInstance().allGamePlayers[i]);

    }

    getScene()->addItem(this->getCapturePointItem());

}

int Map1::getMapId()
{
    return 1;
}

bool Map1::isPositionValid(QPointF pos)
{
    if(!mainBoundingRectangle.contains(pos))
    {
        return false;
    }
    for(int i=0;i<3;i++)
    {
        if(walls[i].boundingRect().contains(pos))
        {
            return false;
        }
    }
    return true;
}
