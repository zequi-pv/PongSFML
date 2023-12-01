#include "Game.h"

#include <time.h>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "elements/Ball.h"
#include "elements/Pad.h"

using namespace std;
using namespace sf;

enum GameScreen
{
	MENU,
	SINGLEPLAYER,
	MULTIPLAYER,
	RULES,
	EXIT
};

static void init(RenderWindow& window, Ball& ball, Pad& rectangle1, Pad& rectangle2, Pad& middleRectangle);
static void PausedGame(bool& pause, GameScreen& currentScreen, Pad& rectangle1, Pad& rectangle2, Ball& ball, bool& gameOver);
static void ResetGame(Pad& rectangle1, Pad& rectangle2, Ball& ball, bool& gameOver);
static void drawGame(Ball& ball, Pad& rectangle1, Pad& rectangle2, Pad& middleRectangle, Texture texBall, Texture texPadOne, Texture texPadTwo, Texture texField, bool pause, int winPoints, Texture textMenuPause);
static void drawRules(Texture texField);
static void returnToMenu(GameScreen& currentScreen, Pad& rectangle1, Pad& rectangle2, Ball& ball, bool& gameOver);
static void inputsSingle(Time& dt, Keyboard keyboard, Pad& rectangle1);
static void updateSingleplayer(Time& dt, Keyboard keyboard, Ball& ball, Pad& rectangle1, Pad& rectangle2, GameScreen& currentScreen, bool& gameOver, int winPoints, bool& pause, int& currentOption);
static void inputsMulti(Time& dt, Keyboard keyboard, Pad& rectangle1, Pad& rectangle2);
static void updateMultiplayer(Time& dt, Keyboard keyboard, Ball& ball, Pad& rectangle1, Pad& rectangle2, GameScreen& currentScreen, bool& gameOver, int winPoints, bool& pause, int& currentOption);
static void close();

