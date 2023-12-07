#include "buttons.h"

void Button::buttonFill()
{
}

void Button::buttonDefault()
{
}

void Button::buttonPressed()
{
}


void Button::changePosition(int positionX, int positionY)
{
}


SliderButton::SliderButton(int minValue, int maxValue, std::string sliderName, int sliderValue, int sliderPositionX, int sliderPositionY, Orientation orientation)
	: minValue(minValue), maxValue(maxValue),
	sliderName(sliderName), sliderValue(sliderValue),
	sliderPositionX(sliderPositionX), sliderPositionY(sliderPositionY),
	orientation(orientation)
{
	temp = sliderValue;
	buttonFill();
}

void SliderButton::buttonFill() {
	if (orientation == Orientation::HORIZONTAL) {
		sliderWidth = static_cast<int>((maxValue - minValue) + 3); //ñ÷èòàåì øèðèíó ñëàéäðà
		sliderValue -= minValue;
		arr.resize(sliderHeight);
		for (int i = 0; i < sliderHeight; i++) {
			for (int j = 0; j < sliderWidth; j++) {   //ñîçäà¸ì âåêòîð äëÿ õðàíåíèÿ ñëàéäåðà
				arr[i].push_back(' ');
			}
		}
		char a = 17;
		char b = 16;
		arr[sliderHeight - 2][0] = a;
		arr[sliderHeight - 2][sliderWidth - 1] = b;
		arr[sliderHeight - 1][0] = '-';
		arr[sliderHeight - 1][sliderWidth - 1] = '+';
		for (int i = 1; i < sliderWidth - 1; i++) {
			arr[sliderHeight - 2][i] = '-';
		}
		for (int i = 0, j = (sliderWidth - static_cast<int>(sliderName.size())) / 2; i < static_cast<int>(sliderName.size()); i++, j++) { //îòîáðàæåíèå èìåíè ñëàéäåðà
			arr[0][j] = sliderName[i];
		}
		std::string s = std::to_string(sliderValue + minValue);
		for (int i = 0, j = (sliderWidth - static_cast<int>(s.size())) / 2; i < static_cast<int>(s.size()); i++, j++) {  //îòîáðàæåíèÿ ñîñòîÿíèÿ ñëàéäåðà
			arr[sliderHeight - 1][j] = s[i];
		}
		arr[sliderHeight - 2][sliderValue + 1] = 219;  //ïîëçóíîê ñëàéäåðà
	}
	else if (orientation == Orientation::VERTICAL)
	{
		double V = sliderValue;
		((maxValue - minValue + 1) % 2 == 0) ? sliderHeight = ((maxValue - minValue + 1) / 2) + 4 : sliderHeight = ((maxValue - minValue + 1) / 2) + 5; //âûñîòà
		sliderWidth = (sliderName.size() >= 3) ? sliderName.size() + 2 : 5;  //øèðèíà
		V = sliderValue - minValue;
		V = V / 2 - 1;
		arr.resize(sliderHeight);
		for (int i = 0; i < sliderHeight; i++)
		{
			for (int j = 0; j < sliderWidth; j++)    //ñîçäà¸ì âåòîð äëÿ ñëàéäåðà
			{
				arr[i].push_back(' ');
			}
		}

		arr[1][static_cast<std::vector<char, std::allocator<char>>::size_type>(sliderWidth / 2) + 1] = char(30);
		arr[sliderHeight - 2][static_cast<std::vector<char, std::allocator<char>>::size_type>(sliderWidth / 2) + 1] = char(31);

		for (int i = 2; i < sliderHeight - 2; i++) arr[i][sliderWidth / 2 + 1] = char(124);

		for (int i = 0; i < sliderName.size(); i++) arr[0][i + 2] = sliderName[i];

		std::string s = std::to_string(sliderValue);
		for (int i = 0, j = (sliderWidth - s.size()) / 2 + 2; i < s.size(); i++, j++)   //ñîñòîÿíèå ñëàéäåðà
		{
			arr[sliderHeight - 1][j] = s[i];
		}

		if (V - int(V) == 0)
		{
			arr[sliderHeight - 4 - V][sliderWidth / 2 + 2] = char(220);
			arr[sliderHeight - 4 - V][sliderWidth / 2 + 1] = char(220);
			arr[sliderHeight - 4 - V][sliderWidth / 2] = char(220);
		}
		else                                                                    //ñîçäàíèå è óñòàíîâêà íà íóæíóþ ïîçèöèþ ïîëçóíêà
		{
			arr[sliderHeight - 3 - V][sliderWidth / 2 + 2] = char(223);
			arr[sliderHeight - 3 - V][sliderWidth / 2 + 1] = char(223);
			arr[sliderHeight - 3 - V][sliderWidth / 2] = char(223);
		}
	}
}

