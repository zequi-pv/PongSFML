#pragma once
#include "Ball.h"

struct Pad
{
    double x;
    double y;
    double width;
    double height;
    int score = 0;
    int minPosition;
    int maxPosition;
};

void initPad1(Pad& pad);
void initPad2(Pad& pad);
void Limit(Pad& rectangle);
bool isColliding(Pad rectangle, Ball ball);