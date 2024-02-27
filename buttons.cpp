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

void Button::setBackgroundColor(const ConsoleColor& newColor)
{
}

void Button::setForegroundColor(const ConsoleColor& newColor)
{
}

void Button::allowChanges()
{
	this->isChanged = true;
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
SliderButton::SliderButton(int minValue, int maxValue, std::string sliderName, int sliderValue, int multiplier, int sliderPositionX, int sliderPositionY, Orientation orientation) :
	minValue(minValue), maxValue(maxValue),
	sliderName(sliderName), sliderValue(sliderValue), multiplier(multiplier),
	sliderPositionX(sliderPositionX), sliderPositionY(sliderPositionY),
	orientation(orientation)
{
	temp = sliderValue;
	buttonFill();
}
void SliderButton::buttonFill() {
	if (orientation == Orientation::HORIZONTAL) {
		sliderWidth = static_cast<int>((maxValue - minValue) + 3); //считаем ширину слайдра
		sliderValue -= minValue;
		arr.resize(sliderHeight);
		for (int i = 0; i < sliderHeight; i++) {
			for (int j = 0; j < sliderWidth; j++) {   //создаём вектор для хранения слайдера
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
		for (int i = 0, j = (sliderWidth - static_cast<int>(sliderName.size())) / 2; i < static_cast<int>(sliderName.size()); i++, j++) { //отображение имени слайдера
			arr[0][j] = sliderName[i];
		}
		std::string s = std::to_string((sliderValue + minValue)*multiplier);
		for (int i = 0, j = (sliderWidth - static_cast<int>(s.size())) / 2; i < static_cast<int>(s.size()); i++, j++) {  //отображения состояния слайдера
			arr[sliderHeight - 1][j] = s[i];
		}
		arr[sliderHeight - 2][sliderValue + 1] = 219;  //ползунок слайдера
	}
	else if (orientation == Orientation::VERTICAL)
	{
		double V = sliderValue;
		((maxValue - minValue + 1) % 2 == 0) ? sliderHeight = ((maxValue - minValue + 1) / 2) + 4 : sliderHeight = ((maxValue - minValue + 1) / 2) + 5; //высота
		sliderWidth = (sliderName.size() >= 3) ? sliderName.size() + 2 : 5;  //ширина
		V = sliderValue - minValue;
		V = V / 2 - 1;
		arr.resize(sliderHeight);
		for (int i = 0; i < sliderHeight; i++)
		{
			for (int j = 0; j < sliderWidth; j++)    //создаём ветор для слайдера
			{
				arr[i].push_back(' ');
			}
		}

		arr[1][static_cast<std::vector<char, std::allocator<char>>::size_type>(sliderWidth / 2) + 1] = char(30);
		arr[sliderHeight - 2][static_cast<std::vector<char, std::allocator<char>>::size_type>(sliderWidth / 2) + 1] = char(31);

		for (int i = 2; i < sliderHeight - 2; i++) arr[i][sliderWidth / 2 + 1] = char(124);

		for (int i = 0; i < sliderName.size(); i++) arr[0][i + 2] = sliderName[i];

		std::string s = std::to_string(sliderValue*multiplier);
		for (int i = 0, j = (sliderWidth - s.size()) / 2 + 2; i < s.size(); i++, j++)   //состояние слайдера
		{
			arr[sliderHeight - 1][j] = s[i];
		}

		if (V - int(V) == 0)
		{
			arr[sliderHeight - 4 - V][sliderWidth / 2 + 2] = char(220);
			arr[sliderHeight - 4 - V][sliderWidth / 2 + 1] = char(220);
			arr[sliderHeight - 4 - V][sliderWidth / 2] = char(220);
		}
		else                                                                    //создание и установка на нужную позицию ползунка
		{
			arr[sliderHeight - 3 - V][sliderWidth / 2 + 2] = char(223);
			arr[sliderHeight - 3 - V][sliderWidth / 2 + 1] = char(223);
			arr[sliderHeight - 3 - V][sliderWidth / 2] = char(223);
		}
	}
	isChanged = true;
}

void SliderButton::buttonDefault() {
	if (isPressed == true)isChanged = true;
	isPressed = false;
	if (orientation == Orientation::HORIZONTAL) {
		arr[0][0] = ' ';
	}
	else {
		setcur(sliderPositionX - 1, sliderPositionY - 1); // устранение артефактов
		std::cout << ' ';
		arr[0][0] = ' ';
	}
}

void SliderButton::buttonPressed() {
	if (isPressed == false)isChanged = true;
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

		std::string s = std::to_string((sliderValue + minValue)*multiplier);

		for (int i = 0, j = (sliderWidth - static_cast<int>(s.size())) / 2; i < static_cast<int>(s.size()); i++, j++) { //закрашиваем предыдущее состояние слайдера
			arr[sliderHeight - 1][j] = ' ';
		}
		if (value >= 0 && value <= maxValue - minValue) sliderValue = value;

		s = std::to_string((sliderValue + minValue)*multiplier);

		for (int i = 0, j = (sliderWidth - static_cast<int>(s.size())) / 2; i < static_cast<int>(s.size()); i++, j++) {  //устанавливаем новое значение слайдера
			arr[sliderHeight - 1][j] = s[i];
		}

		arr[sliderHeight - 2][sliderValue + 1] = 219;
	}
	else if (orientation == Orientation::VERTICAL) {
		double V;
		V = sliderValue - minValue;
		V = V / 2 - 1;

		if (V - int(V) == 0)                        //закрашиваем предыдущее состояние слайдера
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

		std::string s = std::to_string(sliderValue*multiplier);
		for (int i = 0; i < sliderWidth; i++)
		{
			arr[sliderHeight - 1][i] = ' ';
		}

		if (value >= minValue && value <= maxValue)sliderValue = value; //устанавливаем новое значение слайдера
		V = sliderValue - minValue;
		V = V / 2 - 1;

		s = std::to_string(sliderValue * multiplier);
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
	isChanged = true;
}

void SliderButton::show() {
	if(isChanged)
	{
		for (int i = 0; i < sliderHeight; i++) {
			for (int j = 0; j < sliderWidth; j++) {
				setcur(sliderPositionX + j, sliderPositionY + i);  //отображаем слайдер
				std::cout << arr[i][j];
			}
		}
		isChanged = false;
	}
}

void SliderButton::changePosition(int positionX, int positionY)
{
	this->sliderPositionX = positionX;
	this->sliderPositionY = positionY;
	isChanged = true;
}

void SliderButton::setBackgroundColor(const ConsoleColor& newColor)
{
	this->backgroundColor = newColor;
	isChanged = true;
}

void SliderButton::setForegroundColor(const ConsoleColor& newColor)
{
	this->foregroundColor = newColor;
	isChanged = true;
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
						if(userFunction1 != nullptr)userFunction1();
					}
				}
				else if (mousePos.X == sliderPositionX + sliderWidth / 2 + 1 && mousePos.Y == sliderPositionY + 1) {
					if (temp < maxValue) {
						temp++;
						setValue(temp);
						if (userFunction2 != nullptr)userFunction2();
					}
				}
				/*else if (mousePos.Y >= sliderPositionY + 2 && mousePos.Y < sliderPositionY + sliderHeight - 2 && mousePos.X >= sliderPositionX  && mousePos.X <= sliderPositionX + sliderWidth) {
					int delta = sliderValue + sliderPositionY + 2 - mousePos.Y;
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
				}*/
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
	isChanged = true;
}

void StandartButton::buttonDefault()
{
	if(isPressed == true)isChanged = true;
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
	if(isPressed != true)isChanged = true;
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

void StandartButton::setName(const std::string& newName)
{
	this->buttonName = newName;
	buttonFill();
}

void StandartButton::show()
{
	if(isChanged)
	{
		saveConsoleAttributes();
		setColorForeground(foregroundColor);
		setColorBackground(backgroundColor);

		for (int i = 0; i < buttonHeight; i++)
		{
			for (int j = 0; j < buttonWidth; j++)
			{
				setcur(buttonPositionX + j, buttonPositionY + i);
				std::cout << arr[i][j];
			}
		}
		restoreConsoleAttributes();
		isChanged = false;
	}

}

void StandartButton::changePosition(int positionX, int positionY)
{
	this->buttonPositionX = positionX;
	this->buttonPositionY = positionY;
	isChanged = true;
}

void StandartButton::setBackgroundColor(const ConsoleColor& newColor)
{
	this->backgroundColor = newColor;
	isChanged = true;
}

void StandartButton::setForegroundColor(const ConsoleColor& newColor)
{
	this->foregroundColor = newColor;
	isChanged = true;
}

void StandartButton::setTexture(char topLeft, char topRight, char bottomLeft, char bottomRight, char horizontal, char vertical) {
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
		arr[i][0] = verticalLine;
		arr[i][switchWidth - 1] = verticalLine;
	}

	for (int j = 0; j < switchWidth; j++)
	{
		arr[0][j] = horizontalLine;
		arr[switchHeight - 1][j] = horizontalLine;
	}

	arr[0][0] = topLeftCorner;
	arr[switchHeight - 1][0] = bottomLeftCorner;
	arr[0][switchWidth - 1] = topRightCorner;
	arr[switchHeight - 1][switchWidth - 1] = bottomRightCorner;

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
	isChanged = true;
}

void SwitchButton::buttonDefault()
{
	if(isPressed == true)isChanged = true;
	isPressed = false;

	for (std::size_t i = 0; i < arr.size(); i++)
	{
		arr[i][0] = verticalLine;
		arr[i][switchWidth - 1] = verticalLine;
	}

	for (int j = 0; j < switchWidth; j++)
	{
		arr[0][j] = horizontalLine;
		arr[switchHeight - 1][j] = horizontalLine;
	}

	arr[0][0] = topLeftCorner;
	arr[switchHeight - 1][0] = bottomLeftCorner;
	arr[0][switchWidth - 1] = topRightCorner;
	arr[switchHeight - 1][switchWidth - 1] = bottomRightCorner;
}

void SwitchButton::buttonPressed()
{
	if(isPressed != true)isChanged = true;
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
	if(isChanged)
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
		isChanged = false;
	}
}

