#include"Minesweeper.h"
#include<stdio.h>

void Play(Board my_Board[][MAXBOARD]){
	DrawBoard(*my_Board);
	IsGameReset();
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
				/* CntMine 구현 후 추가예정 
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