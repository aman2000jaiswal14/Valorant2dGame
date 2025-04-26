#include "bullet2.h"

Bullet2::Bullet2() {

    setSpeed(50);
    setRange(500);
    setDamage(100);
}



QRectF Bullet2::boundingRect() const
{
    return QRectF(0,0,6,2);
}

void Bullet2::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();

    painter->translate(boundingRect().center());
    painter->rotate(getAngle());
    painter->translate(-boundingRect().center());
    QPen pen = QPen(QColor(Qt::red),1);
    QBrush brush = QBrush(QColor(Qt::red));
    painter->setPen(pen);
    painter->setBrush(brush);

    painter->drawRect(boundingRect());
    painter->restore();
}

BulletInterface* Bullet2::release(double startPosX, double startPosY, double angle, int gamePlayerId, int gunId)
{
    this->setStartPosX(startPosX);
    this->setStartPoxY(startPosY);
    this->setAngle(angle);
    this->setGamePlayerId(gamePlayerId);
    this->setGunId(gunId);
    // qDebug()<<"startX : "<<startPosX<<" startY : "<<startPosY<<" angle : "<<angle;
    return this;

}

int Bullet2::getBulletId()
{
    return 2;
}
