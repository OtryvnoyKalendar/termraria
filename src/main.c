#include <string.h> // для strlen(), memset()
#include <unistd.h> // для usleep()

// мои функции и процедуры
#include "main.h"
#include "core.h"
#include "tui.h"
#include "keys.h"
#include "mouse.h"
#include "movesub.h"

Tworld world;
POINT CamPos = {-3, -3}; // позиция верхнего левого угла области копирования

Tmap map;
int mapColors[MAP_HEIGHT][MAP_WIDTH+1];

int CursX = -1;
int CursY = -1;
unsigned MouseFlags = 0x0;

enum {S_SAND = 0, S_WATER, S_WALL, S_NOTHING, S_LAST};
int substance = S_SAND;
char SubChar[] = {SYMBOL_SAND, SYMBOL_WATER, SYMBOL_WALL, SYMBOL_NOTHING};
char* SubName[] = {"sand", "water", "wall", "space"};

void OpenConsoleMode() {
	setConsoleSize(MAP_WIDTH, MAP_HEIGHT);
	setConsoleTitle("Termraria");
	OpenKeysMode();
	OpenNcursesMode();
}

void CloseConsoleMode() {
	CloseNcursesMode();
	CloseKeysMode();
}

void BeforeCloseProgram() {
	CloseConsoleMode();
}

// основной цикл

void SelectSubstance() {
	for(int i=0; i < S_LAST; i++)
		if(GetKeyState(KEY_1+i))
			substance = i;
}

void InitWorld() {
	ClearMap();
	memset(world, SYMBOL_SOIL, sizeof(world));
	ClearMapColors();
}

void GameControl() {
	RefreshKeyboardStatus();
	
	if(GetKeyState(KEY_R))
		InitWorld();
	
	SelectSubstance();
	
	if(GetKeyState(KEY_ESC))
		CloseProgram();
	
	GetMouseState(&CursY, &CursX, &MouseFlags);
	int BreakCount = 0;
	int BreakCountMax = 5;
	
	while(MOUSE_LEFT_PRESSED) {
		GetMouseState(&CursY, &CursX, &MouseFlags);
		PutSubstance();
		
		BreakCount += 1;
		if(BreakCount >= BreakCountMax)
			break;
	}
}

void ShowTUI() {
	int CharBufSize = 40;
	char CharBuf[CharBufSize];
	snprintf(CharBuf, CharBufSize, "x = %3d, y = %3d, f = %09x", CursX, CursY, MouseFlags);
	PutText(CharBuf, 29, 3, COLOR_WHITE);
	
	snprintf(CharBuf, CharBufSize, "substance: %s", SubName[substance]);
	PutText(CharBuf, 29, 40, COLOR_WHITE);
}

void GameplayLogic() {
	MoveSubstance();
}

int main() {
	OpenConsoleMode();
	InitWorld();
	
	while(1) {
		CheckSignals();
		GameControl();
		napms(GAME_DELAY_CONSTANT);
		GameControl();
		
		GameplayLogic();
		WorldToMapFrom(CamPos.y, CamPos.x);
		ShowMap();
		ShowTUI();
	}
	
	CloseProgram();
	return 0;
}
