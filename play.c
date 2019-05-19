#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Minesweeper.h"

void MineAllocate(Board my_Board[][MAXBOARD], int boardRows, int boardCols) {
	const double mineRate = 0.15;
	int mineNum = (boardRows * boardCols) * mineRate;
	int row;
	int col;
	srand(time(NULL));
	while (mineNum > 0) {
		row = rand() % boardRows;
		col = rand() % boardCols;
		if (my_Board[row][col].statusMine == NORMAL) {
			my_Board[row][col].statusMine = MINE;
			mineNum--;
		}
	}
}


void DrawBoard(Board my_Board[][MAXBOARD],int boardRows, int boardCols){
	int i,j;
	for(i=0;i<MAXBOARD;i++){ 
		if(my_Board[i][0].statusBlock==STATUS_OUTOFRANGE)
			return ;

		for(j=0;j<MAXBOARD;j++){
			switch(my_Board[i][j].statusBlock){
			case STATUS_OPEN:
				printf(" %d ",my_Board[i][j].cntNearMine);
				break;
			case STATUS_CLOSE:
				printf(" %d ",my_Board[i][j].indexBlock);
				break;
			case STATUS_FLAG:
				printf(" F ");
				break;	
			case STATUS_OUTOFRANGE:
				printf("\n");
				j=MAXBOARD;
				break;
			default:
				break;
			}

		}
	}
}



//HACK: 2\C1\DFfor\B9\AE\B0\FA 2\C1\DFif\B9\AE\C0\B8\B7\CE \B0\A1\B5\B6\BC\BA\C0\CC \B6\B3\BE\EE\C1\F8\B4\D9. if\B9\AE\B8\B8 \C7Լ\F6\B7\CE \B3\AA\B4\AD \BC\F6 \C0\D6\C0\BB \B0\CD \B0\B0\B4\D9.
int IsVictory(Board my_Board[][MAXBOARD], int boardRows, int boardCols) {
	int i, j;
	int checkvictory = 1; //ó\C0\BD\BF\A1\B4\C2 \BD¸\AE\BF\A9\BAθ\A6 \BD¸\AE(1)\B7\CE \B5д\D9.

	for (i = 0; i < boardRows; i++) {
		for (j = 0; j < boardCols; j++) {

			//ĭ\C0\C7 \BB\F3\C5°\A1 \B4\DD\C8\F7\B0ų\AA \C7÷\B9\B1\D7\C0\CF \B0\E6\BF\EC, \C1\F6\B7ڰ\A1 \BE\F8\C0\B8\B8\E9 \BD¸\AE\BEƴ\D4 \B9\DDȯ
			if (my_Board[i][j].statusMine==STATUS_CLOSE || my_Board[i][j].statusMine==STATUS_FLAG){
				if (my_Board[i][j].statusMine == NORMAL) {
					checkvictory = 1;
					return checkvictory;
				}
			}

			//\C1\F6\C1\A4\B5\C8 ĭ\C0\BB \B3Ѿ \B0˻\E7\C7ϸ\E9 \BF\C0\B7\F9\C3\E2\B7\C2
			if (my_Board[i][j].statusMine == STATUS_OUTOFRANGE) {
				printf("IsVictory func ourofrange error\n");
				getchar();
			}
			
		}
	}

	return checkvictory;
}

void CntMine(Board my_Board[][MAXBOARD], int row, int col, int boardRows, int boardCols) {
	int cnt = 0; //\C1\F6\B7\DA \BC\F6 \BC\BC\B1\E2
	int checkrow, checkcol;

	//\C1\D6\C0\A7\C0\C7 9\B0\B3\C0\C7 ĭ\B5\E9\C0\BB 1\C7྿ üũ\C7Ѵ\D9
	for (checkrow = row - 1; checkrow <= row + 1; checkrow++) {
		//üũ\C7ϴ\C2 \C7\E0\C0\CC \B0\D4\C0\D3\C6\C7 \B9\FC\C0\A7 \B3\BB\BF\A1 \C0ִ°\A1?
		if (checkrow >= 0 && checkrow < boardRows) {

			//üũ\C7ϴ\C2 \C7\E0\C0\C7 \B0\A2 \BF\AD\C0\BB üũ\C7Ѵ\D9.
			for (checkcol = col - 1; checkcol <= col + 1; checkcol++) {
				//üũ\C7ϴ\C2 \BF\AD\C0\CC \B0\D4\C0\D3\C6\C7 \B9\FC\C0\A7 \B3\BB\BF\A1 \C0ִ°\A1?
				if (checkcol >= 0 && checkcol < boardCols) {
			
					//üũ\C7ϴ\C2 ĭ\BF\A1 \C1\F6\B7ڰ\A1 \C0\D6\C0\B8\B8\E9 cnt 1 \C1\F5\B0\A1
					if (my_Board[checkrow][checkcol].statusMine == MINE) {
						cnt++;
					}
				}
			}
		}
	}

	my_Board[row][col].cntNearMine = cnt;

	if (cnt == 0) {
		for (checkrow = row - 1; checkrow <= row + 1; checkrow++) {
			//üũ\C7ϴ\C2 \C7\E0\C0\CC \B0\D4\C0\D3\C6\C7 \B9\FC\C0\A7 \B3\BB\BF\A1 \C0ִ°\A1?
			if (checkrow >= 0 && checkrow < boardRows) {

				//üũ\C7ϴ\C2 \C7\E0\C0\C7 \B0\A2 \BF\AD\C0\BB üũ\C7Ѵ\D9.
				for (checkcol = col - 1; checkcol <= col + 1; checkcol++) {
					//üũ\C7ϴ\C2 \BF\AD\C0\CC \B0\D4\C0\D3\C6\C7 \B9\FC\C0\A7 \B3\BB\BF\A1 \C0ִ°\A1?
					if (checkcol >= 0 && checkcol < boardCols) {

						//üũ\C7ϴ\C2 ĭ\C0\CC \B4\DD\C8\F9 \BB\F3\C5\C2\C0\CF \B0\E6\BF\EC, \BF\AD\B8\B0 \BB\F3\C5·\CE \B9ٲٰ\ED(cnt\B0\A1 0\C0̹Ƿ\CE \C1\F6\B7ڴ\C2 \BE\F8\B4\D9) CntMine\C7Լ\F6 \BD\C7\C7\E0
						if (my_Board[checkrow][checkcol].statusBlock == STATUS_CLOSE) {
							my_Board[checkrow][checkcol].statusBlock == STATUS_OPEN;
							CntMine(my_Board, checkrow, checkcol, boardRows, boardCols);
						}
					}
				}
			}
		}
	}
}


void Play(Board my_Board[][MAXBOARD], int boardRows, int boardCols) {
	DrawBoard(*my_Board,boardRows, boardCols);
	MineAllocate(*my_Board, boardRows, boardCols);
	IsGameReset();
	return;
}

