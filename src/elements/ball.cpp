#include "gameData/game.h"
#include "Ball.h"

namespace pong
{
    void initBall(Ball& ball)
    {
        ball.x = GetScreenWidth() / 2.0f;
        ball.y = GetScreenHeight() / 2.0f;
        ball.speedX = 250.0f;
        ball.speedY = 250.0f;
        ball.width = 30;
        ball.height = 30;
    }
}