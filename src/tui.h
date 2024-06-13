#pragma once

int isMapCellExists(int y, int x);
void PutSymbolToConsole(int y, int x, char ch, int color);
void ShowMap();
void PutText(const char* message, int ystart, int xstart, int color);
void ClearMap();
void ClearMapColors();
void ShowPlayer();
void PutCircle(int y, int x, int rad, char symbol);
