#ifndef _DEFINE_
#define _DEFINE_

#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
using namespace std;

#define blank 0		//空白点
#define black 1		//黑方
#define white 2		//白方
#define inf 0x3f3f3f3f
#define inboard(a,b) (a>0 && a<=15 && b>0 && b<=15)		//用于检验招法是否在棋盘上
#define cvt_Player_to_Color(a) (a + 1)
#define cvt_to_Rival_Clr(a) (3 - a)

#define GRID_NUM 16		

extern const int posValue[GRID_NUM][GRID_NUM];
extern int counter;

struct point
{
	int x, y;
	int val;
	point(int input_x = 0, int input_y = 0) {
		x = input_x;
		y = input_y;
		val = posValue[input_x][input_y];
	}
	bool operator < (const point &a) const {
		return val > a.val;
	}
};

//声明
extern int chessBoard[GRID_NUM][GRID_NUM];

extern int piecesCounter[3];
extern point chessPieces[3][GRID_NUM * GRID_NUM];



#endif

