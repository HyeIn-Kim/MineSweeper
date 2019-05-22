#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Minesweeper.h"

void MineAllocate(Board my_Board[][MAXBOARD], int boardRows, int boardCols, int inrow, int incol) {
	const double mineRate = 0.15;
	int mineNum = (boardRows * boardCols) * mineRate;
	int row;
	int col;

	srand(time(NULL));

	while (mineNum > 0) {
		row = rand() % boardRows;
		col = rand() % boardCols;
		if (my_Board[row][col].statusMine == NORMAL) {
			if (row == inrow && col == incol)
				continue;

			my_Board[row][col].statusMine = MINE;
			mineNum--;
		}
	}

}


void DrawBoard(Board my_Board[][MAXBOARD], int boardRows, int boardCols) {
	int i, j;
	for (i = 0;i<MAXBOARD;i++) {
		if (my_Board[i][0].statusBlock == STATUS_OUTOFRANGE)
			return;

		for (j = 0;j<MAXBOARD;j++) {
			switch (my_Board[i][j].statusBlock) {
			case STATUS_OPEN:
				printf(" %d ", my_Board[i][j].cntNearMine);
				break;
			case STATUS_CLOSE:
				printf(" %d ", my_Board[i][j].indexBlock);
				break;
			case STATUS_FLAG:
				printf(" F ");
				break;
			case STATUS_OUTOFRANGE:
				printf("\n");
				j = MAXBOARD;
				break;
			default:
				break;
			}

		}
	}
}



//HACK: maybe can divide into subfunction
int IsVictory(Board my_Board[][MAXBOARD], int boardRows, int boardCols) {
	int i, j;
	int checkvictory = 1; //initial->victory

	for (i = 0; i < boardRows; i++) {
		for (j = 0; j < boardCols; j++) {

			//closed or flaged->not mine->not victory
			if (my_Board[i][j].statusBlock == STATUS_CLOSE || my_Board[i][j].statusBlock == STATUS_FLAG) {
				if (my_Board[i][j].statusMine != MINE) {
					checkvictory = 0;
					return checkvictory;
				}
			}

			//errorcheck
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
							my_Board[checkrow][checkcol].statusBlock = STATUS_OPEN;
							CntMine(my_Board, checkrow, checkcol, boardRows, boardCols);
						}
					}
				}
			}
		}
	}
}

int OpenBlock(Board my_Board[][MAXBOARD], int row, int col, int boardRows, int boardCols) {
	if (my_Board[row][col].statusBlock == STATUS_CLOSE) {
		if (my_Board[row][col].statusMine == MINE) {
			return 1;
		}
		else {
			my_Board[row][col].statusBlock = STATUS_OPEN;
			CntMine(my_Board, row, col, boardRows, boardCols);
			return 0;
		}
	}
	return 0;
}

void FlagBlock(int row, int col, Board my_Board[][MAXBOARD]) {
	if (my_Board[row][col].statusBlock == STATUS_FLAG) {
		my_Board[row][col].statusBlock = STATUS_CLOSE;
	}
	else {
		my_Board[row][col].statusBlock = STATUS_FLAG;
	}
}

void Play(Board my_Board[][MAXBOARD], int boardRows, int boardCols) {
	static int init = 0;
	int row, col;
	int action;

	do {
		printf("\n");
		DrawBoard(*my_Board, boardRows, boardCols);

		do {
			printf("\nPlease Enter Rows 0~%d / Cols 0~%d: ", boardRows - 1, boardCols - 1);
			scanf_s(" %d %d", &row, &col);
		} while (!checkRowsinGame(row, boardRows) || !checkColsinGame(col, boardCols));

		if (init == 0) {
			MineAllocate(*my_Board, boardRows, boardCols, row, col);
			init = 1;
		}

		do {
			printf("\nSelect your action (1: Open Block / 2: Flag):");
			scanf_s(" %d", &action);
		} while (!ActionInRange(action));

		switch (action) {
		case 1:
			if (OpenBlock(my_Board, row, col, boardRows, boardCols)) {
				return;
			}
			break;
		case 2:
			FlagBlock(row, col, my_Board);
			break;
		}

	} while (!IsVictory(my_Board, boardRows, boardCols));

	IsGameReset();
}
