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

//HACK: 2��for���� 2��if������ �������� ��������. if���� �Լ��� ���� �� ���� �� ����.
int IsVictory(Board **my_Board, int boardRows, int boardCols) {
	int i, j;
	int checkvictory = 1; //ó������ �¸����θ� �¸�(1)�� �д�.

	for (i = 0; i < boardRows; i++) {
		for (j = 0; j < boardCols; j++) {

			//ĭ�� ���°� �����ų� �÷����� ���, ���ڰ� ������ �¸��ƴ� ��ȯ
			if (my_Board[i][j].statusMine==STATUS_CLOSE || my_Board[i][j].statusMine==STATUS_FLAG){
				if (my_Board[i][j].statusMine == NORMAL) {
					checkvictory = 1;
					return checkvictory;
				}
			}

			//������ ĭ�� �Ѿ �˻��ϸ� �������
			if (my_Board[i][j].statusMine == STATUS_OUTOFRANGE) {
				printf("IsVictory func ourofrange error\n");
				getchar();
			}
			
		}
	}

	return checkvictory;
}

void CntMine(Board **my_Board, int row, int col, int boardRows, int boardCols) {
	int cnt = 0; //���� �� ����
	int checkrow, checkcol;

	//������ 9���� ĭ���� 1�྿ üũ�Ѵ�
	for (checkrow = row - 1; checkrow <= row + 1; checkrow++) {
		//üũ�ϴ� ���� ������ ���� ���� �ִ°�?
		if (checkrow >= 0 && checkrow < boardRows) {

			//üũ�ϴ� ���� �� ���� üũ�Ѵ�.
			for (checkcol = col - 1; checkcol <= col + 1; checkcol++) {
				//üũ�ϴ� ���� ������ ���� ���� �ִ°�?
				if (checkcol >= 0 && checkcol < boardCols) {
			
					//üũ�ϴ� ĭ�� ���ڰ� ������ cnt 1 ����
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
			//üũ�ϴ� ���� ������ ���� ���� �ִ°�?
			if (checkrow >= 0 && checkrow < boardRows) {

				//üũ�ϴ� ���� �� ���� üũ�Ѵ�.
				for (checkcol = col - 1; checkcol <= col + 1; checkcol++) {
					//üũ�ϴ� ���� ������ ���� ���� �ִ°�?
					if (checkcol >= 0 && checkcol < boardCols) {

						//üũ�ϴ� ĭ�� ���� ������ ���, ���� ���·� �ٲٰ�(cnt�� 0�̹Ƿ� ���ڴ� ����) CntMine�Լ� ����
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



