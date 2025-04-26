#include "gameplayerinterface.h"


GamePlayerInterface::GamePlayerInterface(PlayerInterface *_player)
{


    smoothTimer = new QTimer;
    smoothTimer->setInterval(20);
    connect(smoothTimer,&QTimer::timeout,this,&GamePlayerInterface::smoothUpdateSlot);
    this->setTransformOriginPoint(getHealthRadius(),getHealthRadius());
    this->_player = _player;
}

PlayerInterface *GamePlayerInterface::player() const
{
    return _player;
}

void GamePlayerInterface::setPlayer(PlayerInterface *newPlayer)
{
    _player = newPlayer;
}

AgentInterFace *GamePlayerInterface::getAgent() const
{
    return agent;
}

void GamePlayerInterface::setAgent(AgentInterFace *newAgent)
{
    agent = newAgent;
    update();
}

GunInterface *GamePlayerInterface::getGun() const
{
    return gun;
}

void GamePlayerInterface::setGun(GunInterface *newGun)
{
    gun = newGun;
    emit gunChangeSignal();
    update();
}

void GamePlayerInterface::useEAbility()
{
    if(getAgent() && getAgent()->getEAbility())
    {
        getAgent()->getEAbility()->executeAbility();
    }
    emit eAbilitYUsedSignal();
}

void GamePlayerInterface::setPositionXY(double newPositionX, double newPositionY)
{
    setPositionX(newPositionX);
    setPositionY(newPositionY);

    emit gamePlayerPositionChangeSignal();
}

double GamePlayerInterface::getPositionX() const
{
    return positionX;
}

void GamePlayerInterface::setPositionX(double newPositionX)
{
    positionX = newPositionX;// - boundingRect().width()/2;
    this->setX(positionX);
    setEyeSightX();

}

double GamePlayerInterface::getPositionY() const
{

    return positionY;
}

void GamePlayerInterface::setPositionY(double newPositionY)
{
    positionY = newPositionY;// - boundingRect().height()/2;
    this->setY(positionY);
    setEyeSightY();
}

void GamePlayerInterface::setSmoothPosition(double x, double y)
{
    renderingPositionX = getPositionX();
    renderingPositionY = getPositionY();
    targetPositionX = x;
    targetPositionY = y;
    smoothTimer->stop();
    smoothTimer->start();
}

int GamePlayerInterface::getHeadPosition() const
{
    return headPosition;
}

void GamePlayerInterface::setHeadPosition(int newHeadPosition)
{
    headPosition = newHeadPosition;
    setRotation(headPosition);
    setEyeSightAngle();

}

int GamePlayerInterface::getHealth() const
{
    return health;
}

void GamePlayerInterface::setHealth(int newHealth)
{
    health = newHealth;
    emit healthUpdatedSignal(this);
}

int GamePlayerInterface::getShield() const
{
    return shield;
}

void GamePlayerInterface::setShield(int newShield)
{
    shield = newShield;
    emit healthUpdatedSignal(this);
}

int GamePlayerInterface::getTeam() const
{
    return team;
}

void GamePlayerInterface::setTeam(int newTeam)
{
    team = newTeam;
}

double GamePlayerInterface::getHealthRadius() const
{
    return healthRadius;
}

void GamePlayerInterface::setHealthRadius(double newHealthRadius)
{
    healthRadius = newHealthRadius;
}

double GamePlayerInterface::getSpeed() const
{
    return speed;
}

void GamePlayerInterface::setSpeed(double newSpeed)
{
    speed = newSpeed;
}

void GamePlayerInterface::reducePlayerHealth(int damage)
{

    int newshield = shield - qMin(shield,damage);
    int newdamage = damage- qMin(shield,damage);
    int newhealth = health - qMin(health,newdamage);

    setHealth(newhealth);
    setShield(newshield);
    if(health == 0)
    {
        update();
    }

}

bool GamePlayerInterface::checkItemInEyeSightRange(QRectF itemRect)
{
    if(eyeSightItem)
    {
        if(eyeSightItem->contains(eyeSightItem->mapFromScene(QPointF(itemRect.topLeft().x()+itemRect.width()/2,itemRect.topLeft().y()+itemRect.height()/2)))){
            return true;
        }
    }
    return false;
}

double GamePlayerInterface::getDefaultSpeed() const
{
    return defaultSpeed;
}

