#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <functional> 
#include <conio.h>
#include "colors.h"
#include "cursor.h"
#include "Object.h"
namespace {
	// Объявляем переменные как статические, чтобы они были видны только внутри данного файла
	static HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
	static INPUT_RECORD InputRecord;
	static DWORD Events;
	static COORD coord;
	static DWORD prev_mode;
	static bool setupInput = false;
	void setupInputHandling() {
		setupInput = true;
		GetConsoleMode(hin, &prev_mode);
		SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
		SetConsoleMode(hin, ENABLE_MOUSE_INPUT);
	}
}

class Button : public Object{
protected:
	virtual void buttonFill() = 0;
	virtual void buttonDefault() = 0;
	virtual void buttonPressed() = 0;
	virtual void changePosition(int positionX, int positionY) = 0;
	virtual ~Button() {}
	template<typename... Args>
	friend void keyboardButtonInteraction(Args*... buttons);
	bool isPressed = false;
};

class SliderButton : public Button {
public:
	enum class Orientation {
		VERTICAL,
		HORIZONTAL
	};

	using Orientation = SliderButton::Orientation;

	SliderButton(int minValue, int maxValue, std::string sliderName, int sliderValue, int sliderPositionX, int sliderPositionY, Orientation orientation);

	template <typename Function1, typename Function2>
	void connect(Function1&& less, Function2&& more) {
		userFunction1 = std::forward<Function1>(less);
		userFunction2 = std::forward<Function2>(more);
	}

	template<typename... Args>
	friend void keyboardButtonInteraction(Args*... buttons);

	template<typename... Args>
	friend void mouseButtonInteraction(Args*... buttons);

	void changePosition(int positionX, int positionY) override;
private:
	std::vector<std::vector<char>> arr;
	int sliderWidth;
	int sliderHeight = 4;
	int minValue = 0;
	int maxValue;
	std::string sliderName;
	int sliderValue;
	int sliderPositionX;
	int sliderPositionY;
	int temp;
	Orientation orientation;
	std::function<void()> userFunction1;
	std::function<void()> userFunction2;
	void setValue(int value);
	void buttonFill() override;
	void buttonDefault() override;
	void buttonPressed() override;
	void show() override;
	void handleMouseEvent(COORD mousePos) override;
	void handleKeyboardEvent(int key) override;
};

class StandartButton : public Button {
public:
	StandartButton(int buttonWidth, int buttonHeight, std::string buttonName, int buttonPositionX, int buttonPositionY);

	template <typename Function>
	void connect(Function&& func) {
		userFunction = std::forward<Function>(func);
	}

	template<typename... Args>
	friend void keyboardButtonInteraction(Args*... buttons);

	template<typename... Args>
	friend void mouseButtonInteraction(Args*... buttons);

	void changePosition(int positionX, int positionY) override;

private:
	std::vector<std::vector<char>> arr;
	int buttonHeight;
	int buttonWidth;
	int buttonPositionX;
	int buttonPositionY;
	std::string buttonName;
	std::function<void()> userFunction;
	void buttonDefault() override;
	void buttonPressed() override;
	void show() override;
	void handleMouseEvent(COORD mousePos) override;
	void handleKeyboardEvent(int key) override;
	void buttonFill() override;
};

class SwitchButton : public Button {
public:
	SwitchButton(int switchWidth, int switchHeight, bool stateSwitch, int switchPositionX, int switchPositionY);

	template <typename Function1, typename Function2>
	void connect(Function1&& off, Function2&& on) {
		userFunction1 = std::forward<Function1>(off);
		userFunction2 = std::forward<Function2>(on);
	}

	void addName(std::string switchName, int switchNamePositionX, int switchPositionY);

	template<typename... Args>
	friend void keyboardButtonInteraction(Args*... buttons);

	template<typename... Args>
	friend void mouseButtonInteraction(Args*... buttons);

	void changePosition(int positionX, int positionY) override;

private:
	std::vector<std::vector<char>> arr;
	int switchWidth;
	int switchHeight;
	std::string switchName = "";
	int switchNamePositionX;
	int switchNamePositionY;
	bool stateSwitch;
	int switchPositionX;
	int switchPositionY;
	std::string state;
	std::function<void()> userFunction1;
	std::function<void()> userFunction2;
	void setValue(bool value);
	void buttonFill() override;
	void buttonDefault() override;
	void buttonPressed() override;
	void show() override;
	void handleMouseEvent(COORD mousePos) override;
	void handleKeyboardEvent(int key) override;
};

class ScrollButton : public Button
{
public:
	enum class Orientation {
		VERTICAL,
		HORIZONTAL
	};

	ScrollButton(std::vector<std::vector<std::vector<char>>>& content, int scrollPositionX, int scrollPositionY, Orientation orientation);

	using Orientation = ScrollButton::Orientation;

	template<typename... Args>
	friend void keyboardButtonInteraction(Args*... buttons);