void SwitchButton::changePosition(int positionX, int positionY)
{
	this->switchPositionX = positionX;
	this->switchPositionY = positionY;
	isChanged = true;
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
	isChanged = true;
}

void SwitchButton::addName(std::string name, int namePositionX, int namePositionY)
{
	this->switchName = name;
	this->switchNamePositionX = namePositionX;
	this->switchNamePositionY = namePositionY;
	isChanged = true;
}

void SwitchButton::setBackgroundColor(const ConsoleColor& newColor)
{
	this->backgroundColor = newColor;
	isChanged = true;
}

void SwitchButton::setForegroundColor(const ConsoleColor& newColor)
{
	this->foregroundColor = newColor;
	isChanged = true;
}

void SwitchButton::setTexture(char topLeft, char topRight, char bottomLeft, char bottomRight, char horizontal, char vertical) {
	topLeftCorner = topLeft;
	topRightCorner = topRight;
	bottomLeftCorner = bottomLeft;
	bottomRightCorner = bottomRight;
	horizontalLine = horizontal;
	verticalLine = vertical;
	buttonFill();
	show();
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
	isChanged = true;
}


int ScrollButton::getSlideNumber()
{
	return this->slideNumber;
}

void ScrollButton::buttonDefault()
{
	if (isPressed == true)isChanged = true;
	isPressed = false;
}

