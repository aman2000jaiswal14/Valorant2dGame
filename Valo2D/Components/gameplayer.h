#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H


#include "playerinterface.h"
#include "gameplayerinterface.h"
class GamePlayer : public GamePlayerInterface
{
public:
    GamePlayer(PlayerInterface *player);
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    ~GamePlayer();
};

#endif // GAMEPLAYER_H
