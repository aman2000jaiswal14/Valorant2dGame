#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QMouseEvent>
#include "bulletinterface.h"
#include <QTimer>
class GameView : public QGraphicsView
{
    Q_OBJECT
    double prev_rotation = 0;
    double rotation_precision = 1;
    QTimer *capturePositionDisplayTimer;
public:
    GameView(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event) ;
    void wheelEvent(QWheelEvent *event);


signals:
    void sceneRotationAngleSignal(double);
    void gunFiredSignal(BulletInterface *bullet);
    void removeBulletFromSceneSignal(BulletInterface *);
    void bulletUpdatedSignal(BulletInterface *bullet,double posX,double posY);
    void capturePositionDisplaySignal();
    void capturePositionDisplayOffSignal();

public slots:
    void bulletDestroyedSlot(BulletInterface *);
    void bulletUpdatedSlot(BulletInterface *bullet,double posX,double posY);

private slots:
    void capturePositionDisplayTimeout();

};

#endif // GAMEVIEW_H