void runGame()
{
	srand(time(NULL));

	RenderWindow window;

	Clock clock;

	Time dt;

	Keyboard keyboard;

	Font font;
	font.loadFromFile("res/fonts/BoaConstruktorBold.ttf");

	Text text;
	text.setFont(font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Regular);

	Ball ball;
	Pad rectangle1;
	Pad rectangle2;
	Pad middleRectangle;
	bool gameOver = false;
	bool pause = false;

	init(window, ball, rectangle1, rectangle2, middleRectangle);

	Texture texBall;
	texBall.loadFromFile("assets/Ball.png");

	Texture texPadOne;
	texPadOne.loadFromFile("assets/PadTwo.png");

	Texture texPadTwo;
	texPadTwo.loadFromFile("assets/PadOne.png");

	Texture texField;
	texField.loadFromFile("assets/Field.png");

	Texture textMenuPause;
	textMenuPause.loadFromFile("assets/PauseMenu.png");

	Texture texMenuLogo;
	texMenuLogo.loadFromFile("assets/MenuLogo.png");

	int initialDirection = rand() % 4 + 1;
	int initialDirectionAgain = rand() % 2 + 1;
	int currentOption = 0;
	int firstOption = SINGLEPLAYER;
	int lastOption = EXIT;
	bool isGameRunning = true;
	int winPoints = 5;
	float timer;
	float coolDownTime = 0.54f;

	GameScreen currentScreen = MENU;

	while (window.isOpen() && isGameRunning)
	{
		dt = clock.restart();

		timer += dt.asSeconds();

		if (keyboard.isKeyPressed(Keyboard::Down))
		{
			if (timer >= coolDownTime)
			{
				timer -= coolDownTime;
				currentOption++;

				if (currentOption >= lastOption)
				{
					currentOption = lastOption;
				}
			}
		}

		if (keyboard.isKeyPressed(Keyboard::Up))
		{
			if (timer >= coolDownTime)
			{
				timer -= coolDownTime;
				currentOption--;

				if (currentOption <= firstOption)
				{
					currentOption = firstOption;
				}
			}

		}

		switch (currentScreen)
		{
		case MENU:
			switch (currentOption)
			{
			case SINGLEPLAYER:
				if (keyboard.isKeyPressed(Keyboard::Enter))
				{
					currentScreen = GameScreen::SINGLEPLAYER;
				}
				break;
			case MULTIPLAYER:
				if (keyboard.isKeyPressed(Keyboard::Enter))
				{
					currentScreen = GameScreen::MULTIPLAYER;
				}
				break;
			case RULES:
				if (keyboard.isKeyPressed(Keyboard::Enter))
				{
					currentScreen = GameScreen::RULES;

				}
				break;
			case EXIT:
				if (keyboard.isKeyPressed(Keyboard::Enter))
				{
					currentScreen = GameScreen::EXIT;
				}
				break;
			default:
				break;
			}
			break;
		case SINGLEPLAYER:
			updateSingleplayer(dt, keyboard, ball, rectangle1, rectangle2, currentScreen, gameOver, winPoints, pause, currentOption);
			break;
		case MULTIPLAYER:
			updateMultiplayer(dt, keyboard,ball, rectangle1, rectangle2, currentScreen, gameOver, winPoints, pause, currentOption);
			break;
		case RULES:
			if (keyboard.isKeyPressed(Keyboard::Escape))
			{
				currentScreen = GameScreen::MENU;
			}
			break;
		case EXIT:
			if (keyboard.isKeyPressed(Keyboard::Enter))
			{
				isGameRunning = false;
			}
			break;
		default:
			break;
		}

		switch (currentScreen)
		{
		case MENU:
			slSetBackColor(0.0, 0.6, 0.0);
			slSetTextAlign(SL_ALIGN_CENTER);
			slSetForeColor(1, 1, 1, 1);
			slSprite(texField, 400, 225, 800, 450);

			slSetFontSize(50);
			slSetForeColor(0, 0, 1, 1);
			slText(400, 320, "SUPER");
			slSetForeColor(1, 1, 0, 1);
			slText(400, 270, "CHAMPION");
			slSetForeColor(1, 0, 0, 1);
			slText(400, 220, "PONG");

			slSetFontSize(20);
			slSetForeColor(1, 1, 1, 1);
			slText(170, 20, "Made by Ezequiel Prieto");
			slText(400, 190, "SINGLE PLAYER");
			slText(400, 170, "MULTI PLAYER");
			slText(400, 150, "RULES");
			slText(400, 130, "EXIT");

			slText(600, 80, "Use the up and down keys ");
			slText(600, 50, "to move through the menu!");

			slSetForeColor(1, 1, 1, 1);

			switch (currentOption)
			{
			case SINGLEPLAYER:
				slSetTextAlign(SL_ALIGN_CENTER);
				slSetFontSize(20);
				slSetForeColor(1, 0, 0, 1);
				slText(400, 190, "SINGLE PLAYER");

				break;
			case MULTIPLAYER:
				slSetTextAlign(SL_ALIGN_CENTER);
				slSetFontSize(20);
				slSetForeColor(1, 0, 0, 1);
				slText(400, 170, "MULTI PLAYER");

				break;
			case RULES:
				slSetTextAlign(SL_ALIGN_CENTER);
				slSetFontSize(20);
				slSetForeColor(1, 0, 0, 1);
				slText(400, 150, "RULES");

				break;
			case EXIT:
				slSetTextAlign(SL_ALIGN_CENTER);
				slSetFontSize(20);
				slSetForeColor(1, 0, 0, 1);
				slText(400, 130, "EXIT");

				break;
			default:
				break;
			}

			break;
		case SINGLEPLAYER:
			slSetBackColor(0.0, 0.600, 0.0);
			drawGame(ball, rectangle1, rectangle2, middleRectangle, texBall, texPadOne, texPadTwo, texField, pause, winPoints, textMenuPause);
			break;
		case MULTIPLAYER:
			slSetBackColor(0.0, 0.600, 0.0);
			drawGame(ball, rectangle1, rectangle2, middleRectangle, texBall, texPadOne, texPadTwo, texField, pause, winPoints, textMenuPause);
			break;
		case RULES:
			slSetBackColor(0.0, 0.0, 0.0);
			drawRules(texField);
			break;
		case EXIT:
			break;
		default:
			break;
		}

		window.display();
	}

	close();
}

