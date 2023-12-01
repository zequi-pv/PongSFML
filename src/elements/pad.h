#pragma once
#include "Ball.h"

struct Pad
{
    float x;
    float y;
    float width;
    float height;
    int score = 0;
    int minPosition;
    int maxPosition;
};

void initPad1(Pad& pad);
void initPad2(Pad& pad);
void Limit(Pad& rectangle);
bool isColliding(Pad rectangle, Ball ball);