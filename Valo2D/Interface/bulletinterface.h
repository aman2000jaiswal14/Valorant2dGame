#ifndef BULLETINTERFACE_H
#define BULLETINTERFACE_H


#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QTimer>
#include <QObject>

class BulletInterface : public QGraphicsObject
{
    Q_OBJECT
    QTimer *bulletTimer = nullptr;
public:
    BulletInterface();


public:

    QRectF boundingRect() const = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

    virtual int getBulletId() = 0;


    double getPosX() const;
    void setPosX(double newPosX);

    double getPosY() const;
    void setPosY(double newPosY);

    double getStartPosX() const;
    void setStartPosX(double newStartPosX);

    double getStartPoxY() const;
    void setStartPoxY(double newStartPoxY);

    double getRange() const;

    int getGamePlayerId() const;
    void setGamePlayerId(int newGamePlayerId);

    int getGunId() const;
    void setGunId(int newGunId);

    double getSpeed() const;

    virtual BulletInterface* release(double startPosX, double startPosY, double angle, int gamePlayerId, int gunId) = 0;

    double getAngle() const;
    void setAngle(double newAngle);

    void startBulletTimer();
    void stopBulletTimer();
private:
    int uniqueNo;
    double posX;
    double posY;
    double startPosX;
    double startPoxY;
    double tempX;
    double tempY;
    double angle;
    double range = 500;
    double speed = 50;
    int damage = 10;
    int gamePlayerId;
    int gunId;
    bool visibleToPlayer = true;
    bool setBulletTimer(int val);


private slots:
    void bulletTimerTimeOutSlot();

public:

    int getUniqueNo() const;
    void setUniqueNo(int newUniqueNo);



    int getDamage() const;
    void setDamage(int newDamage);


    bool getVisibleToPlayer() const;
    void setVisibleToPlayer(bool newVisibleToPlayer);

    void setSpeed(double newSpeed);

    void setRange(double newRange);

signals:
    void bulletUpdatedSignal(BulletInterface *,double ,double);
    void bulletDestroyedSignal(BulletInterface *);

};

#endif // BULLETINTERFACE_H