void GamePlayerInterface::setDefaultSpeed(double newDefaultSpeed)
{
    defaultSpeed = newDefaultSpeed;
}

int GamePlayerInterface::getDefaultShield() const
{
    return defaultShield;
}

void GamePlayerInterface::setDefaultShield(int newDefaultShield)
{
    defaultShield = newDefaultShield;
}

void GamePlayerInterface::smoothUpdateSlot()
{
    int maxRate = 10;
    double rateX = qMax(2.0,qAbs(targetPositionX - renderingPositionX)/maxRate);
    double rateY = qMax(2.0,qAbs(targetPositionY - renderingPositionY)/maxRate);;
    double diffX = 0;
    double diffY = 0;
    if(targetPositionX - this->getPositionX() > 0){
        diffX = qMin(targetPositionX - renderingPositionX,rateX);
    }
    else
    {
        diffX = qMax(targetPositionX - renderingPositionX,-rateX);
    }

    if(targetPositionY - renderingPositionY > 0){
        diffY = qMin(targetPositionY - renderingPositionY,rateY);
    }
    else
    {
        diffY = qMax(targetPositionY - renderingPositionY,-rateY);
    }

    renderingPositionX += diffX;
    renderingPositionY += diffY;


    this->setPositionXY(renderingPositionX,renderingPositionY);

    if(diffX == 0 && diffY == 0)
    {
        smoothTimer->stop();
    }
}

int GamePlayerInterface::getDefaultHealth() const
{
    return defaultHealth;
}

void GamePlayerInterface::setDefaultHealth(int newDefaultHealth)
{
    defaultHealth = newDefaultHealth;
}

int GamePlayerInterface::getDefaultEyeSightAngle() const
{
    return defaultEyeSightAngle;
}

void GamePlayerInterface::setDefaultEyeSightAngle(int newDefaultEyeSightAngle)
{
    defaultEyeSightAngle = newDefaultEyeSightAngle;
}

double GamePlayerInterface::getDefaultEyeSightRadius() const
{
    return defaultEyeSightRadius;
}

void GamePlayerInterface::setDefaultEyeSightRadius(double newDefaultEyeSightRadius)
{
    defaultEyeSightRadius = newDefaultEyeSightRadius;
}

void GamePlayerInterface::setEyeSightX()
{
    if(eyeSightItem)
    {
        eyeSightItem->setX(getPositionX() - eyeSightItem->rect().width()/2 + this->boundingRect().width()/2);
    }

}

void GamePlayerInterface::setEyeSightY()
{
    if(eyeSightItem)
    {
        eyeSightItem->setY(getPositionY() - eyeSightItem->rect().height()/2 + this->boundingRect().height()/2 );
    }
}

void GamePlayerInterface::setEyeSightAngle()
{
    if(eyeSightItem)
        eyeSightItem->setRotation(getHeadPosition());
}

QGraphicsEllipseItem *GamePlayerInterface::getEyeSightItem() const
{
    return eyeSightItem;
}

void GamePlayerInterface::setEyeSightItem(QGraphicsEllipseItem *newEyeSightItem)
{
    eyeSightItem = newEyeSightItem;
    setEyeSightAngle(getEyeSightAngle());
    setEyeSightRadius(getEyeSightRadius());
    eyeSightItem->setBrush(QBrush(QColor(255,0,0,15)));
    setEyeSightX();
    setEyeSightY();
    setEyeSightAngle();

}

int GamePlayerInterface::getEyeSightAngle() const
{
    return eyeSightAngle;
}

void GamePlayerInterface::setEyeSightAngle(int newEyeSightAngle)
{
    eyeSightAngle = newEyeSightAngle;

    eyeSightItem->setStartAngle((90-getEyeSightAngle()/2) * 16);
    eyeSightItem->setSpanAngle(getEyeSightAngle() * 16);
}

double GamePlayerInterface::getEyeSightRadius() const
{
    return eyeSightRadius;
}

void GamePlayerInterface::setEyeSightRadius(double newEyeSightRadius)
{
    eyeSightRadius = newEyeSightRadius;
    eyeSightItem->setRect(QRectF(0, 0, getEyeSightRadius(), getEyeSightRadius()));
    eyeSightItem->setTransformOriginPoint(getEyeSightRadius()/2,getEyeSightRadius()/2);
    setEyeSightX();
    setEyeSightY();
    setEyeSightAngle();
}

