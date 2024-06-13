#pragma once

typedef struct {
	int x;
	int y;
} POINT;

// карта игры

#define MAP_HEIGHT	30
#define MAP_WIDTH	80

typedef char Tmap[MAP_HEIGHT][MAP_WIDTH+1];

extern char map[MAP_HEIGHT][MAP_WIDTH+1];
extern int mapColors[MAP_HEIGHT][MAP_WIDTH+1];

extern int substance;
extern char SubChar[];

extern int CursX;
extern int CursY;
extern unsigned MouseFlags;
//#define MOUSE_LEFT_PRESSED (MouseFlags & BUTTON1_PRESSED)
#define MOUSE_LEFT_PRESSED (MouseFlags & 0x10000000)

#define MOUSE_RIGHT_PRESSED (MouseFlags & BUTTON3_PRESSED)
							// || (MouseFlags & BUTTON1_CLICKED))
// 0x00000004
//  - любая нажата

#define GAME_DELAY_CONSTANT 40

#define SYMBOL_NOTHING 	' '
//#define SYMBOL_SAND 	(char)176
#define SYMBOL_SAND 	'*'
//#define SYMBOL_WATER 	(char)219
#define SYMBOL_WATER 	'%'
#define SYMBOL_WALL 	'#'
#define SYMBOL_PLAYER 	'@'

#define COLOR_SAND		COLOR_YELLOW
#define COLOR_WATER		COLOR_BLUE
#define COLOR_WALL 		COLOR_WHITE
#define COLOR_PLAYER 	COLOR_RED

#define COLOR_STANDARD COLOR_GREEN
#define COLOR_TEXT COLOR_WHITE