void SliderButton::buttonDefault() {
	isPressed = false;
	if (orientation == Orientation::HORIZONTAL) {
		arr[0][0] = ' ';
	}
	else {
		setcur(sliderPositionX - 1, sliderPositionY - 1); // óñòðàíåíèå àðòåôàêòîâ
		std::cout << ' ';
		arr[0][0] = ' ';
	}
}

void SliderButton::buttonPressed() {
	isPressed = true;
	if (orientation == Orientation::HORIZONTAL) {
		arr[0][0] = char(223);
		//arr[0][0] = '*';
	}
	else {
		arr[0][0] = char(223);
	}
}

void SliderButton::setValue(int value) {
	if (orientation == Orientation::HORIZONTAL) {
		value -= minValue;
		arr[sliderHeight - 2][sliderValue + 1] = '-';

		std::string s = std::to_string(sliderValue + minValue);

		for (int i = 0, j = (sliderWidth - static_cast<int>(s.size())) / 2; i < static_cast<int>(s.size()); i++, j++) { //çàêðàøèâàåì ïðåäûäóùåå ñîñòîÿíèå ñëàéäåðà
			arr[sliderHeight - 1][j] = ' ';
		}
		if (value >= 0 && value <= maxValue - minValue) sliderValue = value;

		s = std::to_string(sliderValue + minValue);

		for (int i = 0, j = (sliderWidth - static_cast<int>(s.size())) / 2; i < static_cast<int>(s.size()); i++, j++) {  //óñòàíàâëèâàåì íîâîå çíà÷åíèå ñëàéäåðà
			arr[sliderHeight - 1][j] = s[i];
		}

		arr[sliderHeight - 2][sliderValue + 1] = 219;
	}
	else if (orientation == Orientation::VERTICAL) {
		double V;
		V = sliderValue - minValue;
		V = V / 2 - 1;

		if (V - int(V) == 0)                        //çàêðàøèâàåì ïðåäûäóùåå ñîñòîÿíèå ñëàéäåðà
		{
			arr[sliderHeight - 4 - V][sliderWidth / 2 + 2] = ' ';
			arr[sliderHeight - 4 - V][sliderWidth / 2 + 1] = char(124);
			arr[sliderHeight - 4 - V][sliderWidth / 2] = ' ';
		}
		else
		{
			arr[sliderHeight - 3 - V][sliderWidth / 2 + 2] = ' ';
			arr[sliderHeight - 3 - V][sliderWidth / 2 + 1] = char(124);
			arr[sliderHeight - 3 - V][sliderWidth / 2] = ' ';
		}

		std::string s = std::to_string(sliderValue);
		for (int i = 0; i < sliderWidth; i++)
		{
			arr[sliderHeight - 1][i] = ' ';
		}

		if (value >= minValue && value <= maxValue)sliderValue = value; //óñòàíàâëèâàåì íîâîå çíà÷åíèå ñëàéäåðà
		V = sliderValue - minValue;
		V = V / 2 - 1;

		s = std::to_string(sliderValue);
		for (int i = 0, j = (sliderWidth - s.size()) / 2 + 2; i < s.size(); i++, j++)
		{
			arr[sliderHeight - 1][j] = s[i];
		}

		if (V - int(V) == 0)
		{
			arr[sliderHeight - 4 - V][sliderWidth / 2 + 2] = char(220);
			arr[sliderHeight - 4 - V][sliderWidth / 2 + 1] = char(220);
			arr[sliderHeight - 4 - V][sliderWidth / 2] = char(220);
		}
		else
		{
			arr[sliderHeight - 3 - V][sliderWidth / 2 + 2] = char(223);
			arr[sliderHeight - 3 - V][sliderWidth / 2 + 1] = char(223);
			arr[sliderHeight - 3 - V][sliderWidth / 2] = char(223);
		}
	}
}

void SliderButton::show() {
	for (int i = 0; i < sliderHeight; i++) {
		for (int j = 0; j < sliderWidth; j++) {
			setcur(sliderPositionX + j, sliderPositionY + i);  //îòîáðàæàåì ñëàéäåð
			std::cout << arr[i][j];
		}
	}
}

