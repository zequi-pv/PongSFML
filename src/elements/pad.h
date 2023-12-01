#pragma once
#include "Ball.h"

namespace pong
{
    struct Pad
    {
        float x;
        float y;
        int width;
        int height;
        int score;
        int minPosition;
        int maxPosition;
    };

    void initPad1(Pad& pad);
    void initPad2(Pad& pad);
    void Limit(Pad& rectangle);
    bool isColliding(Pad rectangle, Ball ball);
}