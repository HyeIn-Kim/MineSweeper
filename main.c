#include <stdlib.h>
#include <stdio.h>
#include "minesweeper.h"

int main()
{
	int i,j;
	Board my_Board[MAXBOARD][MAXBOARD];
	int boardRows, boardCols; 
	boardRows = 0;
	boardCols = 0;
	while (!checkRows(boardRows) || !checkCols(boardCols)){
		printf("%d~%d Please enter rows, cols:",MINBOARD,MAXBOARD); 
		scanf_s("%d %d", &boardRows, &boardCols);
	}
	
	InitBoard(my_Board, boardRows, boardCols);
	Play(*my_Board);

    return 0;
}

void InitBoard(Board my_Board[][MAXBOARD], int boardRows, int boardCols){
	int i,j;
	for(i=0;i<MAXBOARD;i++){ 
		for(j=0;j<MAXBOARD;j++){
			if(i>=boardRows || j>=boardCols){
				my_Board[i][j].statusBlock=STATUS_OUTOFRANGE;
			}
			else{
				my_Board[i][j].statusBlock=STATUS_CLOSE;
			}
			my_Board[i][j].statusMine=NORMAL;
		}
	}
}
