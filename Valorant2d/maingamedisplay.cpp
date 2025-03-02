#include "maingamedisplay.h"
#include <QDebug>
#include <QtMath>
MainGameDisplay::MainGameDisplay() {

    player2.x = this->width()/2;
    player2.y = 40;
    player2.headAngle = 90;
    player2.team = 1;

    player1.x = this->width()/2;
    player1.y = this->height()-40;
    player1.headAngle = 270;
    player1.team = 2;

    currentPlayer = player2;
    pressedKeys = QSet<Qt::Key>();
    setFocus();
    setAttribute(Qt::WA_KeyCompression);
    setMouseTracking(true);

    // Initialize FPS and frame timer
    frameTimer.start();  // Start the timer
    frameCount = 0;      // Count the number of frames
    fps = 0;             // Initialize FPS to 0
    // Optional: Create a label to display the FPS on the screen
    fpsLabel = new QLabel(this);
    fpsLabel->setStyleSheet("color: white; font-size: 16px; background-color: rgba(0, 0, 0, 128); padding: 5px;");
    fpsLabel->move(10, 10); // Position near top-left corner

    // Set the label to resize automatically based on its content
    fpsLabel->adjustSize();  // Make sure the label fits the content
    fpsLabel->show();
}

void MainGameDisplay::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, this->width(), this->height());

    // ## LOAD MAP ###################

    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(Qt::white,2));
    painter.drawRect(20, 20, this->width()-40, this->height()-40);

    painter.drawLine(20,this->height()/2,this->width()/3-20,this->height()/2);
    painter.drawLine(this->width()/3+20,this->height()/2,2*this->width()/3-20,this->height()/2);
    painter.drawLine(2*this->width()/3+20,this->height()/2,this->width()-20,this->height()/2);

    // ###############################


    // ## PLAYERS #####################

    paintPlayer(painter,currentPlayer);
    paintPlayer(painter,player1);
    updatePlayerPosition();
    // ###############################


    // ## DRAW BULLETS ######################
    for (Bullet &bullet : bullets) {
        painter.setPen(QPen(Qt::yellow));  // Bullet color
        painter.drawEllipse(QPointF(bullet.x, bullet.y), 2, 2);  // Draw bullet
    }

    // Update player position based on key presses
    updatePlayerPosition();

    // Update bullet positions and remove bullets that go out of range
    for (int i = 0; i < bullets.size(); ++i) {
        if (bullets[i].updatePosition()) {
            bullets.removeAt(i);  // Remove bullet if it has exceeded its range
            i--;  // Adjust index to account for removed bullet
        }
    }

    // Update FPS
    updateFPS();

    // painter.end();


}

void MainGameDisplay::paintPlayer(QPainter &painter, Player &player)
{
    painter.save();
    if(player.team==1)
        painter.setPen(QPen(QColor(Qt::green)));
    else if(player.team==2)
        painter.setPen(QPen(QColor(Qt::red)));

    painter.drawEllipse(QPointF(player.x,player.y),5,5);
    double degrees = player.headAngle;
    painter.drawLine(QPointF(player.x,player.y),QPointF(player.x+10*qCos(qDegreesToRadians(degrees)),player.y+10*qSin(qDegreesToRadians(degrees))));
    painter.restore();
}

void MainGameDisplay::keyPressEvent(QKeyEvent *event)
{
    // Add the key to the pressed keys set
    pressedKeys.insert(static_cast<Qt::Key>(event->key()));
}

void MainGameDisplay::keyReleaseEvent(QKeyEvent *event)
{
    // Remove the key from the pressed keys set when released
    pressedKeys.remove(static_cast<Qt::Key>(event->key()));
}

void MainGameDisplay::updatePlayerPosition()
{
    double moveSpeed = 0.1;  // Movement speed

    double moveX = 0;
    double moveY = 0;

    // Check for movement keys in the pressedKeys set
    if (pressedKeys.contains(Qt::Key_W)) {   // Move up
        moveY -= moveSpeed;
    }
    if (pressedKeys.contains(Qt::Key_S)) {   // Move down
        moveY += moveSpeed;
    }
    if (pressedKeys.contains(Qt::Key_A)) {   // Move left
        moveX -= moveSpeed;
    }
    if (pressedKeys.contains(Qt::Key_D)) {   // Move right
        moveX += moveSpeed;
    }

    // Normalize movement to prevent faster diagonal movement
    double length = std::sqrt(moveX * moveX + moveY * moveY);
    if (length != 0) {
        moveX /= length;
        moveY /= length;
    }

    // Apply the movement to player position
    currentPlayer.x += moveX * moveSpeed;
    currentPlayer.y += moveY * moveSpeed;

    // Trigger a repaint
    update();
}
void MainGameDisplay::mouseMoveEvent(QMouseEvent *event)
{
    // Get the center of the player (or you can use widget center)
    double centerX = currentPlayer.x;
    double centerY = currentPlayer.y;

    // Get the mouse position
    double mouseX = event->x();
    double mouseY = event->y();

    // Calculate the angle from the center to the mouse position (in radians)
    double deltaX = mouseX - centerX;
    double deltaY = mouseY - centerY;
    currentPlayer.headAngle = std::atan2(deltaY, deltaX) * 180.0 / M_PI; // Convert radians to degrees

    // Repaint the widget to show the new angle
    update();
}
void MainGameDisplay::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        fireBullet(currentPlayer);  // Fire bullet in the direction of the mouse
    }
}

void MainGameDisplay::fireBullet(Player &player) {
    // Create a new bullet at the player's position, heading in the player's current direction
    Bullet bullet(player.x, player.y, player.headAngle, bulletSpeed, bulletRange, bulletHitPoints);
    bullets.append(bullet);  // Add the bullet to the vector

}

void MainGameDisplay::updateFPS() {
    // Increment the frame count
    frameCount++;

    // If one second has passed, calculate and display FPS
    if (frameTimer.elapsed() >= 1000) {  // 1000 milliseconds (1 second)
        fps = frameCount;  // FPS is the number of frames in the last second
        frameCount = 0;  // Reset the frame count for the next second
        frameTimer.restart();  // Restart the timer for the next second
    }

    // Optionally, display FPS on screen
    fpsLabel->setText(QString("FPS: %1").arg(fps));

    // Ensure the label resizes to fit the new text content
    fpsLabel->adjustSize();
}
