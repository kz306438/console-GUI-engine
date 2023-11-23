#include "window.h"

Window::Window(size_t windowWidth, size_t windowHeight, size_t windowPositionX, size_t windowPositionY) :
	windowWidth(windowWidth), windowHeight(windowHeight),
	windowPositionX(windowPositionX), windowPositionY(windowPositionY)
{
	windowFill();
}

Window::Window(size_t windowWidth, size_t windowHeight, size_t windowPositionX, size_t windoePositionY, std::string windowName, size_t windowNamePositionX, size_t windowNamePositionY) :
	windowWidth(windowWidth), windowHeight(windowHeight),
	windowPositionX(windowPositionX), windowPositionY(windowPositionY),
	windowName(windowName), windowNamePositionX(windowNamePositionX), windowNamePositionY(windowNamePositionY)
{
	windowFill();
}

void Window::windowFill()
{
	if (windowName.size() > windowWidth - 2)
	{
		windowName = "";
	}
	arr.resize(windowHeight);
	for (size_t i = 0; i < windowHeight; i++)
	{
		for (size_t j = 0; j < windowWidth; j++)
		{
			arr[i].push_back(' ');
		}
	}
	for (size_t i = 1; i < windowHeight - 1; i++)
	{
		for (size_t j = 1; j < windowWidth - 1; j++)
		{
			arr[i][j] = ' ';
		}
	}
	for (size_t i = 1; i < windowHeight - 1; i++)
	{
		arr[i][0] = char(219);
		arr[i][windowWidth - 1] = char(219);
	}
	for (size_t j = 0; j < windowWidth; j++)
	{
		arr[0][j] = char(220);
		arr[windowHeight - 1][j] = char(223);
	}
	for (size_t i = 0; i < windowName.size(); i++)
	{
		arr[windowNamePositionY][windowNamePositionX + i] = windowName[i];
	}
}

void Window::show()
{
	for (size_t i = 0; i < windowHeight; i++)
	{
		for (size_t j = 0; j < windowWidth; j++)
		{
			setcur(windowPositionX + j, windowPositionY + i);
			std::cout << arr[i][j];
		}
	}
}
void Window::addWindowName(std::string windowName, size_t windowNamePositionX, size_t windowNamePositionY)
{
	if (windowName.size() <= windowWidth - 2 && windowNamePositionX > 0 && windowNamePositionX < windowWidth && windowNamePositionY > 0 && windowNamePositionY < windowHeight)
	{
		this->windowName = windowName;
		this->windowNamePositionX = windowPositionX;
		this->windowNamePositionY = windowNamePositionY;
		for (size_t i = 0; i < windowName.size(); i++)
		{
			arr[windowNamePositionY][windowNamePositionX + i] = windowName[i];
		}
	}
}