#include "Minesweeper.h"

/** 
* ***** MINESWEEPER GAME *****
* 2019-1 오픈소스SW개론(001) 과제 3~5 Project MineSweeper, Sejong University, Korea
* http://github.com/HyeIn-Kim/MineSweeper
*
* @LICENSE
* Apache License Version 2.0
* (라이센스 본문은 LICENSE를 참고해주세요.)
*
* @AUTHOR
* 16011200 김혜인 (https://github.com/HyeIn-Kim)
* 16011151 최한나 (https://github.com/hann3)
* 17011692 이도영 (https://github.com/woozu99)
*
* @VERSION 
* v2.1 
*
* @WARNING 행과 열 입력시 숫자가 아닌 문자 입력시 오류 발생
*
* May 30, 2019
*/


int main(void) {
	/* 최초 실행 반환값은 1 게임 종료시 사용자에게 게임 재시작 여부를 묻는다 */
	while(IsGameReset()){
		boardRows = 0;
		boardCols = 0;
		/* 사용자에게 행렬의 크기를 입력 받는다 */
		SetBoardSize();
		/* 입력 받은 행렬의 크기만큼 게임판의 블록 상태를 초기화 */
		InitBoard();
		/* 게임 시작 */
		Play();
	}

}

/**  
* 사용자에게 행렬의 크기를 입력 받는 함수
* 최소값과 최대값 사이의 수를 입력할 때까지 반복 
* @param void
* @return void 
* @exception 숫자가 아닌 문자를 입력하는 경우 무한 루프되는 현상 발생 
*/


void SetBoardSize(void) {
	COORD pos;	/* 현재 커서 위치를 저장 */
	IntroShow();
	/* 입력한 행렬 크기가 범위 내의 값을 가질 때까지 반복 */
	while (!CheckRows() || !CheckCols()) {
		/* 인트로 화면보다 아래쪽에 커서를 위치시킨다 */
		SetCurrentCursorPos(0, 7);
		printf("%d~%d Please enter rows, cols:", MINBOARD, MAXBOARD); 
		/* 이전 입력값을 지우기 위해 현재 위치 저장 후 공백으로 채운다 */
		pos = GetCurrentCursorPos();
		printf("        ");
		SetCurrentCursorPos(pos.X, pos.Y);
		scanf(" %d %d", &boardRows, &boardCols);

	}
	/* 화면을 비우기 위해 호출 */
	system("cls");

}

/** 
* 사용자에게 입력 받은 행렬 크기만큼 게임판을 초기화하는 함수 
* 블록의 상태, 인접한 지뢰의 수, 지뢰 여부를 초기화
* @param void
* @return void 
*/

void InitBoard(void){
	int i, j;
	for(i = 0; i < MAXBOARD; i++) {
		for(j = 0; j < MAXBOARD; j++) {
			/* 행렬을 벗어난 블록은 범위 밖으로 표시 */
			if(i >= boardRows || j >= boardCols) {
				my_Board[i][j].statusBlock = STATUS_OUTOFRANGE;
			}

			else {
				/* 블록의 초기 상태는 닫혀 있다. 지뢰가 배치되기 전이므로 지뢰 상태와 인접한 지뢰의 수를 초기화 */
				my_Board[i][j].statusBlock = STATUS_CLOSE;
				my_Board[i][j].cntNearMine = 0;
			}

			my_Board[i][j].statusMine = NORMAL;

		}
	}
}
