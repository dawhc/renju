#include "define.h"

#define UNVISITED 0
#define VISITED 1
// 棋型编号
#define TYPE_NUM 9
#define _FIVE 1
#define _FOUR 2
#define _S_FOUR 3
#define _THREE 4
#define _S_THREE 5
#define _TWO 6
#define _S_TWO 7
#define _ONE 8
// 先手优势
#define OFFENSIVE_WEIGHT 5

int typeCounter[TYPE_NUM];
bool vis[GRID_NUM][GRID_NUM][4];
bool visLine[GRID_NUM];

int analysisPoint(int *line, int lineSize, int nowPos) {
	// 分析某点在某条线上的棋形
	int nowClr = line[nowPos];
	int leftEdge = nowPos;
	int rightEdge = nowPos;
	memset(visLine, UNVISITED, sizeof(visLine));
	// 数组长度小于5无意义
	if (lineSize < 5) {
		for (int i = 1; i <= lineSize; i++)
			visLine[i] = VISITED;
		return 0;
	}
	// 连子范围
	while (leftEdge >= 1 && line[leftEdge] == nowClr) leftEdge--;
	leftEdge++;
	while (rightEdge <= lineSize && line[rightEdge] == nowClr) rightEdge++;
	rightEdge--;
	// 非障碍范围
	int leftRange = leftEdge;
	int rightRange = rightEdge;
	while (leftRange >= 1 && line[leftRange] != cvt_to_Rival_Clr(nowClr)) leftRange--;
	leftRange++;
	while (rightRange <= lineSize && line[rightRange] != cvt_to_Rival_Clr(nowClr)) rightRange++;
	rightRange--;
	// 无法连成五子
	if (rightRange - leftRange < 4) {
		for (int i = leftRange; i <= rightRange; i++)
			visLine[i] = VISITED;
		return 0;
	}
	// 防止重复标记
	for (int i = leftEdge; i <= rightEdge; i++)
		visLine[i] = VISITED;
		
	bool firstCase;

	switch (rightEdge - leftEdge) {
	case 3:
		if (leftEdge > 1 && rightEdge < lineSize && !line[leftEdge - 1] && !line[rightEdge + 1])
			return _FOUR; // 活四1 .oooo.
		else
			return _S_FOUR; // 冲四1 xoooo.

	case 2:
		if (leftEdge > 2 && !line[leftEdge - 1] && line[leftEdge - 2] == nowClr &&
			rightEdge < lineSize - 1 && !line[rightEdge + 1] && line[rightEdge + 2] == nowClr) {
			visLine[leftEdge - 2] = visLine[rightEdge + 2] = VISITED;
			return _FOUR; // 活四2 o.ooo.o
		}

		else if (firstCase = (leftEdge > 2 && !line[leftEdge - 1] && line[leftEdge - 2] == nowClr) ||
			rightEdge < lineSize - 1 && !line[rightEdge + 1] && line[rightEdge + 2] == nowClr) {
			if (firstCase)
				visLine[leftEdge - 2] = VISITED;
			else
				visLine[rightEdge + 2] = VISITED;
			return _S_FOUR; // 冲四2 o.ooo
		}
			

		else if (leftEdge > 1 && rightEdge < lineSize && !line[leftEdge - 1] && !line[rightEdge + 1]) {
			if (leftEdge > 2 && !line[leftEdge - 2] || rightEdge < lineSize - 1 && !line[rightEdge + 2])
				return _THREE; //活三1 ..ooo.
			else
				return _S_THREE; //眠三1 x.ooo.x
		}
		else
			return _S_THREE; //眠三2 xooo..

	case 1:
		if (firstCase = (leftEdge > 3 && !line[leftEdge - 1] && line[leftEdge - 2] == nowClr && line[leftEdge - 3] == nowClr) ||
			rightEdge < lineSize - 2 && !line[rightEdge + 1] && line[rightEdge + 2] == nowClr && line[rightEdge + 3] == nowClr) {
			if (firstCase)
				visLine[leftEdge - 3] = visLine[leftEdge - 2] = VISITED;
			else
				visLine[rightEdge + 3] = visLine[rightEdge + 2] = VISITED;
			return _S_FOUR; //冲四3 oo.oo
		}

		else if (firstCase = (leftEdge > 3 && !line[leftEdge - 3] && line[leftEdge - 2] == nowClr && !line[leftEdge - 1] && rightEdge < lineSize && !line[rightEdge + 1]) ||
			rightEdge < lineSize - 2 && !line[rightEdge + 3] && line[rightEdge + 2] == nowClr && !line[rightEdge + 1] && leftEdge > 1 && !line[leftEdge - 1]) {
			if (firstCase)
				visLine[leftEdge - 2] = VISITED;
			else
				visLine[rightEdge + 2] = VISITED;
			return _THREE; //活三2 .oo.o.
		}
			
		else if (firstCase = (leftEdge > 3 && !line[leftEdge - 1] && !line[leftEdge - 2] && line[leftEdge - 3] == nowClr) ||
			rightEdge < lineSize - 2 && !line[rightEdge + 1] && !line[rightEdge + 2] && line[rightEdge + 3] == nowClr) {
			if (firstCase)
				visLine[leftEdge - 3] = VISITED;
			else
				visLine[rightEdge + 3] = VISITED;
			return _S_THREE; //眠三2 o..oo
		}

		else if (firstCase = (leftEdge > 3 && !line[leftEdge - 3] && line[leftEdge - 2] == nowClr && !line[leftEdge - 1]) ||
			rightEdge < lineSize - 2 && !line[rightEdge + 3] && line[rightEdge + 2] == nowClr && !line[rightEdge + 1]) {
			if (firstCase)
				visLine[leftEdge - 2] = VISITED;
			else
				visLine[rightEdge + 2] = VISITED;
			return _S_THREE; //眠三3 .o.oox
		}

		else if (firstCase = (leftEdge > 1 && !line[leftEdge - 1] && rightEdge < lineSize - 1 && !line[rightEdge + 1] && line[rightEdge + 2] == nowClr) ||
			rightEdge < lineSize && !line[rightEdge + 1] && leftEdge > 2 && !line[leftEdge - 1] && line[leftEdge - 2] == nowClr) {
			if (firstCase)
				visLine[rightEdge + 2] = VISITED;
			else
				visLine[leftEdge - 2] = VISITED;
			return _S_THREE; //眠三4 .oo.ox
		}
			
		else if (leftEdge > 2 && !line[leftEdge - 2] && !line[leftEdge - 1] && rightEdge < lineSize - 1 && !line[rightEdge + 2] && !line[rightEdge + 1])
			return _TWO; //活二1 ..oo..

		else return _S_TWO; //各种眠二

	case 0: // 只有一个棋子则向左匹配，否则容易重复
		if (leftEdge > 4 && line[leftEdge - 4] == nowClr && !line[leftEdge - 3] && line[leftEdge - 2] == nowClr && !line[leftEdge - 1]) {
			visLine[leftEdge - 4] = visLine[leftEdge - 2] = VISITED;
			return _S_THREE; //眠三5 o.o.o
		}
		
		else if (leftEdge > 3 && !line[leftEdge - 3] && line[leftEdge - 2] == nowClr && !line[leftEdge - 1] && rightEdge < lineSize && !line[rightEdge + 1] &&
			(leftEdge > 4 && !line[leftEdge - 4] || rightEdge - 1 && !line[rightEdge + 2])) {
			visLine[leftEdge - 2] = VISITED;
			return _TWO; //活二2 .o.o..
		}

		else if (leftEdge > 3 && line[leftEdge - 3] == nowClr && !line[leftEdge - 2] && !line[leftEdge - 1]) {
			visLine[leftEdge - 3] = VISITED;
			if (leftEdge > 4 && !line[leftEdge - 4] && rightEdge < lineSize && !line[rightEdge + 1])
				return _TWO; //活二3 .o..o.
			else
				return _S_TWO; //眠二 xo..o.
		}

		else {
			for (int nowPos = leftEdge; nowPos > leftEdge - 5 && nowPos > 0; nowPos--) {
				if (line[nowPos] == cvt_to_Rival_Clr(nowClr))
					break;
				if (line[nowPos] == nowClr) {
					visLine[nowPos] = VISITED;
					return _S_TWO; //眠二
				}	
			}
			return _ONE;
		}

	default:
		return _FIVE;
	}
}

