#include "gameview.h"
#include "datastore.h"
#include "specialutils.h"
#include "structures.h"
#include "middleware.h"
#include <QtMath>
#include <QMenu>
#include <QPoint>
#include <QCursor>
GameView::GameView(QWidget *parent) : QGraphicsView(parent)
{

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setCursor(Qt::CrossCursor);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    this->setStyleSheet("background-color:black");

    capturePositionDisplayTimer = new QTimer;
    capturePositionDisplayTimer->setSingleShot(true);
    capturePositionDisplayTimer->setInterval(2000);
    connect(capturePositionDisplayTimer,&QTimer::timeout,this,&GameView::capturePositionDisplayTimeout);
}

void GameView::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton)
    {
        if(DataStore::getInstance().getGamePlayer() && DataStore::getInstance().getGamePlayer()->player() && DataStore::getInstance().getGamePlayer()->getGun()  && DataStore::getInstance().getGamePlayer()->getGun()->getBulletBehav())
        {
            if(DataStore::getInstance().getGamePlayer()->getHealth() > 0)
            {
                double angle = DataStore::getInstance().getGamePlayer()->getHeadPosition() - 90;
                int offset = 0;
                double currX = DataStore::getInstance().getGamePlayer()->x()+(DataStore::getInstance().getGamePlayer()->boundingRect().width()/2) + (DataStore::getInstance().getGamePlayer()->boundingRect().width()/2 + DataStore::getInstance().getGamePlayer()->getGun()->getBulletBehav()->boundingRect().width() +offset)*qCos(qDegreesToRadians(angle)) ;//- DataStore::getInstance().getGamePlayer()->getGun()->getBulletBehav()->boundingRect().width()/2;
                double currY = DataStore::getInstance().getGamePlayer()->y()+(DataStore::getInstance().getGamePlayer()->boundingRect().height()/2) + (DataStore::getInstance().getGamePlayer()->boundingRect().height()/2 + DataStore::getInstance().getGamePlayer()->getGun()->getBulletBehav()->boundingRect().height() +offset)*qSin(qDegreesToRadians(angle));// - DataStore::getInstance().getGamePlayer()->getGun()->getBulletBehav()->boundingRect().height()/2;

                // qDebug()<<" angle : "<<angle<<" scenepos : "<<DataStore::getInstance().getGamePlayer()->scenePos()<<" currX : "<<currX <<" currY : "<<currY <<" x : "<< DataStore::getInstance().getGamePlayer()->x() <<" y : "<< DataStore::getInstance().getGamePlayer()->y();

                int playerId = DataStore::getInstance().getGamePlayer()->player()->getId();

                int uniqueId = SpecialUtils::getInstance().idGenerator();



                BulletInterface* bullet = DataStore::getInstance().getGamePlayer()->getGun()->fire(currX,currY,angle,playerId);
                if(bullet == NULL) return;

                bullet->setUniqueNo(uniqueId);
                connect(bullet,&BulletInterface::bulletDestroyedSignal,this,&GameView::bulletDestroyedSlot);
                connect(bullet,&BulletInterface::bulletUpdatedSignal,this,&GameView::bulletUpdatedSlot);
                bullet->startBulletTimer();
            }

        }

    }
    else
    {

        // QMenu menu;
        // menu.addAction(QString("pos x: %1 y: %2").arg(event->pos().x()).arg(event->pos().y()));
        // menu.addAction(QString("scene pos x: %1 y: %2").arg(mapToScene(event->pos()).x()).arg(mapToScene(event->pos()).y()));
        // menu.addAction(QString("scene from pos x: %1 y: %2").arg(mapFromScene(event->pos()).x()).arg(mapFromScene(event->pos()).y()));
        // menu.addAction(QString("scene from pos x: %1 y: %2").arg(mapFromScene(event->pos()).x()).arg(mapToGlobal(event->pos()).y()));
        // menu.exec((event->pos()));
    }


    QGraphicsView::mousePressEvent(event);
}

void GameView::mouseReleaseEvent(QMouseEvent *event)
{

    if(event->button() == Qt::RightButton)
    {
        DataStore::getInstance().capturePosition = mapToScene(event->pos());
        DataStore::getInstance().capturePositionDisplay = mapToScene(event->pos());
        emit capturePositionDisplaySignal();
        capturePositionDisplayTimer->start();
    }

    QGraphicsView::mouseReleaseEvent(event);
}

void GameView::mouseMoveEvent(QMouseEvent *event)
{

    double centerX = DataStore::getInstance().getGamePlayer()->x();
    double centerY = DataStore::getInstance().getGamePlayer()->y();

    double mouseX = mapToScene(event->pos()).x();
    double mouseY = mapToScene(event->pos()).y();

    DataStore::getInstance().mouseMovementCursorPosition.setX(mouseX);
    DataStore::getInstance().mouseMovementCursorPosition.setX(mouseY);

    double deltaX = mouseX - centerX;
    double deltaY = mouseY - centerY;

    double rotation = std::atan2(deltaY,deltaX) * 180.0/ M_PI  + 90;

    // qDebug()<<mouseX<<mouseY<<centerX<<centerY<<rotation;
    if(qAbs(prev_rotation-rotation)>rotation_precision)
    {
        prev_rotation = rotation;
        emit sceneRotationAngleSignal(rotation);

    }
    QGraphicsView::mouseMoveEvent(event);

}

void GameView::wheelEvent(QWheelEvent *event)
{

}

void GameView::bulletDestroyedSlot(BulletInterface *bullet)
{
    // qDebug()<<"bullet destroyed" <<bullet->getBulletId();
    // emit removeBulletFromSceneSignal(bullet);

    STRUCT_BULLET_INFO bullet_info;
    bullet_info.uniqueNo = bullet->getUniqueNo();
    bullet_info.bulletId = bullet->getBulletId();
    bullet_info.startPosX = bullet->getStartPosX();
    bullet_info.startPosY = bullet->getStartPoxY();
    bullet_info.posX = bullet_info.posX;
    bullet_info.posY = bullet_info.posY;
    bullet_info.angle = bullet->getAngle();
    bullet_info.playerId = bullet->getGamePlayerId();
    bullet_info.gunId = bullet->getGunId();
    bullet_info.destroyed = true;

    MiddleWare::getInstance().sendBulletInfoMsg(bullet_info);

}

void GameView::bulletUpdatedSlot(BulletInterface *bullet, double posX, double posY)
{
    emit bulletUpdatedSignal(bullet,posX,posY);
}

void GameView::capturePositionDisplayTimeout()
{
    emit capturePositionDisplayOffSignal();
}


