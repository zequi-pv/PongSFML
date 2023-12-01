#include "Game.h"

#include <time.h>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "elements/Ball.h"
#include "elements/Pad.h"
#include "elements/Button.h"

using namespace std;
using namespace sf;

namespace pong 
{
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

	RectangleShape singlePlayerRect;
	RectangleShape multiPlayerRect;
	RectangleShape rulesRect;
	RectangleShape creditsRect;
	RectangleShape exitRect;
	RectangleShape backRect;
	RectangleShape continueRect;

	Button singlePlayerB;
	Button multiPlayerB;
	Button rulesB;
	Button creditsB;
	Button exitB;
	Button backB;
	Button continueB;

	static void init(Ball& ball, Pad& rectangle1, Pad& rectangle2);
	static void initTextures(Texture& texBall, Texture& texPadOne, Texture& texPadTwo,
		Texture& texField, Texture& textMenuPause);
	static void initFont();
	static void initSprites(Texture& texBall, Texture& texPadOne, Texture& texPadTwo,
		Texture& texField, Texture& textMenuPause);
	static void pausedGame(Keyboard keyboard, bool& pause, GameScreen& currentScreen, Pad& rectangle1, Pad& rectangle2, Ball& ball, bool& gameOver);
	static void resetGame(Pad& rectangle1, Pad& rectangle2, Ball& ball, bool& gameOver);
	static void drawField();
	static void drawObjects(Ball ball, Pad rectangle1, Pad rectangle2);
	static void drawGame(Ball& ball, Pad& rectangle1, Pad& rectangle2, bool pause, int winPoints, bool gameOver);
	static void drawRules();
	static void returnToMenu(GameScreen& currentScreen, Pad& rectangle1, Pad& rectangle2, Ball& ball, bool& gameOver);
	static void inputsSingle(Time& dt, Keyboard keyboard, Pad& rectangle1);
	static void updateSingleplayer(Time& dt, Keyboard keyboard, Ball& ball, Pad& rectangle1, Pad& rectangle2, GameScreen& currentScreen,
		bool& gameOver, int winPoints, bool& pause, int& currentOption);
	static void inputsMulti(Time& dt, Keyboard keyboard, Pad& rectangle1, Pad& rectangle2);
	static void updateMultiplayer(Time& dt, Keyboard keyboard, Ball& ball, Pad& rectangle1, Pad& rectangle2, GameScreen& currentScreen,
		bool& gameOver, int winPoints, bool& pause, int& currentOption);
	void drawText(Text text);
	/*bool optionsCollision(RectangleShape buttonRect, Mouse mouse);
	void buttonIsSelected(Button& button, RectangleShape buttonRect, Mouse mouse);*/
	void close();

	RenderWindow* window;
	Font font;

