#include "define.h"

point searchOrder[GRID_NUM * GRID_NUM];
int searchOrder_counter;

void initialize_for_CreateMoves() { // 根据位置权值获得招法顺序
	memset(searchOrder, 0, sizeof(searchOrder));
	searchOrder_counter = 0;
	for (int i = 1; i < GRID_NUM; i++)
		for (int j = 1; j < GRID_NUM; j++)
			if (!chessBoard[i][j])
			searchOrder[++searchOrder_counter] = point(i, j);
	
	sort(searchOrder + 1, searchOrder + searchOrder_counter + 1);
}

void createMoves(vector <point> &newMoves) { // 生成招法代码
	//棋盘上的空白点均为可行招法
	vector <point> ().swap(newMoves);
	for (int i = 1; i <= searchOrder_counter; i++)
		if (!chessBoard[searchOrder[i].x][searchOrder[i].y])
				newMoves.push_back(searchOrder[i]);
}