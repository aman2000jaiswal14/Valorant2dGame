#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);


signals:

};

#endif // GAMESCENE_H
