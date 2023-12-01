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
	CREDITS,
	EXIT
};

Sprite ballSprite;
Sprite padOneSprite;
Sprite padTwoSprite;
Sprite fieldSprite;
Sprite pauseMenuSprite;

static void init(RenderWindow& window, Ball& ball, Pad& rectangle1, Pad& rectangle2);
static void initTextures(Texture& texBall, Texture& texPadOne, Texture& texPadTwo,
	Texture& texField, Texture& textMenuPause);
static void initFont(Font font);
static void initSprites(Texture& texBall, Texture& texPadOne, Texture& texPadTwo,
	Texture& texField, Texture& textMenuPause);
static void pausedGame(Keyboard keyboard, bool& pause, GameScreen& currentScreen, Pad& rectangle1, Pad& rectangle2, Ball& ball, bool& gameOver);
static void resetGame(Pad& rectangle1, Pad& rectangle2, Ball& ball, bool& gameOver);
static void drawField(RenderWindow& window);
static void drawObjects(RenderWindow& window, Ball ball, Pad rectangle1, Pad rectangle2);
static void drawGame(RenderWindow& window, Ball& ball, Pad& rectangle1, Pad& rectangle2, bool pause, int winPoints);
static void drawRules(RenderWindow& window);
static void returnToMenu(GameScreen& currentScreen, Pad& rectangle1, Pad& rectangle2, Ball& ball, bool& gameOver);
static void inputsSingle(Time& dt, Keyboard keyboard, Pad& rectangle1);
static void updateSingleplayer(Time& dt, Keyboard keyboard, Ball& ball, Pad& rectangle1, Pad& rectangle2, GameScreen& currentScreen,
	bool& gameOver, int winPoints, bool& pause, int& currentOption);
static void inputsMulti(Time& dt, Keyboard keyboard, Pad& rectangle1, Pad& rectangle2);
static void updateMultiplayer(Time& dt, Keyboard keyboard, Ball& ball, Pad& rectangle1, Pad& rectangle2, GameScreen& currentScreen,
	bool& gameOver, int winPoints, bool& pause, int& currentOption);

