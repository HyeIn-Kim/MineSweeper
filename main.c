#include <stdlib.h>
#include <stdio.h>
#include "minesweeper.h"


int main()
{
	Board my_Board[16][16];
	int boardRows, boardCols; 
	boardRows = 0;
	boardCols = 0;
	while (!checkRows(boardRows) || !checkCols(boardCols)){
		printf("%d~%d Please enter rows, cols:",MINBOARD,MAXBOARD); 
		scanf_s("%d %d", &boardRows, &boardCols);
	}
	
	InitBoard(*my_Board);
	Play(*my_Board);

    return 0;
}


