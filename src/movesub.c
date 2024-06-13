#include "main.h"
#include "movesub.h"
#include <string.h>

// для работы воды
Tworld worldTmp;
int waterLevel;
POINT foundPoint;

int IsPointInMap(int y, int x) {
	return !(x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT-1);
}

int IsPointInWorld(int y, int x) {
	return !(x < 0 || y < 0 || x >= WORLD_WIDTH || y >= WORLD_HEIGHT);
}

void WorldToMapFrom(int y, int x) {
	memset(map, SYMBOL_OUTSIDE, sizeof(map));
	for(int i = 0; i < MAP_HEIGHT; i++)
		for(int j = 0; j < MAP_WIDTH; j++)
			if(IsPointInWorld(y+i, x+j))
				map[i][j] = world[y+i][x+j];
}

void FindWaterPath(int y, int x) {
	if(!IsPointInWorld(y, x))
		return;
	
	if(y >= waterLevel && y > foundPoint.y) {
		if(worldTmp[y][x] == SYMBOL_NOTHING) {
			foundPoint.x = x;
			foundPoint.y = y;
		}
	}
	
	if(worldTmp[y][x] == SYMBOL_WATER) {
		worldTmp[y][x] = '#'; // исключаем из дальнейшей обработки
		FindWaterPath(y-1, x);
		FindWaterPath(y+1, x);
		FindWaterPath(y, x+1);
		FindWaterPath(y, x-1);
	}
}

void MoveWater(int y, int x) {
	if(!IsPointInWorld(y+1, x))
		return;
	
	switch(world[y+1][x]) {
		case SYMBOL_NOTHING:
			world[y][x] = SYMBOL_NOTHING;
			world[y+1][x] = SYMBOL_WATER;
			break;
		case SYMBOL_WATER:
			if(IsPointInWorld(y-1, x) && world[y-1][x] == SYMBOL_WATER)
				return;
			
			waterLevel = y+1;
			foundPoint.y = -1;
			memcpy(worldTmp, world, sizeof(world));
			FindWaterPath(y+1, x);
			
			if(foundPoint.y >= 0) {
				world[foundPoint.y][foundPoint.x] = SYMBOL_WATER;
				world[y][x] = SYMBOL_NOTHING;
			}
			break;
	}
}

void MoveSand(int y, int x) {
	for(int i = 0; i <= 1; i += (i == 0 ? -1 : 2))
		if(IsPointInWorld(y+1, x+i))
			if(world[y+1][x+i] == SYMBOL_NOTHING || world[y+1][x+i] == SYMBOL_WATER) {
				world[y][x] = world[y+1][x+i];
				world[y+1][x+i] = SYMBOL_SAND;
				break;
			}
}

void MoveSubstance() {
	for(int i=WORLD_HEIGHT-1; i >= 0; i--)
		for(int j=0; j<WORLD_WIDTH; j++) {
			if(world[i][j] == SYMBOL_SAND)
				MoveSand(i, j);
			if(world[i][j] == SYMBOL_WATER)
				MoveWater(i, j);
		}
}