void ScrollButton::buttonPressed()
{
	if (isPressed != true)isChanged = true;
	isPressed = true;
}

void ScrollButton::show()
{
	if(isChanged)
	{
		if (scrollName != "")
		{
			setcur(scrollNamePositionX, scrollNamePositionY);
			std::cout << scrollName;
		}
		saveConsoleAttributes();
		setColorBackground(backgroundColor);
		setColorForeground(foregroundColor);
		for (int i = 0; i < scrollHeight; i++)
		{
			for (int j = 0; j < scrollWidth; j++)
			{
				if ((i == scrollHeight / 2 && j == 0) || (i == scrollHeight / 2 && j == scrollWidth - 1))
				{
					restoreConsoleAttributes();
					setcur(scrollPositionX + j, scrollPositionY + i);
					std::cout << arr[i][j];
					saveConsoleAttributes();
					setColorBackground(backgroundColor);
					setColorForeground(foregroundColor);
				}
				else
				{
					setcur(scrollPositionX + j, scrollPositionY + i);
					std::cout << arr[i][j];
				}
			}
		}
		restoreConsoleAttributes();
		isChanged = false;
	}
}

void ScrollButton::changePosition(int positionX, int positionY)
{
	this->scrollPositionX = positionX;
	this->scrollPositionY = positionY;
	isChanged = true;
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
	isChanged = true;
}

void ScrollButton::setBackgroundColor(const ConsoleColor& newColor)
{
	this->backgroundColor = newColor;
	isChanged = true;
}

