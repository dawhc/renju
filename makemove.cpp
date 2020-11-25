#include "define.h"

int makeMove(struct point node, int color)
{
	//落子
	if (chessBoard[node.x][node.y]) return -1;
	chessBoard[node.x][node.y] = color;
	chessPieces[color][++piecesCounter[color]] = node;
	return 0;
}

int unMakeMove(struct point node)
{
	//撤销落子
	if (!chessBoard[node.x][node.y]) return -1;
	piecesCounter[chessBoard[node.x][node.y]]--;
	chessBoard[node.x][node.y] = blank;
	return 0;
}
