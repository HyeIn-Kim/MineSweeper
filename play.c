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

//HACK: 2중for문과 2중if문으로 가독성이 떨어진다. if문만 함수로 나눌 수 있을 것 같다.
int IsVictory(Board **my_Board, int boardRows, int boardCols) {
	int i, j;
	int checkvictory = 1; //처음에는 승리여부를 승리(1)로 둔다.

	for (i = 0; i < boardRows; i++) {
		for (j = 0; j < boardCols; j++) {

			//칸의 상태가 닫히거나 플레그일 경우, 지뢰가 없으면 승리아님 반환
			if (my_Board[i][j].statusMine==STATUS_CLOSE || my_Board[i][j].statusMine==STATUS_FLAG){
				if (my_Board[i][j].statusMine == NORMAL) {
					checkvictory = 1;
					return checkvictory;
				}
			}

			//지정된 칸을 넘어서 검사하면 오류출력
			if (my_Board[i][j].statusMine == STATUS_OUTOFRANGE) {
				printf("IsVictory func ourofrange error\n");
				getchar();
			}
			
		}
	}

	return checkvictory;
}



