#include "Minesweeper.h"

void DrawBoard(void) {
	int i, j;
	COORD pos;
	SetCurrentCursorPos(OFFSET_X, OFFSET_Y);

	for (i = 0; i < boardRows; i++) {

		if (my_Board[i][0].statusBlock == STATUS_OUTOFRANGE) {
			return;
		}

		for (j = 0; j < boardCols; j++) {
			pos = GetCurrentCursorPos();

			switch (my_Board[i][j].statusBlock) {
			case STATUS_OPEN:
				if (my_Board[i][j].statusMine == MINE) {
					printf("★");
				}
				else {
					printf("%d ", my_Board[i][j].cntNearMine);
				}
				break;

			case STATUS_CLOSE:
				printf("○");
				break;

			case STATUS_FLAG:
				printf("▶");
				break;

			default:
				break;
			}

			SetCurrentCursorPos(pos.X + 4, pos.Y);
		}

		printf("\n");
		pos = GetCurrentCursorPos();

		SetCurrentCursorPos(pos.X + OFFSET_X, pos.Y + 1);
	}
}

/**
* 게임시작시 화면을 출력한다.
*
* @param void
* @return 없음
*/

void IntroShow(void) {

	printf("★★    ★★  ★★★  ★★    ★  ★★★★★\n");
	printf("★★    ★★    ★    ★ ★   ★  ★\n");
	printf("★ ★  ★ ★    ★    ★  ★  ★  ★★★★★\n");
	printf("★  ★★  ★    ★    ★   ★ ★  ★\n");
	printf("★  ★★  ★  ★★★  ★    ★★  ★★★★★");

}
