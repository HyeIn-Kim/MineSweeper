#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Minesweeper.h"

void MineAllocate() {
	const double mineRate = 0.15;
	int mineNum = (boardRows * boardCols) * mineRate;
	int allocateRow;
	int allocateCol;

	srand(time(NULL));

	while (mineNum > 0) {
		allocateRow = rand() % boardRows;
		allocateCol = rand() % boardCols;

		if (my_Board[allocateRow][allocateCol].statusMine == NORMAL) {
			if (allocateRow != row || allocateCol != col) {
				my_Board[allocateRow][allocateCol].statusMine = MINE;
				mineNum--;
			}

		}
	}
}



//HACK: maybe can divide into subfunction
int IsVictory() {
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

void CntMine(int row, int col) {
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
							CntMine(checkrow, checkcol);
						}

					}
				}
			}
		}
	}
}

int OpenBlock() {
	if (my_Board[row][col].statusBlock == STATUS_CLOSE) {

		if (my_Board[row][col].statusMine == MINE) {
			my_Board[row][col].statusBlock = STATUS_OPEN;
			return 1;
		}

		else {
			my_Board[row][col].statusBlock = STATUS_OPEN;
			CntMine(row, col);
			return 0;
		}

	}

	return 0;
}

void FlagBlock() {
	if (my_Board[row][col].statusBlock == STATUS_FLAG) {
		my_Board[row][col].statusBlock = STATUS_CLOSE;
	}

	else {

		if (my_Board[row][col].statusBlock == STATUS_CLOSE) {
			my_Board[row][col].statusBlock = STATUS_FLAG;
		}

	}

}

void Play() {
	int init = 0;
	int action;
	COORD pos;
	COORD firstquarypos;
	COORD secondquarypos;

	do {
		printf("\n");
		DrawBoard();
		firstquarypos = getCurrentCursorPos();

		do {
			setCurrentCursorPos(firstquarypos.X, firstquarypos.Y);
			printf("\nPlease Enter Rows 0~%d / Cols 0~%d: ", boardRows - 1, boardCols - 1);
			pos = getCurrentCursorPos();
			printf("        ");
			setCurrentCursorPos(pos.X, pos.Y);
			scanf_s(" %d %d", &row, &col);

		} while (!checkRowsinGame(row) || !checkColsinGame(col));

		if (init == 0) {
			MineAllocate(row, col);
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
			if (OpenBlock()) {
				system("cls");
				DrawBoard();
				printf("Game Over!\n");
				return;
			}
			break;

		case 2:
			FlagBlock();
			break;

		}

	} while (!IsVictory());

	//FIX 
	system("cls");

	OpenAllBlock();
	DrawBoard();

	printf("You Win!\n");

}


void OpenAllBlock() {
	int i, j;

	for (i = 0; i < boardRows; i++) {
		for (j = 0; j < boardCols; j++) {
			my_Board[i][j].statusBlock = STATUS_OPEN;
		}
	}

}
