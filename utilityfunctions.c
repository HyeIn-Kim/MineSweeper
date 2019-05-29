#include "Minesweeper.h"

int CheckRows(void) {
	return (boardRows >= MINBOARD && boardRows <= MAXBOARD);
}

int CheckCols(void) {
	return (boardCols >= MINBOARD && boardCols <= MAXBOARD);
}

int CheckRowsinGame(int currentRow) {
	return (currentRow >= 0 && currentRow < boardRows);
}

int CheckColsinGame(int currentCol) {
	return (currentCol >= 0 && currentCol < boardCols);
}

int IsGameReset(void){
	static int flag = 0;
	char user;
	COORD pos;
	
	user = ' ';

	if(flag == 0) {
		flag = 1; 
		return 1;
	}
	pos = GetCurrentCursorPos();

	while(user != 'y' && user != 'Y' && user != 'n' && user != 'N') {

		SetCurrentCursorPos(pos.X, pos.Y);
		
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

void SetCurrentCursorPos(int x, int y) {
	COORD pos = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

COORD GetCurrentCursorPos(void) {
	COORD curPoint;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curPoint.X = curInfo.dwCursorPosition.X;
	curPoint.Y = curInfo.dwCursorPosition.Y;

	return curPoint;
}
