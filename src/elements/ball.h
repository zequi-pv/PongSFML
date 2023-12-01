#pragma once
struct Ball
{
    double x;
    double y;
    double width;
    double height;
    float speedY;
    float speedX;
};

void initBall(Ball& ball);