	void runGame()
	{
		srand(static_cast<unsigned int>(time(NULL)));

		Clock clock;

		Time dt;

		Keyboard keyboard;



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

		init(ball, rectangle1, rectangle2);
		initTextures(texBall, texPadOne, texPadTwo, texField, textMenuPause);
		initFont();
		initSprites(texBall, texPadOne, texPadTwo, texField, textMenuPause);

		singlePlayerB = initButton();
		multiPlayerB = initButton();
		rulesB = initButton();
		creditsB = initButton();
		exitB = initButton();
		backB = initButton();
		continueB = initButton();

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

		while (window->isOpen() && isGameRunning)
		{
			Mouse mouse;
			mouse.getPosition();


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

				isGameRunning = false;


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

				drawField();

				title1.setCharacterSize(50);
				title1.setFillColor(Color::Blue);
				title1.setPosition(312, 70);
				title1.setString("SUPER");
				title1.setFont(font);
				drawText(title1);
				
				

				title2.setCharacterSize(50);
				title2.setFillColor(Color::Yellow);
				title2.setPosition(260, 110);
				title2.setString("CHAMPION");
				drawText(title2);

				title3.setCharacterSize(50);
				title3.setFillColor(Color::Red);
				title3.setPosition(320, 150);
				title3.setString("PONG");
				drawText(title3);

				/*singlePlayerB.pos = { 320, 235 };
				singlePlayerRect.setSize(singlePlayerB.size);
				singlePlayerRect.setPosition(singlePlayerB.pos.x, singlePlayerB.pos.y);
				window->draw(singlePlayerRect);

				buttonIsSelected(singlePlayerB, singlePlayerRect, mouse);

				if (mouse.isButtonPressed(Mouse::Left) && singlePlayerB.isSelected)
				{
					currentScreen = GameScreen::SINGLEPLAYER;
				}*/

				singlePlayer.setCharacterSize(20);
				singlePlayer.setFillColor(Color::Black);
				singlePlayer.setPosition(320, 230);
				singlePlayer.setString("SINGLE PLAYER");
				drawText(singlePlayer);

				multiPlayer.setCharacterSize(20);
				multiPlayer.setFillColor(Color::Black);
				multiPlayer.setPosition(320, 250);
				multiPlayer.setString("MULTI PLAYER");
				drawText(multiPlayer);

				rules.setCharacterSize(20);
				rules.setFillColor(Color::Black);
				rules.setPosition(320, 270);
				rules.setString("RULES");
				drawText(rules);

				credits.setCharacterSize(20);
				credits.setFillColor(Color::Black);
				credits.setPosition(320, 290);
				credits.setString("CREDITS");
				drawText(credits);

				exit.setCharacterSize(20);
				exit.setFillColor(Color::Black);
				exit.setPosition(320, 310);
				exit.setString("EXIT");
				drawText(exit);


				/*slText(600, 80, "Use the up and down keys ");
				slText(600, 50, "to move through the menu!");

				slSetForeColor(1, 1, 1, 1);*/

				switch (currentOption)
				{
				case SINGLEPLAYER:
					singlePlayer.setCharacterSize(20);
					singlePlayer.setFillColor(Color::Red);
					singlePlayer.setPosition(320, 230);
					singlePlayer.setString("SINGLE PLAYER");
					drawText(singlePlayer);

					break;
				case MULTIPLAYER:
					multiPlayer.setCharacterSize(20);
					multiPlayer.setFillColor(Color::Red);
					multiPlayer.setPosition(320, 250);
					multiPlayer.setString("MULTI PLAYER");
					drawText(multiPlayer);

					break;
				case RULES:
					rules.setCharacterSize(20);
					rules.setFillColor(Color::Red);
					rules.setPosition(320, 270);
					rules.setString("RULES");
					drawText(rules);

					break;

				case CREDITS:
					credits.setCharacterSize(20);
					credits.setFillColor(Color::Red);
					credits.setPosition(320, 290);
					credits.setString("CREDITS");
					drawText(credits);
					break;

				case EXIT:
					exit.setCharacterSize(20);
					exit.setFillColor(Color::Red);
					exit.setPosition(320, 310);
					exit.setString("EXIT");
					drawText(exit);
					break;
				}

				break;
			case SINGLEPLAYER:
				window->clear(Color::White);
				drawGame(ball, rectangle1, rectangle2, pause, winPoints, gameOver);
				break;
			case MULTIPLAYER:
				window->clear(Color::White);
				drawGame(ball, rectangle1, rectangle2, pause, winPoints, gameOver);
				break;
			case RULES:
				window->clear(Color::White);
				drawRules();
				break;
			case CREDITS:
				//slText(170, 20, "Made by Ezequiel Prieto"); credits
				break;
			case EXIT:
				break;
			default:
				break;
			}

			window->display();
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

	void init(Ball& ball, Pad& rectangle1, Pad& rectangle2)
	{
		window = new RenderWindow();

		const int screenWidth = 800;
		const int screenHeight = 450;

		window->create(sf::VideoMode(screenWidth, screenHeight), "Pong with SFML");

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

	void initFont()
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

	void drawField()
	{
		fieldSprite.setPosition(0.0f, 0.0f);
		fieldSprite.setScale(1.0f, 1.0f);
		window->draw(fieldSprite);
	}

	void drawObjects(Ball ball, Pad rectangle1, Pad rectangle2)
	{
		ballSprite.setPosition(ball.x, ball.y);
		ballSprite.setScale(1.0f, 1.0f);
		window->draw(ballSprite);

		padOneSprite.setPosition(rectangle1.x + static_cast<float>(rectangle1.width / 2), rectangle1.y - static_cast<float>(rectangle1.height / 2));
		padOneSprite.setScale(1.0f, 1.0f);
		window->draw(padOneSprite);

		padTwoSprite.setPosition(rectangle2.x - static_cast<float>(rectangle2.width / 2), rectangle2.y - static_cast<float>(rectangle2.height / 2));
		padTwoSprite.setScale(1.0f, 1.0f);
		window->draw(padTwoSprite);
	}

	void drawGame(Ball& ball, Pad& rectangle1, Pad& rectangle2, bool pause, int winPoints, bool gameOver)
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

		drawField();

		points1.setCharacterSize(25);
		points1.setFillColor(Color::Black);
		points1.setPosition(static_cast<float>((GetScreenWidth() / 2) - 50), 20.0f);
		points1.setString(textPoints1.c_str());
		drawText(points1);

		points2.setCharacterSize(25);
		points2.setFillColor(Color::Black);
		points2.setPosition(static_cast<float>((GetScreenWidth() / 2) + 50), 20);
		points2.setString(textPoints2.c_str());
		drawText(points2);

		if (!gameOver)
		{
			returnTomenuKey.setCharacterSize(15);
			returnTomenuKey.setFillColor(Color::Black);
			returnTomenuKey.setPosition(20, 420);
			returnTomenuKey.setString("Press BackSpace to pause");
			drawText(returnTomenuKey);
		}
		
		drawObjects(ball, rectangle1, rectangle2);

		if (rectangle1.score == winPoints)
		{
			player1Won1.setCharacterSize(20);
			player1Won1.setFillColor(Color::Red);
			player1Won1.setPosition(static_cast<float>(GetScreenWidth() / 2) - 100, static_cast<float>(GetScreenHeight() / 2 - 20));
			player1Won1.setString("Player 1 has won");
			drawText(player1Won1);

			player1Won2.setCharacterSize(20);
			player1Won2.setFillColor(Color::Red);
			player1Won2.setPosition(static_cast<float>(GetScreenWidth() / 2) - 100, static_cast<float>(GetScreenHeight() / 2));
			player1Won2.setString("Press ESC to return to the menu");
			drawText(player1Won2);

			player1Won3.setCharacterSize(20);
			player1Won3.setFillColor(Color::Red);
			player1Won3.setPosition(static_cast<float>(GetScreenWidth() / 2) - 100, static_cast<float>(GetScreenHeight() / 2 + 20));
			player1Won3.setString("or Enter to play again");
			drawText(player1Won3);
		}

		if (rectangle2.score == winPoints)
		{
			player2Won1.setCharacterSize(20);
			player2Won1.setFillColor(Color::Blue);
			player2Won1.setPosition(20, 420);
			player2Won1.setString("Player 2 has won");
			drawText(player2Won1);

			player2Won2.setCharacterSize(20);
			player2Won2.setFillColor(Color::Blue);
			player2Won2.setPosition(20, 390);
			player2Won2.setString("Press ESC to return to the menu");
			drawText(player2Won2);

			player2Won3.setCharacterSize(20);
			player2Won3.setFillColor(Color::Blue);
			player2Won3.setPosition(20, 370);
			player2Won3.setString("or Enter to play again");
			drawText(player2Won3);
		}

		if (pause)
		{
			pause1.setCharacterSize(40);
			pause1.setFillColor(Color::Black);
			pause1.setPosition(230, 270);
			pause1.setString("PAUSED");
			drawText(pause1);

			pause2.setCharacterSize(40);
			pause2.setFillColor(Color::Black);
			pause2.setPosition(230, 230);
			pause2.setString("Use ESC to go to the menu");
			drawText(pause2);

			pause3.setCharacterSize(40);
			pause3.setFillColor(Color::Black);
			pause3.setPosition(230, 190);
			pause3.setString("or Enter to continue");
			drawText(pause3);

			pauseMenuSprite.setPosition(static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2));
			pauseMenuSprite.setScale(1.0f, 1.0f);
			window->draw(pauseMenuSprite);

			/*slSprite(textMenuPause, GetScreenWidth() / 2, GetScreenHeight() / 2, 400, 200);*/
		}
	}

