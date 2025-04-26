#ifndef MAINGAMEPAGE_H
#define MAINGAMEPAGE_H

#include <QWidget>
#include <QObject>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QElapsedTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <gameplayerinterface.h>
#include <QKeyEvent>
#include "bulletinterface.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <mapfactoryclass.h>



namespace Ui {
class MainGamePage;
}

class GameScene;
class GameView;
class MainGamePage : public QWidget
{
    Q_OBJECT

public:
    explicit MainGamePage(QWidget *parent = nullptr);
    ~MainGamePage();
    void connectCurrentPlayer();
    void mainGamePreOpenConfiguration();
    void showView();
    void loadGame();

private:
    Ui::MainGamePage *ui;
    GameView *view = nullptr;
    GameScene *scene = nullptr;
    MapInterFace *map1 = nullptr;





    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;



    void addPlayer(GamePlayerInterface *player);
    void removePlayer(GamePlayerInterface *player);

public:
    void addBullet(BulletInterface *bullet);
    void removeBullet(BulletInterface *bullet);
    void setPlayerName(QString pName);
    void addAllPlayerToScene();
    void setPositionTransfrom();
    void eAbilityBuy();

    MapInterFace *getMap1() const;
    void setMap1(MapInterFace *newMap1);

public slots:
    void sceneRotationAngleSlot(double rotation);
    void gunFiredSlot(BulletInterface *bullet);
    void removeBulletFromSceneSlot(BulletInterface *bullet);
    void healthUpdatedSlot(GamePlayerInterface*);
    void gunChangeSlot();
    void bulletStatusUpdatedSlot();
    void bulletUpdatedSlot(BulletInterface *bullet,double posX,double posY);
    void gamePlayerPositionChangeSlot();
    void eAbilitYUsedSlot();
    void capturePositionDisplaySlot();
    void capturePositionDisplayOffSlot();

signals:
    void openCloseItemStoreSignal();
};

#endif // MAINGAMEPAGE_H
