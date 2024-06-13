#include "main.h"
#include "movesub.h"
#include <string.h>

// для работы воды
Tmap mapTmp;
int waterLevel;
POINT foundPoint;

int IsPointInMap(int y, int x) {
	return !(x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT-1);
}

void FindWaterPath(int y, int x) {
	if(!IsPointInMap(y, x))
		return;
	
	if(y >= waterLevel && y > foundPoint.y) {
		if(mapTmp[y][x] == SYMBOL_NOTHING) {
			foundPoint.x = x;
			foundPoint.y = y;
		}
	}
	
	if(mapTmp[y][x] == SYMBOL_WATER) {
		mapTmp[y][x] = '#'; // исключаем из дальнейшей обработки
		FindWaterPath(y-1, x);
		FindWaterPath(y+1, x);
		FindWaterPath(y, x+1);
		FindWaterPath(y, x-1);
	}
}

void MoveWater(int y, int x) {
	if(!IsPointInMap(y+1, x))
		return;
	
	switch(map[y+1][x]) {
		case SYMBOL_NOTHING:
			map[y][x] = SYMBOL_NOTHING;
			map[y+1][x] = SYMBOL_WATER;
			break;
		case SYMBOL_WATER:
			waterLevel = y+1;
			foundPoint.y = -1;
			memcpy(mapTmp, map, sizeof(map));
			FindWaterPath(y+1, x);
			
			if(foundPoint.y >= 0) {
				map[foundPoint.y][foundPoint.x] = SYMBOL_WATER;
				map[y][x] = SYMBOL_NOTHING;
			}
			break;
	}
}

void MoveSand(int y, int x) {
	for(int i = 0; i <= 1; i += (i == 0 ? -1 : 2))
		if(IsPointInMap(y+1, x+i))
			if(map[y+1][x+i] == SYMBOL_NOTHING || map[y+1][x+i] == SYMBOL_WATER) {
				map[y][x] = map[y+1][x+i];
				map[y+1][x+i] = SYMBOL_SAND;
				break;
			}
}

void MoveSubstance() {
	for(int i=MAP_HEIGHT-1; i >= 0; i--)
		for(int j=0; j<MAP_WIDTH; j++) {
			if(map[i][j] == SYMBOL_SAND)
				MoveSand(i, j);
			if(map[i][j] == SYMBOL_WATER)
				MoveWater(i, j);
		}
}
