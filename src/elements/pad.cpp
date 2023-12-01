#include "Pad.h"
#include "Ball.h"
#include "gameData/Game.h"

const int width = 26.5;
const int height = 113;

void initPad1(Pad& pad)
{
	pad.x = GetScreenWidth() / 10.0f;
	pad.y = GetScreenHeight() / 2.0f;
	pad.width = width;
	pad.height = height;
	pad.minPosition = pad.height / 2;
	pad.maxPosition = GetScreenHeight() - pad.height / 2;
	Limit(pad);
}

void initPad2(Pad& pad)
{
	pad.x = GetScreenWidth() - 100.0f;
	pad.y = GetScreenHeight() / 2.0f;
	pad.width = width;
	pad.height = height;
	pad.minPosition = pad.height / 2;
	pad.maxPosition = GetScreenHeight() - pad.height / 2;
	Limit(pad);
}

void Limit(Pad& rectangle)
{
	if (rectangle.y - rectangle.height / 2 <= 0)
	{
		rectangle.y = rectangle.minPosition;
	}
	else if (rectangle.y + rectangle.height / 2 >= GetScreenHeight())
	{
		rectangle.y = rectangle.maxPosition;
	}
}

bool isColliding(Pad rectangle, Ball ball)
{
	float ballLeft = ball.x - ball.width / 2;
	float ballRight = ball.x + ball.width / 2;
	float ballTop = ball.y + ball.height / 2;
	float ballBottom = ball.y - ball.height / 2;

	float paddleLeft = rectangle.x - rectangle.width / 2;
	float paddleRight = rectangle.x + rectangle.width / 2;
	float paddleTop = rectangle.y + rectangle.height / 2;
	float paddleBottom = rectangle.y - rectangle.height / 2;

	return	paddleRight >= ballLeft &&
		paddleLeft <= ballRight &&
		paddleTop >= ballBottom &&
		paddleBottom <= ballTop;
}