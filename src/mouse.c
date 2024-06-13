#include "main.h"
#include "tui.h"
#include "core.h"
#include "movesub.h"
#include <math.h>

int SubRad = 1;
int SubRadMin = 1;
int SubRadMax = 10;

void PutLine(POINT posA, POINT posB, char NewSymbol) {
	float dx = (posB.x - posA.x) / (float)MAP_WIDTH;
	float dy = (posB.y - posA.y) / (float)MAP_WIDTH;
	
	for(int i = 0; i<MAP_WIDTH; i++) {
		int newY = (int)(posA.y+dy*i);
		int newX = (int)(posA.x+dx*i);
		if(IsPointInWorld(newY, newX)) {
			if(SubRad > 1)
				PutCircle(newY, newX, SubRad, NewSymbol);
			else
				world[newY][newX] = NewSymbol;
		}
	}
}

void PutSubstance() {
	POINT PtNew = {CursX, CursY};
	static POINT PtOld;
	PtNew.x += CamPos.x;
	PtNew.y += CamPos.y;
	
	if(CursX != -1 && CursY != -1 && MOUSE_EVENTS_CHECK) {
		if(MOUSE_LEFT_PRESSED) {
			char NewSymbol = SubChar[substance];
			float PtDistance = sqrt( pow((PtOld.x - PtNew.x), 2) + pow((PtOld.y - PtNew.y), 2) );
			if(PtDistance <= 3.5f)
				PutLine(PtOld, PtNew, NewSymbol);
			else {
				if(IsPointInWorld(PtNew.y, PtNew.x)) {
					if(SubRad > 1)
						PutCircle(PtNew.y, PtNew.x, SubRad, NewSymbol);
					else
						world[PtNew.y][PtNew.x] = NewSymbol;
				}
			}
		}
		
		static int wheelDelayTime = 0;
		const int wheelDelayTimer = 20;
		
		if(MOUSE_WHEEL_SCROLL_UP) {
			if(SubRad < SubRadMax && wheelDelayTime >= wheelDelayTimer) {
				SubRad++;
				wheelDelayTime = 0;
				MouseFlags = 0x0;
			}
		}
		else if(MOUSE_WHEEL_SCROLL_DOWN) {
			if(SubRad > SubRadMin && wheelDelayTime >= wheelDelayTimer) {
				SubRad--;
				wheelDelayTime = 0;
				MouseFlags = 0x0;
			}
		}
		
		if(wheelDelayTime < wheelDelayTimer)
			wheelDelayTime++;
	}
	
	PtOld = PtNew;
}
