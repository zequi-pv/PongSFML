#include "Button.h"

namespace pong
{
	Button initButton()
	{
		Button button;
		button.size = { 170.0f, 20.0f };
		button.buttonColor = Color::White;
		button.isSelected = false;
		return button;
	}
}