#include <stdlib.h> // для srand()
#include <string.h> // для memset()

#include "main.h"
#include "keys.h"
#include "movesub.h"
#include "tui.h"

RECT GetPlayerRect() {
	return (RECT){player.x, player.y,
	player.x+player.w-1, player.y+player.h-1};
}

int IsCrossBlocks(RECT r, const char blocks[]) {
	int k;
	for(int i = r.left; i <= r.right; i++)
		for(int j = r.top; j <= r.bottom; j++)
			if(k = 0, IsPointInWorld(j, i)) {
				while(blocks[k] != '\0')
					if(world[j][i] == blocks[k++])
						return 1;
			}
			else if(blocks == solidBlocks) {
				return 1;
			}
	return 0;
}

TBlockType TryMovePlayer(int dy, int dx) {
	TPlayer old = player;
	player.x += dx;
	player.y += dy;
	
	RECT rect = GetPlayerRect();
	if(IsCrossBlocks(rect, solidBlocks))
		return (player = old, B_SOLID);
	if(IsCrossBlocks(rect, liquidBlocks))
		return B_LIQUID;
	return B_GAS;
}

int GetOne(int a) {
	return (a > 0 ? 1 : (a < 0 ? -1 : 0));
}

void ApplyPlayerGravity() {
	player.ay++;
	TBlockType res;
	for(int i = 0; i < abs(player.ay); i++) {
		res = TryMovePlayer(GetOne(player.ay), 0);
		if(res == B_SOLID)
			player.ay = 0;
		if(res == B_LIQUID)
			player.ay -= GetOne(player.ay);
	}
}

void PlayerMove(TPlayer* plr, char w, char a, char s, char d) {
	ApplyPlayerGravity();
	char wasd[4] = {w, a, s, d};
	for(int i = 0; i < plr->speed; i++)
		for(int j = 0; j < 4; j++)
			if(GetKeyState(wasd[j])) {
				if(j == 0) {
					RECT foot = {player.x, player.y + player.h,
								player.x + player.w - 1, player.y + player.h};
					if(IsCrossBlocks(foot, solidBlocks))
						player.ay = -4;
					if(!IsCrossBlocks(GetPlayerRect(), liquidBlocks))
						continue;
				}
				
				TryMovePlayer(dirInc[j].y, dirInc[j].x);
				
				/* подниматься на 1 вверх + влево/вправо
				if(j == 1 || j == 2)
					TryMovePlayer(dirInc[j].y-1, dirInc[j].x);
				*/
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
