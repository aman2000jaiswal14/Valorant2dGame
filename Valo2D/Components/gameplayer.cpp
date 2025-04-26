#include "gameplayer.h"



GamePlayer::GamePlayer(PlayerInterface *player):GamePlayerInterface(player)
{
    // this->setFlag(GraphicsItemFlag::ItemIsMovable);
}

QRectF GamePlayer::boundingRect() const
{
    return QRectF(0,0,2*getHealthRadius(),2*getHealthRadius());
}

void GamePlayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();


    if(getHealth() == 0)
    {
        QPen pen = QPen(QColor(Qt::red),1);
        painter->setPen(pen);
        painter->drawEllipse(boundingRect());
        painter->drawLine(boundingRect().topLeft(),boundingRect().bottomRight());
        painter->drawLine(boundingRect().topRight(),boundingRect().bottomLeft());
    }
    else
    {
        QPen pen = QPen(QColor(Qt::blue),1);
        pen.setStyle(Qt::DotLine);
        painter->setPen(pen);
        painter->drawEllipse(boundingRect());

        if(this->getAgent() != NULL)
        {
            this->getAgent()->display(painter,boundingRect());
        }
        if(this->getGun() != NULL)
        {
            this->getGun()->display(painter,boundingRect());
        }

    }

    painter->restore();
}



GamePlayer::~GamePlayer()
{

}