void SliderButton::changePosition(int positionX, int positionY)
{
	this->sliderPositionX = positionX;
	this->sliderPositionY = positionY;
}

void SliderButton::handleMouseEvent(COORD mousePos) {
	if (orientation == Orientation::HORIZONTAL) {
		if (mousePos.X >= sliderPositionX && mousePos.X < sliderPositionX + sliderWidth &&
			mousePos.Y >= sliderPositionY && mousePos.Y < sliderPositionY + sliderHeight) {
			buttonPressed();
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
				if ((mousePos.X == sliderPositionX && mousePos.Y == sliderPositionY + 2) || (mousePos.X == sliderPositionX && mousePos.Y == sliderPositionY + 3)) {
					if (temp > minValue) {
						temp--;
						setValue(temp);
						if (userFunction1 != nullptr)userFunction1();
					}
				}
				else if ((mousePos.X == sliderPositionX + sliderWidth - 1 && mousePos.Y == sliderPositionY + 2) || (mousePos.X == sliderPositionX + sliderWidth - 1 && mousePos.Y == sliderPositionY + 3)) {
					if (temp < maxValue) {
						temp++;
						setValue(temp);
						if (userFunction2 != nullptr)userFunction2();
					}
				}
				else if (mousePos.X >= sliderPositionX + 1 && mousePos.X < sliderPositionX + sliderWidth - 1 && mousePos.Y >= sliderPositionY + 1 && mousePos.Y <= sliderPositionY + 3) {
					int delta = sliderValue + sliderPositionX + 1 - mousePos.X;
					temp -= delta;
					setValue(temp);
					if (delta < 0) {
						for (int i = 0; i < abs(delta); i++)
						{
							if (userFunction2 != nullptr)userFunction2();
						}
					}
					else if (delta > 0) {
						for (int i = 0; i < delta; i++)
						{
							if (userFunction1 != nullptr)userFunction1();
						}
					}
				}
			}

		}
		else {
			buttonDefault();
		}
	}
	else {
		if (mousePos.X >= sliderPositionX && mousePos.X < sliderPositionX + sliderWidth &&
			mousePos.Y >= sliderPositionY && mousePos.Y < sliderPositionY + sliderHeight) {
			if (!isPressed) buttonPressed();
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
				if (mousePos.X == sliderPositionX + sliderWidth / 2 + 1 && mousePos.Y == sliderPositionY + sliderHeight - 2) {
					if (temp > minValue) {
						temp--;
						setValue(temp);
						userFunction1();
					}
				}
				else if (mousePos.X == sliderPositionX + sliderWidth / 2 + 1 && mousePos.Y == sliderPositionY + 1) {
					if (temp < maxValue) {
						temp++;
						setValue(temp);
						userFunction2();
					}
				}
			}

		}
		else {
			buttonDefault();
		}
	}
}

void SliderButton::handleKeyboardEvent(int key)
{
	if (key == 75)
	{
		if (temp > minValue) {
			temp--;
			setValue(temp);
			if (userFunction1 != nullptr)userFunction1();
		}
	}
	else if (key == 77)
	{
		if (temp < maxValue) {
			temp++;
			setValue(temp);
			if (userFunction2 != nullptr)userFunction2();
		}
	}
}

StandartButton::StandartButton(int buttonWidth, int buttonHeight, std::string buttonName, int buttonPositionX, int buttonPositionY)
	: buttonWidth(buttonWidth), buttonHeight(buttonHeight),
	buttonName(buttonName), buttonPositionX(buttonPositionX), buttonPositionY(buttonPositionY)
{
	buttonFill();
}

