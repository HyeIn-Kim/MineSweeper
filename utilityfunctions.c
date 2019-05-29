#include <stdio.h>
#include "Minesweeper.h"
#pragma warning (disable:4996)

int checkRows() {
	return (boardRows >= MINBOARD && boardRows <= MAXBOARD);
}

int checkCols() {
	return (boardCols >= MINBOARD && boardCols <= MAXBOARD);
}

int checkRowsinGame(int currentRow) {
	return (currentRow >= 0 && currentRow < boardRows);
}

int checkColsinGame(int currentCol) {
	return (currentCol >= 0 && currentCol < boardCols);
}

int IsGameReset(){
	static int flag = 0;
	char user;
	COORD pos;
	
	user = ' ';

	if(flag == 0) {
		flag = 1; 
		return 1;
	}
	pos = getCurrentCursorPos();

	while(user != 'y' && user != 'Y' && user != 'n' && user != 'N') {

		setCurrentCursorPos(pos.X, pos.Y);
		
		getchar();

		printf("\nRetry? (Y/N):");
		scanf("%c", &user);

		if(user == 'y' || user == 'Y') {
			system("cls");
			return 1;
		}

		if(user == 'n' || user == 'N') {
			return 0;
		}
	}

	/* error-loop ended before getting right input */
	return -1;
}

int ActionInRange(int action) {
	if (action == 1 || action == 2) {
		return 1;
	}

	else {
		return 0;
	}
		
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