void runGame()
{
	srand(static_cast<unsigned int>(time(NULL)));

	RenderWindow window;

	Clock clock;

	Time dt;

	Keyboard keyboard;

	Font font;

	Texture texBall;
	Texture texPadOne;
	Texture texPadTwo;
	Texture texField;
	Texture textMenuPause;

	Text title1;
	Text title2;
	Text title3;

	Text singlePlayer;
	Text multiPlayer;
	Text rules;
	Text credits;
	Text exit;

	title1.setFont(font);
	title1.setCharacterSize(30);
	title1.setStyle(sf::Text::Regular);

	Ball ball;
	Pad rectangle1;
	Pad rectangle2;

	GameScreen currentScreen = MENU;

	init(window, ball, rectangle1, rectangle2);
	initTextures(texBall, texPadOne, texPadTwo, texField, textMenuPause);
	initFont(font);
	initSprites(texBall, texPadOne, texPadTwo, texField, textMenuPause);

	/*int initialDirection = rand() % 4 + 1;
	int initialDirectionAgain = rand() % 2 + 1;*/
	int currentOption = 0;
	int firstOption = SINGLEPLAYER;
	int lastOption = EXIT;
	int winPoints = 5;

	float timer = 0;
	float coolDownTime = 0.54f;

	bool gameOver = false;
	bool pause = false;
	bool isGameRunning = true;

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
			updateMultiplayer(dt, keyboard, ball, rectangle1, rectangle2, currentScreen, gameOver, winPoints, pause, currentOption);
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

			/*slSetBackColor(0.0, 0.6, 0.0);
			slSetTextAlign(SL_ALIGN_CENTER);
			slSetForeColor(1, 1, 1, 1);*/

			drawField(window);

			title1.setCharacterSize(50);
			title1.setFillColor(Color::Blue);
			title1.setPosition(400, 320);
			title1.setString("SUPER");

			title2.setCharacterSize(50);
			title2.setFillColor(Color::Yellow);
			title2.setPosition(400, 270);
			title2.setString("CHAMPION");

			title3.setCharacterSize(50);
			title3.setFillColor(Color::Red);
			title3.setPosition(400, 220);
			title3.setString("PONG");


			singlePlayer.setCharacterSize(20);
			singlePlayer.setFillColor(Color::White);
			singlePlayer.setPosition(400, 190);
			singlePlayer.setString("SINGLE PLAYER");

			multiPlayer.setCharacterSize(20);
			multiPlayer.setFillColor(Color::White);
			multiPlayer.setPosition(400, 170);
			multiPlayer.setString("MULTI PLAYER");

			rules.setCharacterSize(20);
			rules.setFillColor(Color::White);
			rules.setPosition(400, 150);
			rules.setString("RULES");

			credits.setCharacterSize(20);
			credits.setFillColor(Color::White);
			credits.setPosition(400, 130);
			credits.setString("CREDITS");

			exit.setCharacterSize(20);
			exit.setFillColor(Color::White);
			exit.setPosition(400, 110);
			exit.setString("EXIT");


			/*slText(600, 80, "Use the up and down keys ");
			slText(600, 50, "to move through the menu!");

			slSetForeColor(1, 1, 1, 1);*/

			switch (currentOption)
			{
			case SINGLEPLAYER:
				singlePlayer.setCharacterSize(20);
				singlePlayer.setFillColor(Color::Red);
				singlePlayer.setPosition(400, 190);
				singlePlayer.setString("SINGLE PLAYER");

				break;
			case MULTIPLAYER:
				multiPlayer.setCharacterSize(20);
				multiPlayer.setFillColor(Color::Red);
				multiPlayer.setPosition(400, 170);
				multiPlayer.setString("MULTI PLAYER");

				break;
			case RULES:
				rules.setCharacterSize(20);
				rules.setFillColor(Color::Red);
				rules.setPosition(400, 150);
				rules.setString("RULES");

				break;

			case CREDITS:
				credits.setCharacterSize(20);
				credits.setFillColor(Color::Red);
				credits.setPosition(400, 130);
				credits.setString("CREDITS");
				break;

			case EXIT:
				exit.setCharacterSize(20);
				exit.setFillColor(Color::Red);
				exit.setPosition(400, 110);
				exit.setString("EXIT");
				break;
			}

			break;
		case SINGLEPLAYER:
			window.clear(Color::White);
			drawGame(window, ball, rectangle1, rectangle2, pause, winPoints);
			break;
		case MULTIPLAYER:
			window.clear(Color::White);
			drawGame(window, ball, rectangle1, rectangle2, pause, winPoints);
			break;
		case RULES:
			window.clear(Color::White);
			drawRules(window);
			break;
		case CREDITS:
			//slText(170, 20, "Made by Ezequiel Prieto"); credits
			break;
		case EXIT:
			break;
		default:
			break;
		}

		window.display();
	}

	window.close();
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

void pausedGame(Keyboard keyboard, bool& pause, GameScreen& currentScreen, Pad& rectangle1, Pad& rectangle2, Ball& ball, bool& gameOver)
{
	if (keyboard.isKeyPressed(Keyboard::BackSpace))
	{
		pause = true;
	}
	if (keyboard.isKeyPressed(Keyboard::Enter))
	{
		pause = false;
	}
	if (keyboard.isKeyPressed(Keyboard::Escape))
	{
		returnToMenu(currentScreen, rectangle1, rectangle2, ball, gameOver);
	}
}

void resetGame(Pad& rectangle1, Pad& rectangle2, Ball& ball, bool& gameOver)
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
	resetGame(rectangle1, rectangle2, ball, gameOver);
	currentScreen = GameScreen::MENU;
}

void ResetBall(Ball& ball)
{
	int direction = rand() % 4 + 1;
	ball.speedX = 250.0f;
	ball.speedY = 250.0f;

	ball.x = static_cast<float>(GetScreenWidth() / 2);
	ball.y = static_cast<float>(GetScreenHeight() / 2);

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

void init(RenderWindow& window, Ball& ball, Pad& rectangle1, Pad& rectangle2)
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	window.create(sf::VideoMode(screenWidth, screenHeight), "Pong with SFML");

	initBall(ball);

	initPad1(rectangle1);

	initPad2(rectangle2);
}

void initTextures(Texture& texBall, Texture& texPadOne, Texture& texPadTwo,
	Texture& texField, Texture& textMenuPause)
{
	texBall.loadFromFile("res/assets/Ball.png");

	texPadOne.loadFromFile("res/assets/PadTwo.png");

	texPadTwo.loadFromFile("res/assets/PadOne.png");

	texField.loadFromFile("res/assets/Field.png");

	textMenuPause.loadFromFile("res/assets/PauseMenu.png");
}

