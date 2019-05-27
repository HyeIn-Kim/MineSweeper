#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "minesweeper.h"
#include "Windows.h"

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
	COORD pos;
	IntroShow();
	while (!checkRows(boardRows) || !checkCols(boardCols)){
		setCurrentCursorPos(0,7);
		printf("%d~%d Please enter rows, cols:",MINBOARD,MAXBOARD); 
		pos=getCurrentCursorPos();
		printf("        ");
		setCurrentCursorPos(pos.X,pos.Y);
		scanf_s(" %d %d", &boardRows, &boardCols);
	}
	system("cls");
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
				my_Board[i][j].cntNearMine=0;
			}
			my_Board[i][j].statusMine=NORMAL;
		}
	}
}

void IntroShow() {
	printf("���      �֡� �ââ� ��     �� �ߡߡߡ�\n");
	printf("���      �֡�   ��   ����   �� ��\n");
	printf("�� ��    �� ��   ��   �� ��  �� �ߡߡߡ�\n");
	printf("��  ��  ��  ��   ��   ��  �� �� ��\n");
	printf("��   �٢�   �� �ââ� ��   ���� �ߡߡߡ�\n\n");
}
