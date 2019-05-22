
#include"Minesweeper.h"
#include <stdio.h>
#include <Windows.h>

int checkRows(int boardRows) {
	return (boardRows >= MINBOARD && boardRows <= MAXBOARD);
}
int checkCols(int boardCols) {
	return (boardCols >= MINBOARD && boardCols <= MAXBOARD);
}

int checkRowsinGame(int currentRow, int boardRows) {
	return (currentRow >= 0 && currentRow < boardRows);
}
int checkColsinGame(int currentCol, int boardCols) {
	return (currentCol >= 0 && currentCol < boardCols);
}

int IsRetry(char user){
	return (user=='y' || user == 'Y');
}
int IsNotRetry(char user){
	return (user=='n' || user=='N');
}

int IsGameReset(){
	char user;
	user=NULL;
	while(!IsRetry(user) && !IsNotRetry(user)){
		getchar();
		printf("Retry? (Y/N): ");
		scanf_s("%c",&user);
		if(IsRetry(user)){return 1;}
		else if(IsNotRetry(user)){return 0;}
	}
}

int ActionInRange(int action) {
	if (action == 1 || action == 2) {
		return 1;
	}
	else
		return 0;
}

void setCurrentCursorPos(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

COORD getCurrentCursorPos(void) {
	COORD curPoint;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curPoint.X = curInfo.dwCursorPosition.X;
	curPoint.Y = curInfo.dwCursorPosition.Y;

	return curPoint;
}

void removeCursor(void) {
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

//Console COORD -> Array COORD
COORD computeArr(int x, int y) {
	COORD computed;
	computed.X = x / 2 - OFFSET_X;
	computed.Y = y - OFFSET_Y;
	return computed;
}

//Array COORD -> Console COORD
COORD computeArrReverse(int x, int y) {
	COORD computed;
	computed.X = (x + OFFSET_X) * 2;
	computed.Y = y + OFFSET_Y;
	return computed;
}