#include "define.h"
#include "hash.h"

hashItem hashTable[3][HASHTABLE_SIZE];
int hashKey32[3][GRID_NUM][GRID_NUM];
__int64 hashKey64[3][GRID_NUM][GRID_NUM];

int nowHashKey32;
__int64 nowHashKey64;

__int64 getRand64() {
	return rand() ^ ((__int64)rand() << 15) ^ ((__int64)rand() << 30) ^
		((__int64)rand() << 45) ^ ((__int64)rand() << 60);
}

int getRand32() {
	return rand() ^ ((long)rand() << 15) ^ ((long)rand() << 30);
}

void initialize_for_Hash() {
	srand((unsigned __int64)time(0));

	for (int i = 0; i < 3; i++)
		for (int j = 1; j < GRID_NUM; j++)
			for (int k = 1; k < GRID_NUM; k++) {
				hashKey32[i][j][k] = getRand32();
				hashKey64[i][j][k] = getRand64();
			}
	
	nowHashKey32 = 0;
	nowHashKey64 = 0ll;
	
	for (int i = 1; i < GRID_NUM; i++)
		for (int j = 1; j < GRID_NUM; j++)
			if (chessBoard[i][j]) {
				int nowClr = chessBoard[i][j];
				nowHashKey32 ^= hashKey32[nowClr][i][j];
				nowHashKey64 ^= hashKey64[nowClr][i][j];
			}
}

void hash_makeMove(point nowPos, int color) {
	nowHashKey32 ^= hashKey32[color][nowPos.x][nowPos.y];
	nowHashKey64 ^= hashKey64[color][nowPos.x][nowPos.y];
}

void hash_unMakeMove(point nowPos, int color) {
	hash_makeMove(nowPos, color);
}

int searchHashTable(int alpha, int beta, int depth, int color) {

	int pos = nowHashKey32 & (HASHTABLE_SIZE - 1);

	hashItem &nowHashTable = hashTable[color][pos];

	if (nowHashTable.checkNum == nowHashKey64 && nowHashTable.depth >= depth) {
		switch (nowHashTable.type) {
		case EXACT_VAL:
			return nowHashTable.val;

		case LOWER_BOUND:
			if (nowHashTable.val >= beta)
				return nowHashTable.val;
			break;

		case UPPER_BOUND:
			if (nowHashTable.val <= alpha)
				return nowHashTable.val;
		}
	}

	return NOT_FOUNDED;
}
void insertHashTable(int type, int val, int depth, int color) {

	int pos = nowHashKey32 & (HASHTABLE_SIZE - 1);
	
	hashItem &nowHashTable = hashTable[color][pos];
	nowHashTable.checkNum = nowHashKey64;
	nowHashTable.depth = depth;
	nowHashTable.val = val;
	nowHashTable.type = type;
}