	void drawRules()
	{
		Text rules1;
		Text rules2;
		Text rules3;
		Text rules4;
		Text rules5;
		Text rules6;

		/*slSetBackColor(0.0, 0.0, 0.0);*/

		drawField();

		rules1.setCharacterSize(20);
		rules1.setFillColor(Color::Black);
		rules1.setPosition(20, 20);
		rules1.setString("- Player 1 has to move the left pad up and down with");
		drawText(rules1);

		rules2.setCharacterSize(20);
		rules2.setFillColor(Color::Black);
		rules2.setPosition(20, 40);
		rules2.setString("   the W and S keys.");
		drawText(rules2);

		rules3.setCharacterSize(20);
		rules3.setFillColor(Color::Black);
		rules3.setPosition(20, 60);
		rules3.setString("- Player 2 has to move the right pad up and down with the up and");
		drawText(rules3);

		rules4.setCharacterSize(20);
		rules4.setFillColor(Color::Black);
		rules4.setPosition(20, 80);
		rules4.setString("   down keys.");
		drawText(rules4);

		rules5.setCharacterSize(20);
		rules5.setFillColor(Color::Black);
		rules5.setPosition(20, 100);
		rules5.setString("- The first one getting five points wins.");
		drawText(rules5);

		rules6.setCharacterSize(20);
		rules6.setFillColor(Color::Black);
		rules6.setPosition(20, 120);
		rules6.setString("To return to the menu press ESC.");
		drawText(rules6);

	}

	void drawText(Text text)
	{
		text.setFont(font);
		window->draw(text);
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

	/*void buttonIsSelected(Button& button, RectangleShape buttonRect, Mouse mouse)
	{
		if (optionsCollision(buttonRect, mouse))
		{
			button.isSelected = true;
		}
		else if (!optionsCollision(buttonRect, mouse))
		{
			button.isSelected = false;
		}
	}

	bool optionsCollision(RectangleShape buttonRect, Mouse mouse)
	{
		return mouse.getPosition().x > buttonRect.getPosition().x
			&& mouse.getPosition().x < buttonRect.getPosition().x + buttonRect.getSize().x
			&& mouse.getPosition().y > buttonRect.getPosition().y
			&& mouse.getPosition().y < buttonRect.getPosition().y + buttonRect.getSize().y;
	}*/

	void close()
	{
		window->close();
		delete window;
	}
}