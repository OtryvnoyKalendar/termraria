#include "main.h"
#include "core.h"
#include <string.h> // для memset()
#include "math.h"
#include "movesub.h"

// отрисовка игры

int isMapCellExists(int y, int x) {
	return (x >= 0 && x < MAP_WIDTH && y >= 0 &&  y < MAP_HEIGHT);
}

void PutSymbolToConsole(int y, int x, char ch, int color) {
	if(!isMapCellExists(y, x))
		ErrorCloseProgram("выход за границы игрового поля");
	map[y][x] = ch;
	move(y, x);
	if(color != -1)
		attron(COLOR_PAIR(color));
	addch(ch);
}

void ShowPlayer() {
	int x = player.x - CamPos.x;
	int y = player.y - CamPos.y;
	
	for(int i = x; i < x + player.w; i++)
		for(int j = y; j < y + player.h; j++)
			map[j][i] = SYMBOL_PLAYER;
}

void ShowMap() {
	for(int i=0; i<MAP_HEIGHT; i++)
		for(int j=0; j<MAP_WIDTH; j++) {
			char symbol = map[i][j];
			int color = COLOR_STANDARD; //mapColors[i][j];
			
			switch(symbol) {
				case SYMBOL_SAND:
					color = COLOR_SAND; break;
				case SYMBOL_WATER:
					color = COLOR_WATER; break;
				case SYMBOL_WALL:
					color = COLOR_WALL; break;
				case SYMBOL_PLAYER:
					color = COLOR_PLAYER; break;
				case SYMBOL_SOIL:
					color = COLOR_SOIL; break;
				case SYMBOL_OUTSIDE:
					color = COLOR_OUTSIDE; break;
			}
			
			PutSymbolToConsole(i, j, symbol, color);
		}
	refresh();
}

void ClearMap() {
	memset(map, SYMBOL_NOTHING, sizeof(map));
}

void ClearMapColors() {
	memset(mapColors, COLOR_STANDARD, sizeof(map));
}

void DrawSymbolInConsole(int y, int x, char ch, int color) {
	if(!isMapCellExists(y, x))
		ErrorCloseProgram("выход за границы игрового поля");
	move(y, x);
	if(color != -1) attron(COLOR_PAIR(color));
	addch(ch);
}

void PutCircle(int y, int x, int rad, char symbol) {
	for(int i = x-rad; i < x+rad; i++)
		for(int j = y-rad; j < y+rad; j++)
			if(IsPointInWorld(j, i)
				&& ( pow(x-i, 2) + pow(y-j, 2) <= pow(rad, 2) ) ) {
					world[j][i] = symbol;
				}
}

void PutText(const char* message, int ystart, int xstart, int color) {
	for(int i=0; message[i]!='\0'; i++)
		if (isMapCellExists(ystart, xstart+i)) {
			DrawSymbolInConsole(ystart, xstart+i, message[i], color);
			//map[ystart][xstart+i] = message[i];
			//mapColors[ystart][xstart+i] = color;
		}
	refresh();
}