void StandartButton::buttonFill()
{
	arr.resize(buttonHeight);
	for (int i = 0; i < buttonHeight; i++)
	{
		for (int j = 0; j < buttonWidth; j++)
		{
			arr[i].push_back(' ');
		}
	}
	for (int i = 1; i < buttonHeight - 1; i++)
	{
		for (int j = 1; j < buttonWidth - 1; j++)
		{
			arr[i][j] = ' ';
		}
	}
	for (int i = 0; i < buttonHeight; i++)
	{
		arr[i][0] = verticalLine;
		arr[i][buttonWidth - 1] = verticalLine;
	}
	for (int j = 0; j < buttonWidth; j++)
	{
		arr[0][j] = horizontalLine;
		arr[buttonHeight - 1][j] = horizontalLine;
	}
	arr[0][0] = topLeftCorner;
	arr[buttonHeight - 1][0] = bottomLeftCorner;
	arr[0][buttonWidth - 1] = topRightCorner;
	arr[buttonHeight - 1][buttonWidth - 1] = bottomRightCorner;
	int x = (buttonWidth - static_cast<int>(buttonName.size())) / 2;
	int y = (buttonHeight - 1) / 2;
	for (int i = 0; i < static_cast<int>(buttonName.size()); i++)
	{
		arr[y][x] = buttonName[i];
		x++;
	}
}

void StandartButton::buttonDefault()
{
	isPressed = false;
	for (int i = 0; i < buttonHeight; i++)
	{
		arr[i][0] = verticalLine;
		arr[i][buttonWidth - 1] = verticalLine;
	}
	for (int j = 0; j < buttonWidth; j++)
	{
		arr[0][j] = horizontalLine;
		arr[buttonHeight - 1][j] = horizontalLine;
	}
	arr[0][0] = topLeftCorner;
	arr[buttonHeight - 1][0] = bottomLeftCorner;
	arr[0][buttonWidth - 1] = topRightCorner;
	arr[buttonHeight - 1][buttonWidth - 1] = bottomRightCorner;
}

void StandartButton::buttonPressed()
{
	isPressed = true;
	for (int j = 0; j < buttonWidth; j++)
	{
		arr[0][j] = static_cast<char>(223);
		arr[buttonHeight - 1][j] = static_cast<char>(220);
	}
	for (int i = 0; i < buttonHeight; i++)
	{
		arr[i][0] = static_cast<char>(219);
		arr[i][buttonWidth - 1] = static_cast<char>(219);
	}
}

void StandartButton::show()
{
	for (int i = 0; i < buttonHeight; i++)
	{
		for (int j = 0; j < buttonWidth; j++)
		{
			setcur(buttonPositionX + j, buttonPositionY + i);
			std::cout << arr[i][j];
		}
	}
}

void StandartButton::changePosition(int positionX, int positionY)
{
	this->buttonPositionX = positionX;
	this->buttonPositionY = positionY;
}

void StandartButton::setButtonTexture(char topLeft, char topRight, char bottomLeft, char bottomRight, char horizontal, char vertical) {
	topLeftCorner = topLeft;
	topRightCorner = topRight;
	bottomLeftCorner = bottomLeft;
	bottomRightCorner = bottomRight;
	horizontalLine = horizontal;
	verticalLine = vertical;
	buttonFill();
	show();
}

void StandartButton::handleMouseEvent(COORD mousePos)
{
	if (mousePos.X >= buttonPositionX && mousePos.X < buttonPositionX + buttonWidth &&
		mousePos.Y >= buttonPositionY && mousePos.Y < buttonPositionY + buttonHeight)
	{
		buttonPressed();
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if (userFunction != nullptr)userFunction();
		}
	}
	else
	{
		buttonDefault();
	}
}

void StandartButton::handleKeyboardEvent(int key)
{
	if (key == 13)
	{
		if (userFunction != nullptr)userFunction();
	}
}

SwitchButton::SwitchButton(int switchWidth, int switchHeight, bool stateSwitch, int switchPositionX, int switchPositionY)
	: switchWidth(switchWidth), switchHeight(switchHeight),
	stateSwitch(stateSwitch),
	switchPositionX(switchPositionX), switchPositionY(switchPositionY)
{
	buttonFill();
}

void SwitchButton::buttonFill()
{

	arr.resize(static_cast<std::size_t>(switchHeight));
	for (std::size_t i = 0; i < arr.size(); i++)
	{
		arr[i].resize(static_cast<std::size_t>(switchWidth), ' ');
	}

	for (std::size_t i = 0; i < arr.size(); i++)
	{
		arr[i][0] = '|';
		arr[i][switchWidth - 1] = '|';
	}

	for (int j = 0; j < switchWidth; j++)
	{
		arr[0][j] = '-';
		arr[switchHeight - 1][j] = '-';
	}

	arr[0][0] = static_cast<char>(197);
	arr[switchHeight - 1][0] = static_cast<char>(197);
	arr[0][switchWidth - 1] = static_cast<char>(197);
	arr[switchHeight - 1][switchWidth - 1] = static_cast<char>(197);

	if (!stateSwitch)
	{
		for (int i = 1; i < switchHeight - 1; i++)
		{
			for (int j = 2; j < switchWidth / 2 - 1; j++)
			{
				arr[i][j] = 219;
			}
		}
		state = ":off";
	}
	else
	{
		for (int i = 1; i < switchHeight - 1; i++)
		{
			for (int j = (switchWidth % 2 == 0) ? switchWidth / 2 + 1 : switchWidth / 2 + 2; j < switchWidth - 2; j++)
			{
				arr[i][j] = 219;
			}
		}
		state = ":on";
	}
}

