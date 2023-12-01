#pragma once

namespace pong
{
    struct Ball
    {
        float x;
        float y;
        int width;
        int height;
        float speedY;
        float speedX;
    };

    void initBall(Ball& ball);
}