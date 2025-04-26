#include "bullet1.h"

Bullet1::Bullet1() {

    setSpeed(25);
    setRange(100);
    setDamage(10);

}

QRectF Bullet1::boundingRect() const
{
    return QRectF(0,0,6,6);
}

void Bullet1::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    QPen pen = QPen(QColor(Qt::blue),1);
    QBrush brush = QBrush(QColor(Qt::black));
    painter->setPen(pen);
    painter->setBrush(brush);

    painter->drawEllipse(boundingRect());
    painter->restore();
}

BulletInterface* Bullet1::release(double startPosX, double startPosY, double angle, int gamePlayerId, int gunId)
{
    this->setStartPosX(startPosX);
    this->setStartPoxY(startPosY);
    this->setAngle(angle);
    this->setGamePlayerId(gamePlayerId);
    this->setGunId(gunId);
    // qDebug()<<"startX : "<<startPosX<<" startY : "<<startPosY<<" angle : "<<angle;
    return this;

}




int Bullet1::getBulletId()
{
    return 1;
}



