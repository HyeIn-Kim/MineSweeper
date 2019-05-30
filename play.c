#include <stdlib.h>
#include <time.h>
#include "Minesweeper.h"

/**
* 게임판의 칸 수의 15%에 지뢰 무작위로 배치한다.
*
* @param void
* @return 없음
*/

void MineAllocate(void) {
	const double mineRate = 0.15; /* 지뢰 비율 */
	int mineNum = (boardRows * boardCols) * mineRate;
	int allocateRow;
	int allocateCol;

	srand(time(NULL));

	/* mineNum만큼의 지뢰가 배치되면 반복문 종료 */
	while (mineNum > 0) {

		/* 랜덤으로 칸을 받는다. */
		allocateRow = rand() % boardRows;
		allocateCol = rand() % boardCols;

		/* 지뢰가 없는 칸일 경우 지뢰를 배치한다*/
		if (my_Board[allocateRow][allocateCol].statusMine == NORMAL) {
			if (allocateRow != row || allocateCol != col) {
				my_Board[allocateRow][allocateCol].statusMine = MINE;
				mineNum--;
			}

		}
	}
}

/**
* 게임판을 검사한 후 승리여부를 반환한다.
*
* @param void
* @return 승리일 경우 1, 승리가 아닐 경우 0
* @exception 검사하는 칸이 게임판 내부의 칸이 아닐 경우 오류메시지 반환
*/

int IsVictory(void) {
	int i, j;
	int checkvictory = 1; //initial->victory

						  /* 승리시 checkvictory=1인 상태로 반복문 종료 */
	for (i = 0; i < boardRows; i++) {
		for (j = 0; j < boardCols; j++) {

			/* 칸의 상태가 STATUS_CLOSE이거나 STATUS_FLAG인 경우, 지뢰가 없을 때 승리가 아님을 반환 */
			if (my_Board[i][j].statusBlock == STATUS_CLOSE || my_Board[i][j].statusBlock == STATUS_FLAG) {
				if (my_Board[i][j].statusMine != MINE) {
					checkvictory = 0;
					return checkvictory;
				}
			}

			/* 검사하는 칸이 게임판 내부의 칸이 아닐경우 오류메시지 출력 */
			if (my_Board[i][j].statusMine == STATUS_OUTOFRANGE) {
				printf("IsVictory func ourofrange error\n");
				getchar();
			}

		}
	}

	/* 승리 반환 */
	return checkvictory;
}

/**
* 인자로 받은 행과 열에 해당하는 칸 주위의 인접 지뢰 개수를 조사한 후,
* 지뢰의 개수가 0인 경우 주변 8방향의 지뢰검사를 수행한다.
* 그 후 지뢰의 개수를 반환한다.
*
* @param int row, int col
* @return 인접 지뢰 개수
*/