void initSprites(Texture& texBall, Texture& texPadOne, Texture& texPadTwo,
	Texture& texField, Texture& textMenuPause)
{
	ballSprite.setTexture(texBall);

	padOneSprite.setTexture(texPadOne);

	padTwoSprite.setTexture(texPadTwo);

	fieldSprite.setTexture(texField);

	pauseMenuSprite.setTexture(textMenuPause);
}

void initFont(Font font)
{
	font.loadFromFile("res/fonts/BoaConstruktorBold.ttf");
}

void inputsSingle(Time& dt, Keyboard keyboard, Pad& rectangle1)
{
	if (keyboard.isKeyPressed(Keyboard::W)) rectangle1.y -= 250.0f * dt.asSeconds();

	if (keyboard.isKeyPressed(Keyboard::S)) rectangle1.y += 250.0f * dt.asSeconds();
}

void inputsMulti(Time& dt, Keyboard keyboard, Pad& rectangle1, Pad& rectangle2)
{
	if (keyboard.isKeyPressed(Keyboard::W)) rectangle1.y -= 250.0f * dt.asSeconds();

	if (keyboard.isKeyPressed(Keyboard::S)) rectangle1.y += 250.0f * dt.asSeconds();

	if (keyboard.isKeyPressed(Keyboard::Up)) rectangle2.y -= 250.0f * dt.asSeconds();

	if (keyboard.isKeyPressed(Keyboard::Down)) rectangle2.y += 250.0f * dt.asSeconds();
}

void drawField(RenderWindow& window)
{
	fieldSprite.setPosition(0.0f, 0.0f);
	fieldSprite.setScale(1.0f, 1.0f);
	window.draw(fieldSprite);
}

void drawObjects(RenderWindow& window, Ball ball, Pad rectangle1, Pad rectangle2)
{
	ballSprite.setPosition(ball.x, ball.y);
	ballSprite.setScale(1.0f, 1.0f);
	window.draw(ballSprite);

	padOneSprite.setPosition(rectangle1.x, rectangle1.y);
	padOneSprite.setScale(1.0f, 1.0f);
	window.draw(padOneSprite);

	padTwoSprite.setPosition(rectangle2.x, rectangle2.y);
	padTwoSprite.setScale(1.0f, 1.0f);
	window.draw(padTwoSprite);
}

void drawGame(RenderWindow& window, Ball& ball, Pad& rectangle1, Pad& rectangle2, bool pause, int winPoints)
{
	string textPoints1 = to_string(rectangle1.score);
	string textPoints2 = to_string(rectangle2.score);

	Text points1;
	Text points2;

	Text returnTomenuKey;

	Text player1Won1;
	Text player1Won2;
	Text player1Won3;

	Text player2Won1;
	Text player2Won2;
	Text player2Won3;

	Text pause1;
	Text pause2;
	Text pause3;

	points1.setCharacterSize(25);
	points1.setFillColor(Color::Black);
	points1.setPosition(200, 400);
	points1.setString(textPoints1.c_str());

	points2.setCharacterSize(25);
	points2.setFillColor(Color::Black);
	points2.setPosition(600, 400);
	points2.setString(textPoints2.c_str());

	returnTomenuKey.setCharacterSize(25);
	returnTomenuKey.setFillColor(Color::Black);
	returnTomenuKey.setPosition(20, 20);
	returnTomenuKey.setString("Press BackSpace to pause");

	drawField(window);

	drawObjects(window, ball, rectangle1, rectangle2);

	if (rectangle1.score == winPoints)
	{
		player1Won1.setCharacterSize(20);
		player1Won1.setFillColor(Color::Red);
		player1Won1.setPosition(20, 420);
		player1Won1.setString("Player 1 has won");

		player1Won2.setCharacterSize(20);
		player1Won2.setFillColor(Color::Red);
		player1Won2.setPosition(20, 390);
		player1Won2.setString("Press ESC to return to the menu");

		player1Won3.setCharacterSize(20);
		player1Won3.setFillColor(Color::Red);
		player1Won3.setPosition(20, 370);
		player1Won3.setString("or Enter to play again");
	}

	if (rectangle2.score == winPoints)
	{
		player2Won1.setCharacterSize(20);
		player2Won1.setFillColor(Color::Blue);
		player2Won1.setPosition(20, 420);
		player2Won1.setString("Player 2 has won");

		player2Won2.setCharacterSize(20);
		player2Won2.setFillColor(Color::Blue);
		player2Won2.setPosition(20, 390);
		player2Won2.setString("Press ESC to return to the menu");

		player2Won3.setCharacterSize(20);
		player2Won3.setFillColor(Color::Blue);
		player2Won3.setPosition(20, 370);
		player2Won3.setString("or Enter to play again");
	}

	if (pause)
	{
		pause1.setCharacterSize(40);
		pause1.setFillColor(Color::Black);
		pause1.setPosition(230, 270);
		pause1.setString("PAUSED");

		pause2.setCharacterSize(40);
		pause2.setFillColor(Color::Black);
		pause2.setPosition(230, 230);
		pause2.setString("Use ESC to go to the menu");

		pause3.setCharacterSize(40);
		pause3.setFillColor(Color::Black);
		pause3.setPosition(230, 190);
		pause3.setString("or Enter to continue");

		/*slSprite(textMenuPause, GetScreenWidth() / 2, GetScreenHeight() / 2, 400, 200);*/
	}
}

