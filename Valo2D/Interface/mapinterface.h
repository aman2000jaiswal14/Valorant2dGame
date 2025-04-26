#ifndef MAPINTERFACE_H
#define MAPINTERFACE_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

#include <QObject>
class MapInterFace : public QObject
{
    Q_OBJECT
public:
    MapInterFace();
    virtual void loadMap() = 0;
    virtual int getMapId() = 0;


    QGraphicsScene *getScene() const;
    void setScene(QGraphicsScene *newScene);

    QGraphicsEllipseItem *getEyesightItem() const;
    void setEyesightItem(QGraphicsEllipseItem *newEyesightItem);

    virtual bool isPositionValid(QPointF pos) = 0;

    void showCapturePoint(QPointF pos,QColor col);
    void hideCapturePoint();

    QGraphicsEllipseItem *getCapturePointItem() const;

private:
    QGraphicsScene *scene = nullptr;
    QGraphicsEllipseItem *eyesightItem = nullptr;
    QGraphicsEllipseItem *capturePointItem = nullptr;


};

#endif // MAPINTERFACE_H