void ScrollButton::setForegroundColor(const ConsoleColor& newColor)
{
	this->foregroundColor = newColor;
	isChanged = true;
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
				else if (mousePos.X == scrollPositionX + scrollWidth/ 2 && mousePos.Y == scrollPositionY + scrollHeight - 1) {
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
	buttonFill();
}

void CustomButton::buttonFill()
{
	isChanged = true;
}

void CustomButton::buttonDefault()
{
	if (isPressed == true)isChanged = true;
	isPressed = false;
}

void CustomButton::buttonPressed()
{
	if (isPressed != true)isChanged = true;
	isPressed = true;
}

void CustomButton::show()
{
	if(isChanged)
	{
		setColorBackground(backgroundColor);
		setColorForeground(foregroundColor);
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
		isChanged = false;
	}
}

void CustomButton::changePosition(int positionX, int positionY)
{
	this->buttonPositionX = positionX;
	this->buttonPositionY = positionY;
	isChanged = true;
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

void CustomButton::setBackgroundColor(const ConsoleColor& newColor)
{
	this->backgroundColor = newColor;
	isChanged = true;
}

void CustomButton::setForegroundColor(const ConsoleColor& newColor)
{
	this->foregroundColor = newColor;
	isChanged = true;
}

RadioButton::RadioButton(std::string buttonName, int radioPositionX, int radioPositionY) : 
	buttonName(buttonName), radioPositionX(radioPositionX), radioPositionY(radioPositionY)
{
	buttonFill();
}

void RadioButton::buttonFill()
{
	isChanged = true;
	arr.resize(4 + buttonName.size(), ' ');
	arr[0] = '(';
	arr[2] = ')';
	for (int i = 0; i < buttonName.size(); i++)
	{
		arr[i + 4] = buttonName[i];
	}
}

void RadioButton::buttonDefault()
{
	if (isPressed == true)isChanged = true;
	isPressed = false;
	bracketColor = foregroundColor;
}

void RadioButton::buttonPressed()
{
	if (isPressed != true)isChanged = true;
	isPressed = true;
	bracketColor = BrightCyan;
}

void RadioButton::show()
{
	if (isChanged)
	{
		saveConsoleAttributes();
		setColorForeground(foregroundColor);
		setColorBackground(backgroundColor);

		for (int i = 0; i < arr.size(); i++)
		{
			setcur(radioPositionX + i, radioPositionY);
			if (i == 0 || i == 2)
			{
				setColorForeground(bracketColor);
			    std::cout << arr[i];
				setColorForeground(foregroundColor);
			}
			else
			{
				std::cout << arr[i];
			}
		}
		restoreConsoleAttributes();
		isChanged = false;
	}
}

void RadioButton::handleMouseEvent(COORD mousePos)
{
	if (mousePos.X >= radioPositionX && mousePos.X <= radioPositionX + 2 &&
		mousePos.Y == radioPositionY)
	{
		buttonPressed();
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			state ^= true;
			if (state)
			{
				arr[1] = char(250);
				if(userFunction != nullptr)userFunction();
			}
			else
			{
				arr[1] = ' ';
			}
			isChanged = true;
		}
	}
	else
	{
		buttonDefault();
	}
}



void RadioButton::handleKeyboardEvent(int key)
{
	if(key == 13)
	{
		state ^= true;
		if (state)
		{
			arr[1] = char(250);
			if (userFunction != nullptr)userFunction();
		}
		else
		{
			arr[1] = ' ';
		}
		isChanged = true;
	}
}

void RadioButton::changePosition(int positionX, int positionY)
{
	radioPositionX = positionX;
	radioPositionY = positionY;
}

void RadioButton::setBackgroundColor(const ConsoleColor& newColor)
{
	backgroundColor = newColor;
	isChanged = true;
}

void RadioButton::setForegroundColor(const ConsoleColor& newColor)
{
	foregroundColor = newColor;
	bracketColor = foregroundColor;
	isChanged = true;
}

void RadioButton::setState(const bool& newState)
{ 	state = newState;
}

bool RadioButton::getState() const
{
	return state;
}
  

RadioButtonManager::RadioButtonManager(std::vector<RadioButton>& objects, int numberActiveButton) : 
	objects(objects), numberActiveButton(numberActiveButton)
{
	objects[numberActiveButton].arr[1] = char(250);
	objects[numberActiveButton].state = true;
	objects[numberActiveButton].isChanged = true;
}

void RadioButtonManager::handleMouseEvent(COORD mousePos)
{
	for (auto& el : objects)
	{
		el.handleMouseEvent(mousePos);
		for (int i = 0; i < objects.size(); ++i)
		{
			if (objects[i].state == true && i != numberActiveButton)
			{
				int prev = numberActiveButton;

				objects[prev].arr[1] = ' ';
				objects[prev].state = false;
				objects[prev].isChanged = true;

				numberActiveButton = i;

				objects[numberActiveButton].arr[1] = char(250);
				objects[numberActiveButton].state = true;
				objects[numberActiveButton].isChanged = true;
			}
			if (objects[i].state == false && i == numberActiveButton)
			{
				objects[numberActiveButton].arr[1] = char(250);
				objects[numberActiveButton].state = true;
				objects[numberActiveButton].isChanged = true;
			}
		}
	}
}

void RadioButtonManager::handleKeyboardEvent(int key)
{
	for (auto& el : objects)
	{
		el.handleKeyboardEvent(key);
		for (int i = 0; i < objects.size(); ++i)
		{
			if (objects[i].state == true && i != numberActiveButton)
			{
				int prev = numberActiveButton;

				objects[prev].arr[1] = ' ';
				objects[prev].state = false;
				objects[prev].isChanged = true;

				numberActiveButton = i;

				objects[numberActiveButton].arr[1] = char(250);
				objects[numberActiveButton].state = true;
				objects[numberActiveButton].isChanged = true;
			}
			if (objects[i].state == false && i == numberActiveButton)
			{
				objects[numberActiveButton].arr[1] = char(250);
				objects[numberActiveButton].state = true;
				objects[numberActiveButton].isChanged = true;
			}
		}
	}
}

void RadioButtonManager::show()
{
	for (auto& el : objects)
	{
		el.show();
	}
}

void RadioButtonManager::add(RadioButton& newButton)
{
	objects.push_back(newButton);
}

CheckBox::CheckBox(std::string buttonName, int radioPositionX, int radioPositionY) :
	buttonName(buttonName), radioPositionX(radioPositionX), radioPositionY(radioPositionY)
{
	buttonFill();
}

void CheckBox::buttonFill()
{
	isChanged = true;
	arr.resize(4 + buttonName.size(), ' ');
	arr[0] = '[';
	arr[2] = ']';
	for (int i = 0; i < buttonName.size(); i++)
	{
		arr[i + 4] = buttonName[i];
	}
}

void CheckBox::buttonDefault()
{
	if (isPressed == true)isChanged = true;
	isPressed = false;
	bracketColor = foregroundColor;
}

void CheckBox::buttonPressed()
{
	if (isPressed != true)isChanged = true;
	isPressed = true;
	bracketColor = BrightCyan;
}

void CheckBox::show()
{
	if (isChanged)
	{
		saveConsoleAttributes();
		setColorForeground(foregroundColor);
		setColorBackground(backgroundColor);

		for (int i = 0; i < arr.size(); i++)
		{
			setcur(radioPositionX + i, radioPositionY);
			if (i == 0 || i == 2)
			{
				setColorForeground(bracketColor);
				std::cout << arr[i];
				setColorForeground(foregroundColor);
			}
			else
			{
				std::cout << arr[i];
			}
		}
		restoreConsoleAttributes();
		isChanged = false;
	}
}

void CheckBox::handleMouseEvent(COORD mousePos)
{
	if (mousePos.X >= radioPositionX && mousePos.X <= radioPositionX + 2 &&
		mousePos.Y == radioPositionY)
	{
		buttonPressed();
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			state ^= true;
			if (state)
			{
				arr[1] = char(251);
				if (userFunction != nullptr)userFunction();
			}
			else
			{
				arr[1] = ' ';
			}
			isChanged = true;
		}
	}
	else
	{
		buttonDefault();
	}
}



void CheckBox::handleKeyboardEvent(int key)
{
	if (key == 13)
	{
		state ^= true;
		if (state)
		{
			arr[1] = char(251);
			if (userFunction != nullptr)userFunction();
		}
		else
		{
			arr[1] = ' ';
		}
		isChanged = true;
	}
}

void CheckBox::changePosition(int positionX, int positionY)
{
	radioPositionX = positionX;
	radioPositionY = positionY;
}

void CheckBox::setBackgroundColor(const ConsoleColor& newColor)
{
	backgroundColor = newColor;
	isChanged = true;
}

void CheckBox::setForegroundColor(const ConsoleColor& newColor)
{
	foregroundColor = newColor;
	bracketColor = foregroundColor;
	isChanged = true;
}

void CheckBox::setState(const bool& newState)
{
	state = newState;
}

bool CheckBox::getState() const
{
	return state;
}
