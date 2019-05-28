#include <stdio.h>
#include "Minesweeper.h"

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

int IsRetry(char user) {
	return (user == 'y' || user == 'Y');
}

int IsNotRetry(char user) {
	return (user == 'n' || user == 'N');
}

int IsGameReset(){
	static int flag = 0;
	char user;

	user = NULL;

	if(flag == 0) {
		flag = 1; 
		return 1;
	}

	while(!IsRetry(user) && !IsNotRetry(user)) {

		getchar();

		printf("\nRetry? (Y/N):");
		scanf_s("%c", &user);

		if(IsRetry(user)) {
			system("cls");
			return 1;
		}

		else if(IsNotRetry(user)) {
			return 0;
		}

	}
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