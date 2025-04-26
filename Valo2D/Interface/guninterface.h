#ifndef GUNINTERFACE_H
#define GUNINTERFACE_H
#include <QRectF>
#include <QPainter>


#include "bulletinterface.h"
#include <QTimer>
class GunInterface : public QObject
{
    Q_OBJECT
    QTimer *reloadTimer = nullptr;
public:
    GunInterface();
    virtual ~GunInterface(){}
    virtual int getGunId() = 0;
    virtual QString getName() = 0;
    virtual QString getDesc() = 0;
    virtual void display(QPainter * painter,QRectF boundingRect) = 0;

    virtual BulletInterface* fire(double startPosX, double startPosY, double angle, int gamePlayerId);

    virtual BulletInterface *getBulletBehav() =0;


    int getMagzine() const;
    void setMagzine(int newMagzine);

    int getMagzineCap() const;
    void setMagzineCap(int newMagzineCap);

    int getReloadTime() const;
    void setReloadTime(int newReloadTime);

    int getBulletLeft() const;
    void setBulletLeft(int newBulletLeft);

    int getMagzineLeft() const;
    void setMagzineLeft(int newMagzineLeft);

    bool getIsReloading() const;
    void setIsReloading(bool newIsReloading);

    void startReloading();

    virtual void configureGun() = 0;
private:
    int magzine=2;
    int magzineCap = 6;
    int reloadTime = 3000;
    int bulletLeft = 6;
    int magzineLeft = 2;
    bool isReloading = false;

private slots:
    void reloadTimerTimeOutSlot();

public:
signals:
    void bulletStatusUpdatedSignal();




};

#endif // GUNINTERFACE_H
