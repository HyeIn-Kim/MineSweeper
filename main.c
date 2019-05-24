#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "minesweeper.h"

int boardRows, boardCols; 

int main()
{
	Board my_Board[MAXBOARD][MAXBOARD];
	while(IsGameReset()){
		boardRows = 0;
		boardCols = 0;
		setBoardSize();
		InitBoard(*my_Board, boardRows, boardCols);
		Play(*my_Board, boardRows, boardCols);
	}
}
void setBoardSize(){
	while (!checkRows(boardRows) || !checkCols(boardCols)){
		printf("%d~%d Please enter rows, cols:",MINBOARD,MAXBOARD); 
		scanf_s(" %d %d", &boardRows, &boardCols);
	}
}
void InitBoard(Board my_Board[][MAXBOARD], int boardRows, int boardCols){
	int i,j;
	int index=0;
	for(i=0;i<MAXBOARD;i++){ 
		for(j=0;j<MAXBOARD;j++){
			if(i>=boardRows || j>=boardCols){
				my_Board[i][j].statusBlock=STATUS_OUTOFRANGE;
			}
			else{
				index++;
				my_Board[i][j].statusBlock=STATUS_CLOSE;
				my_Board[i][j].indexBlock=index;
				my_Board[i][j].cntNearMine=0;
			}
			my_Board[i][j].statusMine=NORMAL;
		}
	}
}
