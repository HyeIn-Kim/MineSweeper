#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Minesweeper.h"

void MineAllocate(Board my_Board[][MAXBOARD], int boardRows, int boardCols) {
	srand(time(NULL));
	const double mineRate = 0.15;
	int mineNum = (boardRows * boardCols) * mineRate;
	int row;
	int col;

	while (mineNum > 0) {
		row = rand() % boardRows;
		col = rand() % boardCols;
		if (my_Board[row][col].statusMine == NORMAL) {
			my_Board[row][col].statusMine = MINE;
			mineNum--;
		}
	}
}


void DrawBoard(Board my_Board[][MAXBOARD]){
	int i,j;
	int cntMine;
	for(i=0;i<MAXBOARD;i++){ 
		if(my_Board[i][0].statusBlock==STATUS_OUTOFRANGE)
			return ;

		for(j=0;j<MAXBOARD;j++){
			switch(my_Board[i][j].statusBlock){
			case STATUS_OPEN:
				/* CntMine
				printf(" %d ",cntMine);
				*/
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


void Play(Board my_Board[][MAXBOARD], int boardRows, int boardCols) {
	DrawBoard(*my_Board);
	MineAllocate(*my_Board, boardRows, boardCols);
	IsGameReset();
	return;
}



