#include "define.h"

int makeMove(struct point node, int color)
{
	//Âä×Ó
	if (chessBoard[node.x][node.y]) return -1;
	chessBoard[node.x][node.y] = color;
	chessPieces[color][++piecesCounter[color]] = node;
	return 0;
}

int unMakeMove(struct point node)
{
	//³·ÏúÂä×Ó
	if (!chessBoard[node.x][node.y]) return -1;
	piecesCounter[chessBoard[node.x][node.y]]--;
	chessBoard[node.x][node.y] = blank;
	return 0;
}