	template<typename... Args>
	friend void mouseButtonInteraction(Args*... buttons);

	template <typename Function1, typename Function2>
	void connect(Function1&& prev, Function2&& next) {
		userFunction1 = std::forward<Function1>(prev);
		userFunction2 = std::forward<Function2>(next);
	}

	void nextSlide(int newSlideNumber);

	void addName(std::string name, int namePositionX, int namePositionY);

	void changePosition(int positionX, int positionY) override;

private:
	std::vector<std::vector<std::vector<char>>> content;
	std::vector<std::vector<char>> arr;
	int  scrollWidth;
	int  scrollHeight;
	std::string  scrollName = "";
	int scrollNamePositionX;
	int scrollNamePositionY;
	int  scrollPositionX;
	int  scrollPositionY;
	Orientation orientation;
	int slideNumber = 0;
	std::function<void()> userFunction1;
	std::function<void()> userFunction2;
	void buttonFill() override;
	void buttonDefault() override;
	void buttonPressed() override;
	void show() override;
	void handleMouseEvent(COORD mousePos) override;
	void handleKeyboardEvent(int key) override;
};

class CustomButton : public Button
{
public:
	CustomButton(std::vector<std::vector<char>>& textureDefault, std::vector<std::vector<char>>& texturePressed, int buttonPositionX, int buttonPositionY);

	template <typename Function>
	void connect(Function&& func) {
		userFunction = std::forward<Function>(func);
	}

	template<typename... Args>
	friend void keyboardButtonInteraction(Args*... buttons);

	template<typename... Args>
	friend void mouseButtonInteraction(Args*... buttons);

	void setButtonBackgroundColor(ConsoleColor backgroundColor);

	void setButtonForegroundColor(ConsoleColor foregroundColor);

	void changePosition(int positionX, int positionY) override;

private:
	std::vector<std::vector<char>> textureDefault;
	std::vector<std::vector<char>> texturePressed;
	int buttonPositionX;
	int buttonPositionY;
	std::function<void()> userFunction;
	void buttonFill() override;
	void buttonDefault() override;
	void buttonPressed() override;
	void show() override;
	virtual void handleMouseEvent(COORD mousePos);
	virtual void handleKeyboardEvent(int key);
	ConsoleColor buttonBackgroundColor = Black;
	ConsoleColor buttonForegroundColor = White;
};

//функция для управления кнопками с помощью клавиатуры
template<typename... Args>
void keyboardButtonInteraction(Args*... buttons)
{
	int activeButton{};//номер нажатой кнопки
	std::vector<Button*> allButtons = { buttons... }; //вектор кнопок

	//ищем нажатую кнопку
	for (int i = 0; i < allButtons.size(); i++)
	{
		if (allButtons[i]->isPressed == true)activeButton = i;
	}

	//для нажатой кнопки вызываем метод buttonPressed
	allButtons[activeButton]->buttonPressed();

	//считываем нажатия клавиш
	if (_kbhit()) {
		int key = _getch();

		switch (key) {
		case 72: // UP arrow key
			if (activeButton == 0) {
				allButtons[activeButton]->buttonDefault();
				activeButton = allButtons.size() - 1;
				allButtons[activeButton]->buttonPressed();
			}
			else {
				allButtons[activeButton]->buttonDefault();
				activeButton -= 1;
				allButtons[activeButton]->buttonPressed();
			}
			break;
		case 80: // DOWN arrow key
			if (activeButton == allButtons.size() - 1) {
				allButtons[activeButton]->buttonDefault();
				activeButton = 0;
				allButtons[activeButton]->buttonPressed();
			}
			else {
				allButtons[activeButton]->buttonDefault();
				activeButton += 1;
				allButtons[activeButton]->buttonPressed();
			}
			break;

		default:
			//вызываем функционал нажатой кнопки
			allButtons[activeButton]->handleKeyboardEvent(key);
			break;
		}
	}
	//выводим в консоль все кнопки
	(buttons->show(), ...);
}

//функция для управления кнопками с помощью мыши
template<typename... Args>
void mouseButtonInteraction(Args*... buttons) {
	INPUT_RECORD InputRecord;
	DWORD Events = 0;

	if (PeekConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &InputRecord, 1, &Events))//при условии что произошло событие ввода
	{
		if (Events > 0 && ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &InputRecord, 1, &Events))
		{
			if (InputRecord.EventType == MOUSE_EVENT)//при условии  что это событие мыши
			{
				MOUSE_EVENT_RECORD mouseEvent = InputRecord.Event.MouseEvent;
				COORD mousePos = mouseEvent.dwMousePosition;

				// Обработка события мыши для каждой кнопки
				(buttons->handleMouseEvent(mousePos), ...);

				// Очистка буфера событий
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			}
		}
	}

	// Отображение каждой кнопки
	(buttons->show(), ...);
}