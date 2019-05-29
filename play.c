#include <stdlib.h>
#include <time.h>
#include "Minesweeper.h"

void MineAllocate(void) {
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
int IsVictory(void) {
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

void CntMine(int _row, int _col) {
	int cnt = 0;
	int checkrow, checkcol;

	for (checkrow = _row - 1; checkrow <= _row + 1; checkrow++) {
		if (CheckRowsinGame(checkrow)) {

			for (checkcol = _col - 1; checkcol <= _col + 1; checkcol++) {
				if (CheckColsinGame(checkcol)) {

					if (my_Board[checkrow][checkcol].statusMine == MINE) {
						cnt++;
					}

				}
			}
		}
	}

	my_Board[_row][_col].cntNearMine = cnt;

	if (cnt == 0) {

		for (checkrow = _row - 1; checkrow <= _row + 1; checkrow++) {
			if (CheckRowsinGame(checkrow)) {

				for (checkcol = _col - 1; checkcol <= _col + 1; checkcol++) {
					if (CheckColsinGame(checkcol)) {

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

int OpenBlock(void) {
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

void FlagBlock(void) {
	if (my_Board[row][col].statusBlock == STATUS_FLAG) {
		my_Board[row][col].statusBlock = STATUS_CLOSE;
	}

	else {

		if (my_Board[row][col].statusBlock == STATUS_CLOSE) {
			my_Board[row][col].statusBlock = STATUS_FLAG;
		}

	}

}

void OpenAllBlock(void) {
	int i, j;

	for (i = 0; i < boardRows; i++) {
		for (j = 0; j < boardCols; j++) {
			my_Board[i][j].statusBlock = STATUS_OPEN;
		}
	}

}

void Play(void) {
	int init = 0;
	int action;
	COORD pos;
	COORD currentPos;

	do {

		printf("\n");
		DrawBoard();
		currentPos = GetCurrentCursorPos();

		do {

			SetCurrentCursorPos(currentPos.X, currentPos.Y);
			printf("\nPlease Enter Rows 1~%d / Cols 1~%d: ", boardRows, boardCols);
			pos = GetCurrentCursorPos();
			printf("        ");
			SetCurrentCursorPos(pos.X, pos.Y);
			scanf(" %d %d", &row, &col);

			row = row - 1;
			col = col - 1;

		} while (!CheckRowsinGame(row) || !CheckColsinGame(col));

		if (init == 0) {
			MineAllocate();
			init = 1;
		}

		currentPos = GetCurrentCursorPos();

		do {

			SetCurrentCursorPos(currentPos.X, currentPos.Y);
			printf("\nSelect your action (1: Open Block / 2: Flag):");
			pos = GetCurrentCursorPos();
			printf("        ");
			SetCurrentCursorPos(pos.X, pos.Y);
			scanf(" %d", &action);

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