int GetScreenWidth()
{
	const int screenWidth = 800;
	return screenWidth;
}

int GetScreenHeight()
{
	const int screenHeight = 450;
	return screenHeight;
}

void PausedGame(bool& pause, GameScreen& currentScreen, Pad& rectangle1, Pad& rectangle2, Ball& ball, bool& gameOver)
{
	if (slGetKey(SL_KEY_BACKSPACE))
	{
		pause = true;
	}
	if (slGetKey(SL_KEY_ENTER))
	{
		pause = false;
	}
	if (pause && slGetKey(SL_KEY_ESCAPE))
	{
		returnToMenu(currentScreen, rectangle1, rectangle2, ball, gameOver);
	}
}

void ResetGame(Pad& rectangle1, Pad& rectangle2, Ball& ball, bool& gameOver)
{
	gameOver = false;
	rectangle1.score = 0;
	rectangle2.score = 0;
	initBall(ball);
	initPad1(rectangle1);
	initPad2(rectangle2);
}

void returnToMenu(GameScreen& currentScreen, Pad& rectangle1, Pad& rectangle2, Ball& ball, bool& gameOver)
{
	ResetGame(rectangle1, rectangle2, ball, gameOver);
	currentScreen = GameScreen::MENU;
}

void ResetBall(Ball& ball)
{
	int direction = rand() % 4 + 1;
	ball.speedX = 250.0f;
	ball.speedY = 250.0f;

	ball.x = GetScreenWidth() / 2;
	ball.y = GetScreenHeight() / 2;

	switch (direction)
	{
	case 1:
		ball.speedX *= 1.0f;
		ball.speedY *= -1.0f;
		break;
	case 2:
		ball.speedX *= 1.0f;
		ball.speedY *= 1.0f;
		break;
	case 3:
		ball.speedX *= -1.0f;
		ball.speedY *= 1.0f;
		break;
	case 4:
		ball.speedX *= -1.0f;
		ball.speedY *= -1.0f;
		break;
	default:
		break;
	}
}

void init(RenderWindow& window, Ball& ball, Pad& rectangle1, Pad& rectangle2, Pad& middleRectangle)
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "raylib [core] example - keyboard input");

	initBall(ball);

	initPad1(rectangle1);

	initPad2(rectangle2);

	middleRectangle.x = (float)screenWidth - 420;
	middleRectangle.y = (float)screenHeight / 40;
	middleRectangle.width = (float)screenWidth / 30;
	middleRectangle.height = (float)screenHeight;

}

void inputsSingle(Time& dt, Keyboard keyboard, Pad& rectangle1)
{
	if (keyboard.isKeyPressed(Keyboard::S)) rectangle1.y -= 250.0f * dt.asSeconds();

	if (keyboard.isKeyPressed(Keyboard::W)) rectangle1.y += 250.0f * dt.asSeconds();
}

void inputsMulti(Time& dt, Keyboard keyboard, Pad& rectangle1, Pad& rectangle2)
{
	if (keyboard.isKeyPressed(Keyboard::S)) rectangle1.y -= 250.0f * dt.asSeconds();

	if (keyboard.isKeyPressed(Keyboard::W)) rectangle1.y += 250.0f * dt.asSeconds();

	if (keyboard.isKeyPressed(Keyboard::Down)) rectangle2.y -= 250.0f * dt.asSeconds();

	if (keyboard.isKeyPressed(Keyboard::Up)) rectangle2.y += 250.0f * dt.asSeconds();
}

