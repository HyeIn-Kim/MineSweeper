#include "Minesweeper.h"


/** 
* 게임판을 그리는 함수
* 게임이 진행되는 동안 play 함수 내에서 꾸준히 호출된다
* 블록의 상태를 시각적으로 나타내는 일을 한다
* @param void
* @return void 
*/

void DrawBoard(void) {
	int i, j;
	COORD pos;	/* 현재 커서의 위치 */
	/* 호출시 설정한 위치로 커서를 옮긴다. 게임판은 고정된 위치에서 그려진다 */
	SetCurrentCursorPos(OFFSET_X, OFFSET_Y);

	for (i = 0; i < boardRows; i++) {
		/* 범위 밖 블록은 그리지 않음 */
		if (my_Board[i][0].statusBlock == STATUS_OUTOFRANGE) {
			return;
		}

		for (j = 0; j < boardCols; j++) {
			pos = GetCurrentCursorPos();

			switch (my_Board[i][j].statusBlock) {
			case STATUS_OPEN:
				if (my_Board[i][j].statusMine == MINE) {
					/* 지뢰 */
					printf("★");
				}
				else {
					/* 지뢰가 아닌 경우 인접 지뢰 수를 표기 */
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
			/* 커서를 오른쪽으로 두 칸 옮긴다. x축의 이동 단위는 2 */

			SetCurrentCursorPos(pos.X + 4, pos.Y);
		}

		printf("\n");
		pos = GetCurrentCursorPos();
		/* 커서를 아래쪽으로 한 칸 옮긴다. y축의 이동 단위는 1 */
		SetCurrentCursorPos(pos.X + OFFSET_X, pos.Y + 1);
	}
}

void IntroShow(void) {

	printf("★★    ★★  ★★★  ★★    ★  ★★★★★\n");
	printf("★★    ★★    ★    ★ ★   ★  ★\n");
	printf("★ ★  ★ ★    ★    ★  ★  ★  ★★★★★\n");
	printf("★  ★★  ★    ★    ★   ★ ★  ★\n");
	printf("★  ★★  ★  ★★★  ★    ★★  ★★★★★");

}
