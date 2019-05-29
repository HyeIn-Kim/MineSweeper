#ifndef _MINESWEEPER_H
#define _MINESWEEPER_H

#include <stdio.h>
#include <Windows.h>
#pragma warning (disable:4996)

/* ***** 상수 ***** */
/**
 * UI 표현을 위한 오프셋
 * ┌──────────────── SCREEN ────────────────┐
 * │                   ↑                    │
 * │                OFFSET_Y                │
 * │                   ↓                    │
 * │             ○  ○  ○  ○  ○              │
 * │             ○  ○  ○  ○  ○              │  
 * │             ○  ○  ○  ○  ○              │
 * │← OFFSET_X → ○  ○  ○  ○  ○              │
 * │             ○  ○  ○  ○  ○              │
 * │                                        │
 * └────────────────────────────────────────┘
 */
#define OFFSET_X 10
#define OFFSET_Y 2

/* 각 칸의 지뢰 여부 */
#define NORMAL 0        // 지뢰 없음
#define MINE 1          // 지뢰 있음

/* 게임판의 최소, 최대 크기 */
#define MINBOARD 5
#define MAXBOARD 16

/**
 * 각 칸의 상태
 * STATUS_OPEN : 열린 칸
 * STATUS_FLAG : 깃발을 꽂은 칸
 * STATUS_CLOSE : 닫힌 칸
 * STATUS_OUTOFRANGE : 범위를 벗어난 칸
 * 유저가 입력하는 크기에 관계 없이 게임판은 항상 16x16으로 구현된다.
 * 유저가 5x5 게임판을 만들었을 경우,
 * 게임판 배열의 index 5 ~ 15는 모두 STATUS_OUTOFRANGE가 된다.
 */
#define STATUS_OPEN 100
#define STATUS_FLAG 101
#define STATUS_CLOSE 102
#define STATUS_OUTOFRANGE 103

/* ***** 구조체 ***** */
typedef struct Board {
	int statusBlock;    //블럭의 상태를 나타낸다. 열림, 닫힘, 깃발.
	int statusMine;     //지뢰 여부를 나타낸다.
	int cntNearMine;    //해당 칸을 기준으로 3x3에 지뢰가 몇 개인지를 나타낸다.
} Board;                //                  ○ ○ ○
                        //                  ○ ■ ○
                        //                  ○ ○ ○

/* ***** 전역 변수 ***** */
Board my_Board[MAXBOARD][MAXBOARD];
int boardRows;          //유저가 입력한 열 수
int boardCols;          //유저가 입력한 행 수
int row;                //유저가 선택한 열
int col;                //유저가 선택한 행

/* ***** 함수 ***** */
/* main.c */
void SetBoardSize(void);
void InitBoard(void);

/* play.c */
void MineAllocate(void);
int IsVictory(void); 
void CntMine(int, int);
int OpenBlock(void);
void FlagBlock(void);
void OpenAllBlock(void);
void InputBoard(void);
int InputAction(void);
void Play(void);

/* utilityfunctions.c */
int CheckRows(void);
int CheckCols(void);
int CheckRowsinGame(int);
int CheckColsinGame(int);
int IsGameReset(void);
int ActionInRange(int);
void SetCurrentCursorPos(int, int);
COORD GetCurrentCursorPos(void);

/* drawingfunctions.c */
void DrawBoard(void);
void IntroShow(void);

#endif