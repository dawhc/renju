#include "define.h"

void judge(int i, int j)
{
	if (i == 1 && j == 1)
		printf("�X");
	else if (i == 1 && j == 15) {
		if (!chessBoard[i][j - 1]) printf(" ");
		printf("�[");
	}
	else if (i == 15 && j == 1)
		printf("�^");
	else if (i == 15 && j == 15) {
		if (!chessBoard[i][j - 1]) printf(" ");
		printf("�a");
	}
	else if (i == 1 && j != 15 && j != 1) {
		if (!chessBoard[i][j - 1]) printf(" ");
		printf("��");
	}
	else if (i == 15 && j != 15 && j != 1) {
		if (!chessBoard[i][j - 1]) printf(" ");
		printf("��");
	}
	else if (j == 1 && i != 15 && i != 1)
		printf("��");
	else if (j == 15 && i != 15 && i != 1) {
		if (!chessBoard[i][j - 1]) printf(" ");
		printf("��");
	}
		
	else {
		if (!chessBoard[i][j - 1]) printf(" ");
		printf("��");
	}
		
}

void print()
{
	for (int i = 0; i < 16; i++)
	{
		if (i == 0)
		{
			printf("  ");
			for (int j = 1; j < 16; j++)
				printf("%-2d",j);
			printf("\n");
			continue;
		}
		for (int j = 0; j < 16; j++)
		{
			if (j == 0)
			{
				printf("%2d", i);
				continue;
			}

			if (chessBoard[i][j] == 1) {
				if (j != 1 && !chessBoard[i][j - 1]) printf(" ");
				printf("��");
			}
				
			else if (chessBoard[i][j] == 2) {
				if (j != 1 && !chessBoard[i][j - 1]) printf(" ");
				printf("��");
			}
			else
				judge(i, j);
		}
		printf("\n");
	}
}