#pragma once
#include <Windows.h>

//функция для управления кнопками с помощью мыши
template<typename... Args>
void mouseButtonInteraction(Args*... objects) {
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
				(objects->handleMouseEvent(mousePos), ...);

				// Очистка буфера событий
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			}
		}
	}

	// Отображение каждой кнопки
	(objects->show(), ...);
}