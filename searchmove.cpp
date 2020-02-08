#include "define.h"
#include "createmoves.h"
#include "makemove.h"
#include "evaluate.h"
#include "hash.h"
#define MAX_DEPTH 4 // 必须是个偶数否则容易判断失误

vector <point> newMoves[256];
int historyValTable[GRID_NUM][GRID_NUM];
point goodMove;
int nowMaxDepth;

inline void initialize_for_HistoryTable() {
	memset(historyValTable, 10, sizeof(historyValTable));
}

inline int getHistoryVal(point pos) {
	return historyValTable[pos.x][pos.y];
}

inline void insertHistoryVal(point pos, int val) {
	historyValTable[pos.x][pos.y] += 2 << val;
}

bool gameover(point nowPos) {
	// 判断color是否已经胜利

	// 水平方向
	int leftEdge = nowPos.y;
	int rightEdge = nowPos.y;
	int color = chessBoard[nowPos.x][nowPos.y];
	for (; leftEdge > 0 && chessBoard[nowPos.x][leftEdge] == color; leftEdge--); leftEdge++;
	for (; rightEdge < GRID_NUM && chessBoard[nowPos.x][rightEdge] == color; rightEdge++); rightEdge--;
	if (rightEdge - leftEdge > 3) return 1;

	// 竖直方向
	leftEdge = nowPos.x;
	rightEdge = nowPos.x;
	for (; leftEdge > 0 && chessBoard[leftEdge][nowPos.y] == color; leftEdge--); leftEdge++;
	for (; rightEdge < GRID_NUM && chessBoard[rightEdge][nowPos.y] == color; rightEdge++); rightEdge--;
	if (rightEdge - leftEdge > 3) return 1;

	// 左斜对角线方向
	leftEdge = rightEdge = 0;
	for (; nowPos.x + leftEdge > 0 && nowPos.y + leftEdge > 0 && chessBoard[nowPos.x + leftEdge][nowPos.y + leftEdge] == color; leftEdge--); leftEdge++;
	for (; nowPos.x + rightEdge < GRID_NUM && nowPos.y + rightEdge < GRID_NUM && chessBoard[nowPos.x + rightEdge][nowPos.y + rightEdge] == color; rightEdge++); rightEdge--;
	if (rightEdge - leftEdge > 3) return 1;
	
	// 右斜对角线方向
	leftEdge = rightEdge = 0;
	for (; nowPos.x + leftEdge > 0 && nowPos.y - leftEdge < GRID_NUM && chessBoard[nowPos.x + leftEdge][nowPos.y - leftEdge] == color; leftEdge--); leftEdge++;
	for (; nowPos.x + rightEdge < GRID_NUM && nowPos.y - rightEdge > 0 && chessBoard[nowPos.x + rightEdge][nowPos.y - rightEdge] == color; rightEdge++); rightEdge--;
	if (rightEdge - leftEdge > 3) return 1;

	return 0;
}

int alphabeta(int depth, int alpha, int beta, int player)
{
	//搜索主体
	counter++;
	int val = searchHashTable(alpha, beta, depth, player);
  	if (val != NOT_FOUNDED) 
		return val;

	if (depth <= 0) {
		val = evaluate(player);
		insertHashTable(EXACT_VAL, val, depth, player);

		return val;
	}
		
	createMoves(newMoves[depth]);

	int newMoves_counter = newMoves[depth].size();
	// 获得一个搜索顺序
	for (int i = 0; i < newMoves_counter; i++)
		newMoves[depth][i].val = getHistoryVal(newMoves[depth][i]);
	sort(newMoves[depth].begin(), newMoves[depth].end());

	bool isExact = 0;
	int bestmove = -1;
	int a = alpha;
	int b = beta;
	
	for (int i = 0; i < newMoves_counter; i++) {

		makeMove(newMoves[depth][i], player);
		hash_makeMove(newMoves[depth][i], player);

		if (gameover(newMoves[depth][i])) {
			
			unMakeMove(newMoves[depth][i]);
			hash_unMakeMove(newMoves[depth][i], player);
			if (depth == nowMaxDepth)
				goodMove = newMoves[depth][i];
			return 1000000;
		}

		val = -alphabeta(depth - 1, -b, -a, cvt_to_Rival_Clr(player)); // pvs
		if (val > a && val < beta && i > 0) //failhigh
		{
			counter++;
			a = -alphabeta(depth - 1, -beta, -val, cvt_to_Rival_Clr(player));
			isExact = 1;
			bestmove = i;
			if (depth == nowMaxDepth)
				goodMove = newMoves[depth][i];
		}

		unMakeMove(newMoves[depth][i]);
		hash_unMakeMove(newMoves[depth][i], player);
		
		if (val > a) {
			isExact = 1;
			bestmove = i;
			a = val;
			if (depth == nowMaxDepth)
				goodMove = newMoves[depth][i];
		}
		if (a >= beta) {
			insertHistoryVal(newMoves[depth][i], depth);
			insertHashTable(LOWER_BOUND, a, depth, player);
			return a;
		}
		b = a + 1;
	}

	if (bestmove != -1)
		insertHistoryVal(newMoves[depth][bestmove], depth);

	if (isExact)
		insertHashTable(EXACT_VAL, a, depth, player);
	else
		insertHashTable(UPPER_BOUND, a, depth, player);

	return a;
}

point getGoodMove(int player) //得到招法，如果超时直接返回无效解。
{
	//这里是alphabeta的第一层
	

	initialize_for_Hash();
	initialize_for_CreateMoves();
	initialize_for_HistoryTable();
//	printf(" Me: x = %d, y = %d, value = %d \n", best_move.x, best_move.y, best_val);

	if(piecesCounter[1] + piecesCounter[2] > 2) nowMaxDepth = MAX_DEPTH;
	else nowMaxDepth = 3;

	alphabeta(nowMaxDepth, -inf, inf, player);
	return goodMove;
}