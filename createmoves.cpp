#include "define.h"

point searchOrder[GRID_NUM * GRID_NUM];
int searchOrder_counter;

void initialize_for_CreateMoves() { // ����λ��Ȩֵ����з�˳��
	memset(searchOrder, 0, sizeof(searchOrder));
	searchOrder_counter = 0;
	for (int i = 1; i < GRID_NUM; i++)
		for (int j = 1; j < GRID_NUM; j++)
			if (!chessBoard[i][j])
			searchOrder[++searchOrder_counter] = point(i, j);
	
	sort(searchOrder + 1, searchOrder + searchOrder_counter + 1);
}

void createMoves(vector <point> &newMoves) { // �����з�����
	//�����ϵĿհ׵��Ϊ�����з�
	vector <point> ().swap(newMoves);
	for (int i = 1; i <= searchOrder_counter; i++)
		if (!chessBoard[searchOrder[i].x][searchOrder[i].y])
				newMoves.push_back(searchOrder[i]);
}