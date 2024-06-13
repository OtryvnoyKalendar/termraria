#include "main.h"
#include "keys.h"
#include <stdlib.h> // для srand()
#include "tui.h"
#include <string.h> // для memset()

void PlayerMove(TPlayer* plr, char w, char a, char s, char d) {
	char wasd[4] = {w, a, s, d};
	for(int i = 0; i < plr->speed; i++)
		for(int j = 0; j < 4; j++)
			if(GetKeyState(wasd[j])) {
				plr->x += dirInc[j].x;
				plr->y += dirInc[j].y;
			}
}

void FocusToPlayer() {
	static const int dx = MAP_WIDTH / 2;
	static const int dy = MAP_HEIGHT / 2;
	
	CamPos.x = player.x - dx;
	CamPos.y = player.y - dy;
}

void GenerateWorld(int seed) {
	srand(seed);
	// заполняем мир землёй
	memset(world, SYMBOL_SOIL, sizeof(world));
	
	// пустота сверху
	for(int i = 0; i < 100; i++)
		memset(world[i], SYMBOL_NOTHING, sizeof(world[i]));
	
	// холмы
	for(int i = 0; i < WORLD_WIDTH; i++)
		PutCircle(110 + rand()%20, rand() % WORLD_WIDTH, rand()%20, SYMBOL_SOIL);
	
	// система пещер
	for(int i = 0; i < WORLD_WIDTH; i++) {
		int x = rand() % WORLD_WIDTH;
		int y = 110 + rand() % (WORLD_HEIGHT-100);
		int rad = 2 + rand() % 10;
		PutCircle(y, x, rad, SYMBOL_NOTHING);
		if(rand() % 10 == 0)
			PutCircle(y, x, rad, SYMBOL_WATER);
		else if(rand() % 10 == 0)
			PutCircle(y, x, rad, SYMBOL_SAND);
	}
}
