#include "Minesweeper.h"

/** 
* 입력 받은 행의 사이즈가 범위 내의 수인지 여부를 체크하는 함수
*
* @param void
* @return 행이 범위 내 수일 경우 1, 아닐 경우 0
*/
int CheckRows(void) {
	return (boardRows >= MINBOARD && boardRows <= MAXBOARD);
}

/** 
* 입력 받은 열의 사이즈가 범위 내의 수인지 여부를 체크하는 함수
*
* @param void
* @return 열이 범위 내 수일 경우 1, 아닐 경우 0
*/
int CheckCols(void) {
	return (boardCols >= MINBOARD && boardCols <= MAXBOARD);
}

/**
* 행이 게임판 내부의 행인지 여부를 체크하는 함수
*
* @param int currentRow 현재 행 번호
* @return 게임판 내부의 행일 경우 1, 아닐 경우 0
*/
int CheckRowsinGame(int currentRow) {
	return (currentRow >= 0 && currentRow < boardRows);
}

/**
* 열이 게임판 내부의 열인지 여부를 체크하는 함수
*
* @param int currentCol 현재 열 번호
* @return 게임판 내부의 열일 경우 1, 아닐 경우 0
*/
int CheckColsinGame(int currentCol) {
	return (currentCol >= 0 && currentCol < boardCols);
}


/**
* 재시작 여부를 묻는 함수
*
* @param void
* @return 최초 실행시 1, 재시작시 1, 끝낼 경우 0, 예외일 때 -1
*/
int IsGameReset(void){
	static int flag = 0;	/* 최초 실행여부 */
	char user;
	COORD pos;
	
	user = ' ';
	
	/* 최초 실행시 여부를 묻지 않고 true 반환 */
	if(flag == 0) {
		flag = 1; 
		return 1;
	}
	pos = GetCurrentCursorPos();

	/* 사용자가 올바른 값을 입력할 때까지 무한 반복 */
	while(user != 'y' && user != 'Y' && user != 'n' && user != 'N') {

		SetCurrentCursorPos(pos.X, pos.Y);

		printf("\nRetry? (Y/N):");
		scanf("%c", &user);

		if(user == 'y' || user == 'Y') {
			/* 재시작시 화면을 비운다 */
			system("cls");
			return 1;
		}

		if(user == 'n' || user == 'N') {
			return 0;
		}
	}

	/* 비정상적인 예외 상황 */
	return -1;
}

/**
* 사용자의 행동이 1(open) 또는 2(flag) 올바른 입력인지 체크하는 함수
*
* @param int action 사용자의 입력값
* @return 사용자의 입력이 올바른 입력일 경우 1, 아닐 경우 0
*/
int ActionInRange(int action) {
	if (action == 1 || action == 2) {
		return 1;
	}

	else {
		return 0;
	}
		
}

/**
* 원하는 좌표를 입력 받아 커서를 해당 위치로 이동시키는 함수
*
* @param int x, int y 각각의 x, y 좌표
* @return 없음
*/
void SetCurrentCursorPos(int x, int y) {
	COORD pos = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/**
* 현재 커서가 위치한 좌표를 반환하는 함수
*
* @param void
* @return 현재 커서의 위치를 담고 있는 2차원 좌표계
*/
COORD GetCurrentCursorPos(void) {
	COORD curPoint;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;			// 콘솔 정보

	/* 화면에 띄우는 콘솔 정보를 받아와 변수에 저장 */
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curPoint.X = curInfo.dwCursorPosition.X;
	curPoint.Y = curInfo.dwCursorPosition.Y;

	return curPoint;
}
