#include "Minesweeper.h"

/**
 * 머리 주석
 */

int main(void) {
	while(IsGameReset()){
		boardRows = 0;
		boardCols = 0;
		SetBoardSize();
		InitBoard();
		Play();
	}

}

void SetBoardSize(void) {
	COORD pos;
	IntroShow();

	while (!CheckRows() || !CheckCols()) {

		SetCurrentCursorPos(0, 7);
		printf("%d~%d Please enter rows, cols:", MINBOARD, MAXBOARD); 

		pos = GetCurrentCursorPos();
		printf("        ");

		SetCurrentCursorPos(pos.X, pos.Y);
		scanf(" %d %d", &boardRows, &boardCols);

	}

	system("cls");

}

void InitBoard(void){
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