void SwitchButton::buttonDefault()
{
	isPressed = false;
	setcur(switchPositionX - 1, switchPositionY - 1); // óñòðàíåíèå àðòåôàêòîâ
	std::cout << ' ';
	for (int i = 0; i < switchHeight; i++)
	{
		arr[i][0] = '|';
		arr[i][switchWidth - 1] = '|';
	}

	for (int j = 0; j < switchWidth; j++)
	{
		arr[0][j] = '-';
		arr[switchHeight - 1][j] = '-';
	}

	arr[0][0] = static_cast<char>(197);
	arr[switchHeight - 1][0] = static_cast<char>(197);
	arr[0][switchWidth - 1] = static_cast<char>(197);
	arr[switchHeight - 1][switchWidth - 1] = static_cast<char>(197);
}

void SwitchButton::buttonPressed()
{
	isPressed = true;
	for (int j = 0; j < switchWidth; j++)
	{
		arr[0][j] = 223;
		arr[switchHeight - 1][j] = 220;
	}

	for (int i = 0; i < switchHeight; i++)
	{
		arr[i][0] = 219;
		arr[i][switchWidth - 1] = 219;
	}
}

void SwitchButton::show()
{
	for (int i = 0; i < switchHeight; i++)
	{
		for (int j = 0; j < switchWidth; j++)
		{
			setcur(switchPositionX + j, switchPositionY + i);
			std::cout << arr[i][j];
		}
	}
	if (switchName.size() != 0)
	{
		std::string s = switchName + state;
		setcur(switchNamePositionX, switchNamePositionY);
		std::cout << s;
	}
}

void SwitchButton::changePosition(int positionX, int positionY)
{
	this->switchPositionX = positionX;
	this->switchPositionY = positionY;
}

void SwitchButton::setValue(bool value)
{
	this->stateSwitch = value;

	if (!stateSwitch)
	{
		for (int i = 1; i < switchHeight - 1; i++)
		{
			for (int j = 2; j < switchWidth / 2 - 1; j++)
			{
				arr[i][j] = 219;
			}
		}
		state = ":off";
		for (int i = 1; i < switchHeight - 1; i++)
		{
			for (int j = (switchWidth % 2 == 0) ? switchWidth / 2 + 1 : switchWidth / 2 + 2; j < switchWidth - 2; j++)
			{
				arr[i][j] = ' ';
			}
		}
	}
	else
	{
		for (int i = 1; i < switchHeight - 1; i++)
		{
			for (int j = (switchWidth % 2 == 0) ? switchWidth / 2 + 1 : switchWidth / 2 + 2; j < switchWidth - 2; j++)
			{
				arr[i][j] = 219;
			}
		}
		state = ":on ";
		for (int i = 1; i < switchHeight - 1; i++)
		{
			for (int j = 2; j < switchWidth / 2 - 1; j++)
			{
				arr[i][j] = ' ';
			}
		}
	}

	/*std::string s = switchName + state;

	for (std::size_t i = 0; i < s.size() + 1; i++)
	{
		setcur(switchNamePositionX + static_cast<int>(i), switchNamePositionY);
		std::cout << ' ';
	}

	for (std::size_t i = 0; i < s.size(); i++)
	{
		setcur(switchNamePositionX + static_cast<int>(i), switchNamePositionY);
		std::cout << s[i];
	}*/
}

void SwitchButton::addName(std::string name, int namePositionX, int namePositionY)
{
	this->switchName = name;
	this->switchNamePositionX = namePositionX;
	this->switchNamePositionY = namePositionY;
}