void drawGame(Ball& ball, Pad& rectangle1, Pad& rectangle2, Pad& middleRectangle, Texture texBall, Texture texPadOne, Texture texPadTwo, Texture texField, bool pause, int winPoints, Texture textMenuPause)
{
	string textPoints1 = to_string(rectangle1.score);
	string textPoints2 = to_string(rectangle2.score);

	slSetForeColor(1, 1, 1, 1);
	slSetTextAlign(SL_ALIGN_LEFT);

	slSetFontSize(25);

	slSprite(texField, 400, 225, 800, 450);

	slText(200, 400, textPoints1.c_str());

	slText(600, 400, textPoints2.c_str());

	slSetFontSize(20);

	slText(20, 20, "Press BackSpace to pause");

	slSprite(texBall, ball.x, ball.y, ball.width, ball.height);

	slSprite(texPadOne, rectangle1.x, rectangle1.y, rectangle1.width, rectangle1.height);

	slSprite(texPadTwo, rectangle2.x, rectangle2.y, rectangle2.width, rectangle2.height);

	if (rectangle1.score == winPoints)
	{
		slSetTextAlign(SL_ALIGN_LEFT);
		slSetForeColor(1, 0, 0, 1);

		slSetFontSize(20);
		slText(20, 420, "Player 1 has won");
		slSetForeColor(1, 1, 1, 1);
		slText(20, 390, "Press ESC to return to the menu");
		slText(20, 370, "or Enter to play again");
	}

	if (rectangle2.score == winPoints)
	{
		slSetTextAlign(SL_ALIGN_RIGHT);
		slSetForeColor(1, 0, 0, 1);

		slSetFontSize(20);
		slText(600, 420, "Player 2 has won");
		slSetForeColor(1, 1, 1, 1);
		slText(800, 390, "Press enter to return to the menu");
		slText(650, 370, "or Enter to play again");
	}

	if (pause)
	{
		slSetTextAlign(SL_ALIGN_LEFT);
		slSetForeColor(0, 0, 0, 1);

		slSetForeColor(1, 1, 1, 1);
		slSprite(textMenuPause, GetScreenWidth() / 2, GetScreenHeight() / 2, 400, 200);
		slSetForeColor(0, 0, 0, 1);
		slSetFontSize(40);
		slText(230, 270, "PAUSED");
		slSetFontSize(20);
		slText(230, 230, "Use ESC to go to the menu");
		slText(230, 190, "or Enter to continue");
	}
}

void drawRules(Texture texField)
{
	slSetBackColor(0.0, 0.0, 0.0);

	slSprite(texField, 400, 225, 800, 450);

	slSetTextAlign(SL_ALIGN_LEFT);

	slSetFontSize(20);

	slSetForeColor(1, 1, 1, 1);

	slText(20, 430, "- Player 1 has to move the left pad up and down with");

	slText(20, 410, "   the W and S keys.");

	slText(20, 390, "- Player 2 has to move the right pad up and down with the up and");

	slText(20, 370, "   down keys.");

	slText(20, 350, "- The first one getting five points wins.");

	slText(20, 330, "To ESC to the menu press enter.");

}

