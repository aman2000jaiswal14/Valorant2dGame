#ifndef MAINGAMEDISPLAY_H
#define MAINGAMEDISPLAY_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent><
#include <QElapsedTimer>
#include <QLabel>
class Player{
public:
    double x = 0;
    double y = 0;
    double headAngle = 0;
    int team = 1;

};
class Bullet {
public:
    double x, y;      // Bullet's position
    double angle;     // Angle at which the bullet is fired
    double speed;     // Speed of the bullet
    double range;     // Max range before bullet disappears
    int hitPoints;    // Bullet hit points

    Bullet(double startX, double startY, double direction, double bulletSpeed, double bulletRange, int bulletHitPoints)
        : x(startX), y(startY), angle(direction), speed(bulletSpeed), range(bulletRange), hitPoints(bulletHitPoints) {}

    // Update bullet position and check if it exceeds the range
    bool updatePosition() {
        // Move in the direction of the angle
        x += speed * qCos(qDegreesToRadians(angle));
        y += speed * qSin(qDegreesToRadians(angle));

        // Check if the bullet exceeds the range
        range -= speed;
        return range <= 0;  // If the bullet has traveled its full range, it will be removed
    }
};

class MainGameDisplay : public QWidget
{
    Q_OBJECT
public:
    MainGameDisplay();
    void paintEvent(QPaintEvent *event);
    void paintPlayer(QPainter &painter, Player &player);
    Player player1;
    Player player2;
    Player currentPlayer;
    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void updatePlayerPosition() ;
    void fireBullet(Player &player);
   void mousePressEvent(QMouseEvent *event) override;
   void updateFPS();

    QVector<Bullet> bullets;  // Store bullets fired by the player
    double bulletSpeed = 2.0;  // Bullet speed
    double bulletRange = 300.0;  // Bullet range
    int bulletHitPoints = 1;  // Bullet hit points (can be extended to handle damage

    QElapsedTimer frameTimer;  // Use QElapsedTimer for time tracking
    int fps;           // Frames per second
    int frameCount;
    QLabel* fpsLabel;  // Optional: To display FPS on screen
private :
    QSet<Qt::Key> pressedKeys;



};

#endif // MAINGAMEDISPLAY_H