void SwitchButton::handleMouseEvent(COORD mousePos)
{
	if (mousePos.X >= switchPositionX && mousePos.X < switchPositionX + switchWidth &&
		mousePos.Y >= switchPositionY && mousePos.Y < switchPositionY + switchHeight)
	{
		if (!isPressed) buttonPressed();

		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if (!stateSwitch)
			{
				setValue(true);
				if (userFunction2 != nullptr)userFunction2();
			}
			else
			{
				setValue(false);
				if (userFunction1 != nullptr)userFunction1();
			}
		}
	}
	else
	{
		buttonDefault();
	}
}

void SwitchButton::handleKeyboardEvent(int key)
{
	if (key == 75)
	{
		if (stateSwitch)
		{
			setValue(false);
			if (userFunction1 != nullptr)userFunction1();
		}
	}
	else if (key == 77)
	{
		if (!stateSwitch)
		{
			setValue(true);
			if (userFunction2 != nullptr)userFunction2();
		}
	}
}

ScrollButton::ScrollButton(std::vector<std::vector<std::vector<char>>>& content, int scrollPositionX, int scrollPositionY, Orientation orientation) :
	content(content), scrollPositionX(scrollPositionX), scrollPositionY(scrollPositionY), orientation(orientation)
{
	buttonFill();
}

void ScrollButton::buttonFill()
{
	if (orientation == Orientation::HORIZONTAL) {
		scrollHeight = content[slideNumber].size();
		scrollWidth = content[slideNumber][0].size() + 4;
	}
	else {
		scrollHeight = content[slideNumber].size() + 2;
		scrollWidth = content[slideNumber][0].size();
	}

	arr.resize(static_cast<std::size_t>(scrollHeight));
	for (std::size_t i = 0; i < arr.size(); i++) {
		arr[i].resize(static_cast<std::size_t>(scrollWidth), ' ');
	}

	if (orientation == Orientation::HORIZONTAL) {
		for (int i = 0; i < scrollHeight; i++) {
			for (int j = 2, k = 0; k < content[slideNumber][0].size(); j++, k++) {
				arr[i][j] = content[slideNumber][i][k];
			}
		}

		arr[scrollHeight / 2][0] = char(17);
		arr[scrollHeight / 2][scrollWidth - 1] = char(16);
	}
	else {
		for (int i = 1, k = 0; k < content[slideNumber].size(); i++, k++) {
			for (int j = 0; j < scrollWidth; j++) {
				arr[i][j] = content[slideNumber][k][j];
			}
		}

		arr[0][scrollWidth / 2] = char(30);
		arr[scrollHeight - 1][scrollWidth / 2] = char(31);
	}
}


int ScrollButton::getSlideNumber()
{
	return this->slideNumber;
}

void ScrollButton::buttonDefault()
{

}

void ScrollButton::buttonPressed()
{

}

void ScrollButton::show()
{
	if (scrollName != "")
	{
		setcur(scrollNamePositionX, scrollNamePositionY);
		std::cout << scrollName;
	}
	for (int i = 0; i < scrollHeight; i++)
	{
		for (int j = 0; j < scrollWidth; j++)
		{
			setcur(scrollPositionX + j, scrollPositionY + i);
			std::cout << arr[i][j];
		}
	}
}

void ScrollButton::changePosition(int positionX, int positionY)
{
	this->scrollPositionX = positionX;
	this->scrollPositionY = positionY;
}

void ScrollButton::nextSlide(int newSlideNumber)
{
	for (int i = 0; i < scrollHeight; i++)
	{
		for (int j = 0; j < scrollWidth; j++)
		{
			arr[i][j] = ' ';
		}
	}
	for (int i = 0; i < scrollHeight; i++)
	{
		for (int j = 0; j < scrollWidth; j++)
		{
			setcur(scrollPositionX + j, scrollPositionY + i);
			std::cout << ' ';
		}
	}
	this->slideNumber = newSlideNumber;
	buttonFill();
}

void ScrollButton::addName(std::string name, int namePositionX, int namePositionY)
{
	this->scrollName = name;
	this->scrollNamePositionX = namePositionX;
	this->scrollNamePositionY = namePositionY;
}

