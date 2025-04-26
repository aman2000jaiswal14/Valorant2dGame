#ifndef GAMEPLAYERINTERFACE_H
#define GAMEPLAYERINTERFACE_H

#include "playerinterface.h"
#include "agentinterface.h"
#include "guninterface.h"
#include "abilityinterface.h"
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QGraphicsEllipseItem>
#include <QTimer>

class GamePlayerInterface : public QGraphicsObject
{
    Q_OBJECT
    QTimer *smoothTimer;

public:
    GamePlayerInterface(PlayerInterface *_player);
    virtual ~GamePlayerInterface(){}

    PlayerInterface *player() const;
    void setPlayer(PlayerInterface *newPlayer);

    AgentInterFace *getAgent() const;
    void setAgent(AgentInterFace *newAgent);

    GunInterface *getGun() const;
    void setGun(GunInterface *newGun);

    void useEAbility();

    void setPositionXY(double newPositionX,double newPositionY);

    double getPositionX() const;
    void setPositionX(double newPositionX);

    double getPositionY() const;
    void setPositionY(double newPositionY);

    void setSmoothPosition(double x, double y);

    int getHeadPosition() const;
    void setHeadPosition(int newHeadPosition);

    int getHealth() const;
    void setHealth(int newHealth);

    int getShield() const;
    void setShield(int newShield);

    int getTeam() const;
    void setTeam(int newTeam);

    virtual QRectF boundingRect() const = 0;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) = 0;


    double getHealthRadius() const;
    void setHealthRadius(double newHealthRadius);

    double getSpeed() const;
    void setSpeed(double newSpeed);

    void reducePlayerHealth(int damage);

    bool checkItemInEyeSightRange(QRectF itemRect);



private:
    PlayerInterface *_player = nullptr;
    AgentInterFace *agent = nullptr;
    GunInterface *gun = nullptr;

    QGraphicsEllipseItem *eyeSightItem = nullptr;

    double positionX = 0;
    double positionY = 0;

    double targetPositionX = 0;
    double targetPositionY = 0;
    double renderingPositionX = 0;
    double renderingPositionY = 0;


    int headPosition = 0;
    int health = 100;
    int shield  =100;
    int team = 0;
    double healthRadius = 20;
    double speed = 15;
    double eyeSightRadius = 300;
    int eyeSightAngle = 150;

    double defaultEyeSightRadius = 300;
    int defaultEyeSightAngle = 150;
    int defaultHealth = 100;
    int defaultShield = 100;
    double defaultSpeed = 20;


    void setEyeSightX();
    void setEyeSightY();
    void setEyeSightAngle();

public:

    double getEyeSightRadius() const;
    void setEyeSightRadius(double newEyeSightRadius);

    int getEyeSightAngle() const;
    void setEyeSightAngle(int newEyeSightAngle);

    QGraphicsEllipseItem *getEyeSightItem() const;
    void setEyeSightItem(QGraphicsEllipseItem *newEyeSightItem);

    double getDefaultEyeSightRadius() const;
    void setDefaultEyeSightRadius(double newDefaultEyeSightRadius);

    int getDefaultEyeSightAngle() const;
    void setDefaultEyeSightAngle(int newDefaultEyeSightAngle);

    int getDefaultHealth() const;
    void setDefaultHealth(int newDefaultHealth);

    int getDefaultShield() const;
    void setDefaultShield(int newDefaultShield);


    double getDefaultSpeed() const;
    void setDefaultSpeed(double newDefaultSpeed);

public slots:
    void smoothUpdateSlot();
signals:
    void healthUpdatedSignal(GamePlayerInterface*);
    void gunChangeSignal();
    void gamePlayerPositionChangeSignal();
    void eAbilitYUsedSignal();



};

#endif // GAMEPLAYERINTERFACE_H
