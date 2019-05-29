﻿#include <stdio.h>
#include "Minesweeper.h"

void DrawBoard() {
	int i, j;
	COORD pos;
	setCurrentCursorPos(OFFSET_X, OFFSET_Y);

	for (i = 0; i < boardRows; i++) {

		if (my_Board[i][0].statusBlock == STATUS_OUTOFRANGE) {
			return;
		}

		for (j = 0; j < boardCols; j++) {
			pos = getCurrentCursorPos();

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

			setCurrentCursorPos(pos.X + 4, pos.Y);
		}

		printf("\n");
		pos = getCurrentCursorPos();

		setCurrentCursorPos(pos.X + OFFSET_X, pos.Y + 1);
	}
}

void IntroShow() {

	printf("★★    ★★  ★★★  ★★    ★  ★★★★★\n");
	printf("★★    ★★    ★    ★ ★   ★  ★\n");
	printf("★ ★  ★ ★    ★    ★  ★  ★  ★★★★★\n");
	printf("★  ★★  ★    ★    ★   ★ ★  ★\n");
	printf("★  ★★  ★  ★★★  ★    ★★  ★★★★★");

}
