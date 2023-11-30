#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

namespace pong {
	struct Button
	{
		sf::Vector2f pos;
		sf::Vector2f size;
		string text;
		sf::Color buttonColor;
		sf::Color textColor;
	};
}