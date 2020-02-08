#ifndef _HASH_
#define _HASH_

#define NOT_FOUNDED 0x7fffffff
#define HASHTABLE_SIZE 1024 * 1024 // Must be 2^n
#define EXACT_VAL 0
#define UPPER_BOUND 1
#define LOWER_BOUND 2

extern int nowHashKey32;
extern __int64 nowHashKey64;

struct hashItem {
	__int64 checkNum;
	int depth;
	int type;
	int val;
};

inline __int64 getRand64();
inline int getRand32();

void initialize_for_Hash();
void hash_makeMove(point, int);
void hash_unMakeMove(point, int);

int searchHashTable(int alpha, int beta, int depth, int color);
void insertHashTable(int type, int val, int depth, int color);

#endif