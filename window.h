#pragma once
#include <vector>
#include <iostream>
#include <Windows.h>
#include "object.h"
#include "cursor.h"

class Window : public Object
{
public:
    Window(size_t windowWidth, size_t windowHeight, size_t windowPositionX, size_t windowPositionY);
    Window(size_t windowWidth, size_t windowHeight, size_t windowPositionX, size_t windoePositionY, std::string windowName, size_t windowNamePositionX, size_t windowNamePositionY);
    void windowFill();
    void show() override;
    void addWindowName(std::string windowName, size_t windoeNamePositionX, size_t windowNamePositionY);
private:
    std::vector<std::vector<char>> arr;
    size_t windowWidth;
    size_t windowHeight;
    size_t windowPositionX;
    size_t windowPositionY;
    std::string windowName = "";
    size_t windowNamePositionX;
    size_t windowNamePositionY;
};