void CntMine(int _row, int _col) {
	int cnt = 0;
	int checkrow, checkcol;

	/* 인자로 받은 행과 열에 해당하는 칸 주위의 지뢰 개수 조사 */
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

	/* 조사한 지뢰 개수 할당 */
	my_Board[_row][_col].cntNearMine = cnt;

	/* 지뢰의 개수가 0인 경우 재귀를 통해 주변 8방향의 칸들 중 닫힌 칸에서 지뢰검사 수행 */
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

/**
* 게임판의 선택한 칸이 닫힌 경우 열린상태로 만들고 칸에 지뢰가 있을 경우 1을 반환한다.
* 선택한 칸이 열려있거나 칸에 지뢰가 없을 경우 인접지뢰의 수를 세고 0을 반환한다.
*
* @param void
* @return 지뢰가 있을 경우 1, 지뢰가 없을 경우 0
*/

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

/**
* 게임판의 선택한 칸에 깃발 꽂는다.
*
* @param void
* @return 없음

*/

void FlagBlock(void) {
	/* 선택한 칸에 깃발이 꽂혀있는 경우 깃발을 해재한다. */
	if (my_Board[row][col].statusBlock == STATUS_FLAG) {
		my_Board[row][col].statusBlock = STATUS_CLOSE;
	}

	/* 선택한 칸에 깃발이 꽂혀있지 않고 닫힌 상태인 경우 깃발을 꽂는다. */
	else {

		if (my_Board[row][col].statusBlock == STATUS_CLOSE) {
			my_Board[row][col].statusBlock = STATUS_FLAG;
		}

	}

}

/**
* 게임판의 모든 블록을 STATUS_OPEN상태로 만든다.
*
* @param void
* @return 없음
*/
void OpenAllBlock(void) {
	int i, j;

	for (i = 0; i < boardRows; i++) {
		for (j = 0; j < boardCols; j++) {
			my_Board[i][j].statusBlock = STATUS_OPEN;
		}
	}

}

/**
* 게임판에서 칸을 선택한다.
*
* @param void
* @return 없음
*/
void InputBoard(void) {
	COORD pos;
	COORD currentPos;

	/* 커서의 시작위치를 저장한다 */
	currentPos = GetCurrentCursorPos();
	SetCurrentCursorPos(currentPos.X, currentPos.Y);

	/* 입력을 받겠다는 문자열을 출력하고 선택할 칸의 행과 열을 입력을 받는다*/
	printf("\nPlease Enter Rows 1~%d / Cols 1~%d:", boardRows, boardCols);
	pos = GetCurrentCursorPos();
	printf("        \n\n");
	printf("                                                   ");
	SetCurrentCursorPos(pos.X, pos.Y);
	scanf(" %d %d", &row, &col);
	getchar();
	/* 배열이므로 입력받은 행과 열에서 1을 뺀다. */
	row = row - 1;
	col = col - 1;

	/* 커서의 위치를 입력 받겠다는 문자열 뒤로 위치시킨다*/
	SetCurrentCursorPos(currentPos.X, currentPos.Y);
}

/**
* 게임에서의 행동을 입력받는다.
*
* @param void
* @return 칸 열기일 경우 1반환, 깃발꽂기일 경우 2 반환
*/
int InputAction(void) {
	int action;
	COORD pos;
	COORD currentPos;

	/* 입력을 받겠다는 문자열을 출력하고 선택할 칸의 행과 열을 입력을 받는다*/
	currentPos = GetCurrentCursorPos();
	SetCurrentCursorPos(currentPos.X, currentPos.Y);

	/* 입력을 받겠다는 문자열을 출력하고 선택할 행동을 입력을 받는다*/
	printf("\n\n\nSelect your action (1: Open Block / 2: Flag):");
	pos = GetCurrentCursorPos();
	printf("        ");
	SetCurrentCursorPos(pos.X, pos.Y);

	scanf(" %d", &action);
	getchar();
	SetCurrentCursorPos(currentPos.X, currentPos.Y);
	/* 행동을 반환한다. */
	return action;
}

/**
* 게임을 실행시킨다.
*
* @param void
* @return 없음
*/
void Play(void) {
	int init = 0;
	int action;

	/* 승리 전까지 반복문을 통해 게임을 진행시킨다. */
	do {

		/* 게임판을 그린다. */
		printf("\n");
		DrawBoard();

		do {

			/* 칸을 선택한다 */
			InputBoard();

		} while (!CheckRowsinGame(row) || !CheckColsinGame(col));

		/* 처음으로 칸을 선택한 경우 지뢰를 배치시킨다. */
		if (init == 0) {
			MineAllocate();
			init = 1;
		}

		/* 행동을 받는다. */
		do {

			action = InputAction();

		} while (!ActionInRange(action));

		/* 각각의 행동에 맞게 동작
		*1. 칸 열기
		*2. 깃발꽂기
		*/
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

	/* 승리 */
	system("cls");

	OpenAllBlock();
	DrawBoard();

	printf("You Win!\n");

}