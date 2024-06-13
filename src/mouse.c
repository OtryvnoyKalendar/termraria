#include "main.h"
#include "tui.h"
#include "core.h"
#include "movesub.h"
#include <math.h>

void PutLine(POINT posA, POINT posB, char NewSymbol) {
	float dx = (posB.x - posA.x) / (float)MAP_WIDTH;
	float dy = (posB.y - posA.y) / (float)MAP_WIDTH;
	
	for(int i = 0; i<MAP_WIDTH; i++) {
		int newY = (int)(posA.y+dy*i);
		int newX = (int)(posA.x+dx*i);
		if(IsPointInWorld(newY, newX))
			world[newY][newX] = NewSymbol;
			//PutSymbolToConsole(newY, newX, NewSymbol, -1);
	}
}

void PutSubstance() {
	POINT PtNew = {CursX, CursY};
	static POINT PtOld;
	PtNew.x += CamPos.x;
	PtNew.y += CamPos.y;
	
	if(CursX != -1 && CursY != -1 && MOUSE_LEFT_PRESSED) {
		char NewSymbol = SubChar[substance];
		float PtDistance = sqrt( pow((PtOld.x - PtNew.x), 2) + pow((PtOld.y - PtNew.y), 2) );
		if(PtDistance <= 3.5f)
			PutLine(PtOld, PtNew, NewSymbol);
		else {
			if(IsPointInWorld(PtNew.y, PtNew.x))
				world[PtNew.y][PtNew.x] = NewSymbol;
				//PutSymbolToConsole(PtNew.y, PtNew.x, NewSymbol, -1);
		}
	}
	
	PtOld = PtNew;
}