void ScrollButton::handleMouseEvent(COORD mousePos)
{
	if (mousePos.X >= scrollPositionX && mousePos.X < scrollPositionX + scrollWidth &&
		mousePos.Y >= scrollPositionY && mousePos.Y < scrollPositionY + scrollHeight) {
		buttonPressed();
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			if (orientation == Orientation::HORIZONTAL)
			{
				if (mousePos.X == scrollPositionX && mousePos.Y == scrollPositionY + scrollHeight / 2) {
					int temp = slideNumber;
					if (temp > 0)temp -= 1;
					else if (temp == 0)temp = content.size() - 1;
					nextSlide(temp);
					if (userFunction1 != nullptr)userFunction1();
				}
				else if (mousePos.X == scrollPositionX + scrollWidth - 1 && mousePos.Y == scrollPositionY + scrollHeight / 2) {
					int temp = slideNumber;
					if (temp < content.size() - 1)temp += 1;
					else if (temp == content.size() - 1)temp = 0;
					nextSlide(temp);
					if (userFunction2 != nullptr)userFunction2();
				}
			}
			else
			{
				if (mousePos.X == scrollPositionX + scrollWidth / 2 && mousePos.Y == scrollPositionY) {
					int temp = slideNumber;
					if (temp > 0)temp -= 1;
					else if (temp == 0)temp = content.size() - 1;
					nextSlide(temp);
					if (userFunction1 != nullptr)userFunction1();
				}
				else if (mousePos.X == scrollPositionX + scrollWidth / 2 && mousePos.Y == scrollPositionY + scrollHeight - 1) {
					int temp = slideNumber;
					if (temp < content.size() - 1)temp += 1;
					else if (temp == content.size() - 1)temp = 0;
					nextSlide(temp);
					if (userFunction2 != nullptr)userFunction2();
				}
			}
		}

	}
	else {
		buttonDefault();
	}
}

void ScrollButton::handleKeyboardEvent(int key)
{
	if (key == 75)
	{
		int temp = slideNumber;
		if (temp > 0)temp -= 1;
		else if (temp == 0)temp = content.size() - 1;
		nextSlide(temp);
		if (userFunction1 != nullptr)userFunction1();
	}
	else if (key == 77)
	{
		int temp = slideNumber;
		if (temp < content.size() - 1)temp += 1;
		else if (temp == content.size() - 1)temp = 0;
		nextSlide(temp);
		if (userFunction2 != nullptr)userFunction2();
	}
}

CustomButton::CustomButton(std::vector<std::vector<char>>& textureDefault, std::vector<std::vector<char>>& texturePressed, int buttonPositionX, int buttonPositionY) :
	textureDefault(textureDefault), texturePressed(texturePressed),
	buttonPositionX(buttonPositionX), buttonPositionY(buttonPositionY)
{
	saveConsoleAttributes();
}

void CustomButton::buttonFill()
{
}

void CustomButton::buttonDefault()
{
	isPressed = false;
}

void CustomButton::buttonPressed()
{
	isPressed = true;
}

void CustomButton::show()
{

	setColorBackground(buttonBackgroundColor);
	setColorForeground(buttonForegroundColor);
	if (isPressed)
	{
		for (int i = 0; i < texturePressed.size(); i++)
		{
			for (int j = 0; j < texturePressed[0].size(); j++)
			{
				setcur(buttonPositionX + j, buttonPositionY + i);
				std::cout << texturePressed[i][j];
			}
		}
	}
	else
	{
		for (int i = 0; i < textureDefault.size(); i++)
		{
			for (int j = 0; j < textureDefault[0].size(); j++)
			{
				setcur(buttonPositionX + j, buttonPositionY + i);
				std::cout << textureDefault[i][j];
			}
		}
	}
	restoreConsoleAttributes();
}

void CustomButton::changePosition(int positionX, int positionY)
{
	this->buttonPositionX = positionX;
	this->buttonPositionY = positionY;
}

void CustomButton::handleMouseEvent(COORD mousePos)
{
	if (mousePos.X >= buttonPositionX && mousePos.X < buttonPositionX + textureDefault[0].size() &&
		mousePos.Y >= buttonPositionY && mousePos.Y < buttonPositionY + textureDefault.size())
	{
		buttonPressed();
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if (userFunction != nullptr)userFunction();
		}
	}
	else
	{
		buttonDefault();
	}
}

void CustomButton::handleKeyboardEvent(int key)
{
	if (key == 13)
	{
		if (userFunction != nullptr)userFunction();
	}
}

void CustomButton::setButtonBackgroundColor(ConsoleColor backgroundColor)
{
	this->buttonBackgroundColor = backgroundColor;
}

void CustomButton::setButtonForegroundColor(ConsoleColor foregroundColor)
{
	this->buttonForegroundColor = foregroundColor;
}
