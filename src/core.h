#pragma once

#include <stdlib.h> // для exit()
#include <ncurses.h> // работа с консолью
#include <signal.h> // для signal()

// закрытие программы

void BeforeCloseProgram();

void ErrorCloseProgram(const char* message);
void CloseProgram();

// цвета

#define COLOR_BLACK		0
#define COLOR_RED		1
#define COLOR_GREEN		2
#define COLOR_YELLOW	3
#define COLOR_BLUE		4
#define COLOR_MAGENTA	5
#define COLOR_CYAN		6
#define COLOR_WHITE		7

void CheckSignals();
void setBackgroundColor(int BackgroundColor);

// режим ncurses

void OpenNcursesMode();
void CloseNcursesMode();
void GetMouseState(int* y, int* x, unsigned* flags);

#define MOUSE_EVENTS (\
	BUTTON1_CLICKED | BUTTON1_PRESSED | BUTTON1_RELEASED | BUTTON1_DOUBLE_CLICKED |\
	BUTTON3_CLICKED | BUTTON3_PRESSED | BUTTON3_RELEASED | BUTTON3_DOUBLE_CLICKED\
					)
//ALL_MOUSE_EVENTS // BUTTON1 - лкм, BUTTON3 - пкм

// изменения настроек консоли

void setConsoleSize(int consoleWidth, int consoleHeight);
void setConsoleTitle(const char* consoleTitle);