int calcScore(int color)//估值算法，返回估值
{
	//统计棋型进行估值
	memset(vis, UNVISITED, sizeof(vis));
	memset(typeCounter, 0, sizeof(typeCounter));
	int temp_Line[GRID_NUM];
	for (int c = 1; c <= piecesCounter[color]; c++) {
		int i = chessPieces[color][c].x;
		int j = chessPieces[color][c].y;
		if (!vis[i][j][0]) {
			// 水平方向判断棋形
			for (int k = 1; k < GRID_NUM; k++)
				temp_Line[k] = chessBoard[i][k];

			int anaResult = analysisPoint(temp_Line, GRID_NUM - 1, j);
			typeCounter[anaResult]++;

			for (int k = 1; k < GRID_NUM; k++)
				vis[i][k][0] |= visLine[k];
		}
		if (!vis[i][j][1]) {
			// 竖直方向判断棋形
			for (int k = 1; k < GRID_NUM; k++)
				temp_Line[k] = chessBoard[k][j];

			int anaResult = analysisPoint(temp_Line, GRID_NUM - 1, i);
			typeCounter[anaResult]++;

			for (int k = 1; k < GRID_NUM; k++)
				vis[k][j][1] |= visLine[k];
		}
		if (!vis[i][j][2]) {
			// 左斜对角方向判断棋形
			int lineSize = 0;
			// 获得左斜对角线的区间
			int k_start = -GRID_NUM;
			int k_end = GRID_NUM;
			int nowPos;
			for (; k_start <= 0 && (i + k_start <= 0 || j + k_start <= 0); k_start++);
			for (; k_end >= 0 && (i + k_end >= GRID_NUM || j + k_end >= GRID_NUM); k_end--);
			lineSize = k_end - k_start + 1;
			for (int k = k_start, t = 1; k <= k_end; k++, t++) {
				if (!k) nowPos = t;
				temp_Line[t] = chessBoard[i + k][j + k];
			}

			int anaResult = analysisPoint(temp_Line, lineSize, nowPos);
			typeCounter[anaResult]++;

			for (int k = k_start, t = 1; k <= k_end; k++, t++)
				vis[i + k][j + k][2] |= visLine[t];
		}
		if (!vis[i][j][3]) {
			// 右斜对角方向判断棋形
			int lineSize = 0;
			// 获得右斜对角线的区间
			int k_start = -GRID_NUM;
			int k_end = GRID_NUM;
			int nowPos;
			for (; k_start <= 0 && (i + k_start <= 0 || j - k_start >= GRID_NUM); k_start++);
			for (; k_end >= 0 && (i + k_end >= GRID_NUM || j - k_end <= 0); k_end--);
			lineSize = k_end - k_start + 1;
			for (int k = k_start, t = 1; k <= k_end; k++, t++) {
				if (!k) nowPos = t;
				temp_Line[t] = chessBoard[i + k][j - k];
			}

			int anaResult = analysisPoint(temp_Line, lineSize, nowPos);
			typeCounter[anaResult]++;

			for (int k = k_start, t = 1; k <= k_end; k++, t++)
				vis[i + k][j - k][3] |= visLine[t];
		}
	}

	// 对统计结果进行加权算分
	if (typeCounter[_FIVE]) return 1000000;
	if (typeCounter[_FOUR] || typeCounter[_S_FOUR] > 1) return 100000;
	if (typeCounter[_S_FOUR] && typeCounter[_THREE]) return  90000;
	if (typeCounter[_THREE] > 1) return 50000;
	if (typeCounter[_THREE] && typeCounter[_S_THREE]) return 10000;
	if (typeCounter[_THREE]) return 5000;
	if (typeCounter[_S_FOUR]) return 1000;
	if (typeCounter[_TWO] > 1) return 500;
	if (typeCounter[_TWO]) return 100;
	if (typeCounter[_S_THREE]) return 50;
	if (typeCounter[_S_TWO]) return 20;
	if (typeCounter[_ONE]) return 10;
	return 0;
}

int evaluate(int color) {
	int myScore = calcScore(color); 
	int rivalScore = calcScore(cvt_to_Rival_Clr(color));
	for (int i = 1; i < GRID_NUM; i++)
		for (int j = 1; j < GRID_NUM; j++)
			if (chessBoard[i][j] == color)
				myScore += posValue[i][j];
			else if (chessBoard[i][j] == cvt_to_Rival_Clr(color))
				rivalScore += posValue[i][j];
	return myScore * OFFENSIVE_WEIGHT - rivalScore;
}