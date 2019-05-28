#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Minesweeper.h"

int main() {
	while(IsGameReset()){
		boardRows = 0;
		boardCols = 0;
		setBoardSize();
		InitBoard();
		Play();
	}

}

void setBoardSize() {
	COORD pos;
	IntroShow();

	while (!checkRows() || !checkCols()) {

		setCurrentCursorPos(0, 7);
		printf("%d~%d Please enter rows, cols:", MINBOARD, MAXBOARD); 

		pos = getCurrentCursorPos();
		printf("        ");

		setCurrentCursorPos(pos.X, pos.Y);
		scanf_s(" %d %d", &boardRows, &boardCols);

	}

	system("cls");

}

void InitBoard(){
	int i, j;
	for(i = 0; i < MAXBOARD; i++) {
		for(j = 0; j < MAXBOARD; j++) {

			if(i >= boardRows || j >= boardCols) {
				my_Board[i][j].statusBlock = STATUS_OUTOFRANGE;
			}

			else {
				my_Board[i][j].statusBlock = STATUS_CLOSE;
				my_Board[i][j].cntNearMine = 0;
			}

			my_Board[i][j].statusMine = NORMAL;

		}
	}
}


