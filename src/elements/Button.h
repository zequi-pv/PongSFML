#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

namespace pong {
	struct Button
	{
		sf::Vector2f pos;
		sf::Vector2f size;
		sf::Color buttonColor;
		bool isSelected;
	};

Button initButton();
}