void updateSingleplayer(Time& dt, Keyboard keyboard, Ball& ball, Pad& rectangle1, Pad& rectangle2, GameScreen& currentScreen, bool& gameOver, int winPoints, bool& pause, int& currentOption)
{
	PausedGame(pause, currentScreen, rectangle1, rectangle2, ball, gameOver);

	if (!gameOver && !pause)
	{
		inputsSingle(rectangle1);

		ball.x += ball.speedX * dt.asSeconds();
		ball.y += ball.speedY * dt.asSeconds();

		if (ball.y >= (GetScreenHeight() - ball.height))
		{
			ball.speedY *= -1.0f;
			ball.y = GetScreenHeight() - ball.height;
		}
		if (ball.y < 0)
		{
			ball.speedY *= -1.0f;
			ball.y = 0;
		}

		if (isColliding(rectangle1, ball))
		{
			ball.x = rectangle1.x + rectangle1.width / 2 + ball.width / 2;
			ball.speedX *= -1.1f;
			ball.speedY *= 1.1f;
		}

		if (isColliding(rectangle2, ball))
		{
			ball.x = rectangle2.x - rectangle2.width / 2 - ball.width / 2;
			ball.speedX *= -1.1f;
			ball.speedY *= 1.1f;
		}

		if (rectangle2.y + rectangle2.height / 2 > ball.y)
		{
			rectangle2.y -= 210.0f * dt.asSeconds();
		}
		if (rectangle2.y + rectangle2.height / 2 <= ball.y)
		{
			rectangle2.y += 210.0f * dt.asSeconds();
		}

		if (ball.x + ball.width / 2 >= 800)
		{
			rectangle1.score++;
			ResetBall(ball);
		}
		if (ball.x - ball.width / 2 <= 0)
		{
			rectangle2.score++;
			ResetBall(ball);
		}
		Limit(rectangle1);
		Limit(rectangle2);
	}

	if (rectangle1.score == winPoints)
	{
		gameOver = true;

		if (keyboard.isKeyPressed(Keyboard::Escape))
		{
			returnToMenu(currentScreen, rectangle1, rectangle2, ball, gameOver);
			currentOption = 0;
		}
		if (keyboard.isKeyPressed(Keyboard::Enter))
		{
			ResetGame(rectangle1, rectangle2, ball, gameOver);
		}
	}

	if (rectangle2.score == winPoints)
	{
		gameOver = true;

		if (keyboard.isKeyPressed(Keyboard::Escape))
		{
			returnToMenu(currentScreen, rectangle1, rectangle2, ball, gameOver);
			currentOption = 0;
		}
		if (keyboard.isKeyPressed(Keyboard::Enter))
		{
			ResetGame(rectangle1, rectangle2, ball, gameOver);
		}
	}

}

void updateMultiplayer(Time& dt, Keyboard keyboard, Ball& ball, Pad& rectangle1, Pad& rectangle2, GameScreen& currentScreen, bool& gameOver, int winPoints, bool& pause, int& currentOption)
{
	PausedGame(pause, currentScreen, rectangle1, rectangle2, ball, gameOver);

	if (!gameOver && !pause)
	{
		inputsMulti(rectangle1, rectangle2);

		ball.x += ball.speedX * dt.asSeconds();
		ball.y += ball.speedY * dt.asSeconds();

		if (ball.y >= (GetScreenHeight() - ball.height))
		{
			ball.speedY *= -1.0f;
			ball.y = GetScreenHeight() - ball.height;
		}
		if (ball.y < 0)
		{
			ball.speedY *= -1.0f;
			ball.y = 0;
		}

		if (isColliding(rectangle1, ball))
		{
			ball.x = rectangle1.x + ball.width;
			ball.speedX *= -1.1f;
			ball.speedY *= 1.1f;
		}

		if (isColliding(rectangle2, ball))
		{
			ball.x = rectangle2.x - ball.width;
			ball.speedX *= -1.1f;
			ball.speedY *= 1.1f;
		}

		if (ball.x + ball.width / 2 >= GetScreenWidth())
		{
			rectangle1.score++;
			ResetBall(ball);
		}
		if (ball.x - ball.width / 2 <= 0)
		{
			rectangle2.score++;
			ResetBall(ball);
		}

		Limit(rectangle1);
		Limit(rectangle2);

	}

	if (rectangle1.score == winPoints)
	{
		gameOver = true;

		if (keyboard.isKeyPressed(Keyboard::Escape))
		{
			returnToMenu(currentScreen, rectangle1, rectangle2, ball, gameOver);
			currentOption = 0;
		}
		if (keyboard.isKeyPressed(Keyboard::Enter))
		{
			ResetGame(rectangle1, rectangle2, ball, gameOver);
		}
	}

	if (rectangle2.score == winPoints)
	{
		gameOver = true;

		if (keyboard.isKeyPressed(Keyboard::Escape))
		{
			ResetGame(rectangle1, rectangle2, ball, gameOver);
			currentOption = 0;
			currentScreen = GameScreen::MENU;
		}

		if (keyboard.isKeyPressed(Keyboard::Enter))
		{
			ResetGame(rectangle1, rectangle2, ball, gameOver);
		}
	}
}

void close()
{

}