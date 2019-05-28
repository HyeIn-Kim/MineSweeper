#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Minesweeper.h"

void MineAllocate(int boardRows, int boardCols, int inrow, int incol) {
	const double mineRate = 0.15;
	int mineNum = (boardRows * boardCols) * mineRate;
	int row;
	int col;

	srand(time(NULL));

	while (mineNum > 0) {
		row = rand() % boardRows;
		col = rand() % boardCols;

		if (my_Board[row][col].statusMine == NORMAL) {

			if (row != inrow || col != incol) {
				my_Board[row][col].statusMine = MINE;
				mineNum--;
			}

		}
	}
}





//HACK: maybe can divide into subfunction
int IsVictory(int boardRows, int boardCols) {
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

void CntMine(int row, int col, int boardRows, int boardCols) {
	int cnt = 0;
	int checkrow, checkcol;

	for (checkrow = row - 1; checkrow <= row + 1; checkrow++) {
		if (checkrow >= 0 && checkrow < boardRows) {

			for (checkcol = col - 1; checkcol <= col + 1; checkcol++) {
				if (checkcol >= 0 && checkcol < boardCols) {

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
			if (checkrow >= 0 && checkrow < boardRows) {

				for (checkcol = col - 1; checkcol <= col + 1; checkcol++) {
					if (checkcol >= 0 && checkcol < boardCols) {

						if (my_Board[checkrow][checkcol].statusBlock == STATUS_CLOSE) {
							my_Board[checkrow][checkcol].statusBlock = STATUS_OPEN;
							CntMine(checkrow, checkcol, boardRows, boardCols);
						}

					}
				}
			}
		}
	}
}

int OpenBlock(int row, int col, int boardRows, int boardCols) {
	if (my_Board[row][col].statusBlock == STATUS_CLOSE) {

		if (my_Board[row][col].statusMine == MINE) {
			my_Board[row][col].statusBlock = STATUS_OPEN;
			return 1;
		}

		else {
			my_Board[row][col].statusBlock = STATUS_OPEN;
			CntMine(row, col, boardRows, boardCols);
			return 0;
		}

	}

	return 0;
}

void FlagBlock(int row, int col) {
	if (my_Board[row][col].statusBlock == STATUS_FLAG) {
		my_Board[row][col].statusBlock = STATUS_CLOSE;
	}

	else {

		if (my_Board[row][col].statusBlock == STATUS_CLOSE) {
			my_Board[row][col].statusBlock = STATUS_FLAG;
		}

	}

}

void Play(int boardRows, int boardCols) {
	int init = 0;
	int row, col;
	int action;
	COORD pos;
	COORD firstquarypos;
	COORD secondquarypos;

	do {
		printf("\n");
		DrawBoard(boardRows, boardCols);

		firstquarypos = getCurrentCursorPos();

		do {
			setCurrentCursorPos(firstquarypos.X, firstquarypos.Y);
			printf("\nPlease Enter Rows 0~%d / Cols 0~%d: ", boardRows - 1, boardCols - 1);
			pos = getCurrentCursorPos();
			printf("        ");
			setCurrentCursorPos(pos.X, pos.Y);
			scanf_s(" %d %d", &row, &col);

		} while (!checkRowsinGame(row, boardRows) || !checkColsinGame(col, boardCols));

		if (init == 0) {
			MineAllocate(boardRows, boardCols, row, col);
			init = 1;
		}

		secondquarypos = getCurrentCursorPos();

		do {
			setCurrentCursorPos(secondquarypos.X, secondquarypos.Y);
			printf("\nSelect your action (1: Open Block / 2: Flag):");
			pos = getCurrentCursorPos();
			printf("        ");
			setCurrentCursorPos(pos.X, pos.Y);
			scanf_s(" %d", &action);

		} while (!ActionInRange(action));

		switch (action) {
		case 1:
			if (OpenBlock(row, col, boardRows, boardCols)) {
				system("cls");

				DrawBoard(boardRows, boardCols);
				printf("Game Over!\n");
				return;
			}
			break;

		case 2:
			FlagBlock(row, col);
			break;

		}

	} while (!IsVictory(boardRows, boardCols));

	//FIX 
	system("cls");

	OpenAllBlock(boardRows, boardCols, row, col);
	DrawBoard(boardRows, boardCols);

	printf("You Win!\n");

}


void OpenAllBlock(int boardRows, int boardCols, int inrow, int incol) {
	int i, j;

	for (i = 0; i < boardRows; i++) {
		for (j = 0; j < boardCols; j++) {
			my_Board[i][j].statusBlock = STATUS_OPEN;
		}
	}

}
