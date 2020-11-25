#include "define.h"
#include "searchmove.h"
#include "printchessboard.h"
#include "makemove.h"

int main()
{
	cout << "*************欢迎来到五子棋人机对弈系统*************" << endl;
	cout << "输入: newblack  电脑先手" << endl;
	cout << "输入: newwhite  电脑后手" << endl;
	cout << "输入: move x y  表示落子点" << endl; 
	print();
	char input[64];
	int errCounter = 0;
	int isStart = 0;

	while (~scanf("%s", input))
	{
		if (strcmp(input, "newblack") == 0)//电脑先手
		{
			if (isStart) {
				puts("Artificial Idiot：老哥？醒醒！已经开始了！");
				continue;
			}
			else isStart = 1;
			errCounter = 0;
			point newMove = getGoodMove(black);
			makeMove(newMove, black);
			print();
			puts("Artificial Idiot：该你辣");
		}
		else if (strcmp(input, "newwhite") == 0)//电脑后手
		{
			if (isStart) {
				puts("Artificial Idiot：老哥？醒醒！已经开始了！");
				continue;
			}
			else isStart = 1;
			errCounter = 0;
		
			puts("Artificial Idiot：你先下就你先下，你以为你先下你就会赢？");
			continue;
		}
		else if (input[0] == 'm')//玩家落子
		{
			errCounter = 0;
			int input_x, input_y;
			scanf("%d%d", &input_x, &input_y);
			if (!inboard(input_x, input_y)) {
				puts("Artificial Idiot ：滚回去重输！");
				continue;
			}
			if (makeMove(point(input_x, input_y), white) == -1) {
				puts("Artificial Idiot：你家五子棋可以吃子儿？");
				continue;
			}
			print();
			if (gameover(point(input_x, input_y))) {
				return puts("Artificial Idiot：woc6啊！wsl……"), 0;
			}
			point newMove = getGoodMove(black);
			makeMove(newMove, black);
			print();

			printf("%d\n", counter);
			counter = 0;

			printf("Move: %d, %d\n", newMove.x, newMove.y);
			if (gameover(newMove)) {
				return puts("Artificial Idiot：恭喜你！经检测你的智商为-INF！"), 0;
			}
			puts("Artificial Idiot：该你辣");
		}
		else
		{
			switch (++errCounter) {
			case 1:
				puts("Artificial Idiot：有毒？你看看你输入的什么玩意");
				break;
			case 2:
				puts("Artificial Idiot: ？？？你要再这样xjb输就算我直接赢了");
				break;
			case 3:
				puts("Artificial Idiot: 我真要赢了啊……");
				break;
			case 4:
				return puts("Artificial Idiot: 好！我赢了！告辞~"), 0;
				break;
			}
			continue;
		}
	}
}





/*
c语言编译原理
头文件用法
#ifndef、#def、#endif等宏的用法
http://www.51hei.com/bbs/dpj-54868-1.html
http://www.51hei.com/bbs/dpj-28952-1.html
http://www.51hei.com/bbs/dpj-46187-1.html

*/