void drawRules(RenderWindow& window)
{
	Text rules1;
	Text rules2;
	Text rules3;
	Text rules4;
	Text rules5;
	Text rules6;

	/*slSetBackColor(0.0, 0.0, 0.0);*/

	drawField(window);

	rules1.setCharacterSize(20);
	rules1.setFillColor(Color::White);
	rules1.setPosition(20, 430);
	rules1.setString("- Player 1 has to move the left pad up and down with");

	rules2.setCharacterSize(20);
	rules2.setFillColor(Color::White);
	rules2.setPosition(20, 410);
	rules2.setString("   the W and S keys.");

	rules3.setCharacterSize(20);
	rules3.setFillColor(Color::White);
	rules3.setPosition(20, 390);
	rules3.setString("- Player 2 has to move the right pad up and down with the up and");

	rules4.setCharacterSize(20);
	rules4.setFillColor(Color::White);
	rules4.setPosition(20, 370);
	rules4.setString("   down keys.");

	rules5.setCharacterSize(20);
	rules5.setFillColor(Color::White);
	rules5.setPosition(20, 350);
	rules5.setString("- The first one getting five points wins.");

	rules6.setCharacterSize(20);
	rules6.setFillColor(Color::White);
	rules6.setPosition(20, 330);
	rules6.setString("To return to the menu press enter.");

}

void updateSingleplayer(Time& dt, Keyboard keyboard, Ball& ball, Pad& rectangle1, Pad& rectangle2, GameScreen& currentScreen, bool& gameOver, int winPoints, bool& pause, int& currentOption)
{
	pausedGame(keyboard, pause, currentScreen, rectangle1, rectangle2, ball, gameOver);

	if (!gameOver && !pause)
	{
		inputsSingle(dt, keyboard, rectangle1);

		ball.x += ball.speedX * dt.asSeconds();
		ball.y += ball.speedY * dt.asSeconds();

		if (ball.y >= (GetScreenHeight() - ball.height))
		{
			ball.speedY *= -1.0f;
			ball.y = static_cast<float>(GetScreenHeight() - ball.height);
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
			resetGame(rectangle1, rectangle2, ball, gameOver);
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
			resetGame(rectangle1, rectangle2, ball, gameOver);
		}
	}

}

void updateMultiplayer(Time& dt, Keyboard keyboard, Ball& ball, Pad& rectangle1, Pad& rectangle2, GameScreen& currentScreen, bool& gameOver, int winPoints, bool& pause, int& currentOption)
{
	pausedGame(keyboard, pause, currentScreen, rectangle1, rectangle2, ball, gameOver);

	if (!gameOver && !pause)
	{
		inputsMulti(dt, keyboard, rectangle1, rectangle2);

		ball.x += ball.speedX * dt.asSeconds();
		ball.y += ball.speedY * dt.asSeconds();

		if (ball.y >= (GetScreenHeight() - ball.height))
		{
			ball.speedY *= -1.0f;
			ball.y = static_cast<float>(GetScreenHeight() - ball.height);
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
			resetGame(rectangle1, rectangle2, ball, gameOver);
		}
	}

	if (rectangle2.score == winPoints)
	{
		gameOver = true;

		if (keyboard.isKeyPressed(Keyboard::Escape))
		{
			resetGame(rectangle1, rectangle2, ball, gameOver);
			currentOption = 0;
			currentScreen = GameScreen::MENU;
		}

		if (keyboard.isKeyPressed(Keyboard::Enter))
		{
			resetGame(rectangle1, rectangle2, ball, gameOver);
		}
	}
}