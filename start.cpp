#include "define.h"
#include "searchmove.h"
#include "printchessboard.h"
#include "makemove.h"

int main()
{
	cout << "*************��ӭ�����������˻�����ϵͳ*************" << endl;
	cout << "����: newblack  ��������" << endl;
	cout << "����: newwhite  ���Ժ���" << endl;
	cout << "����: move x y  ��ʾ���ӵ�" << endl; 
	print();
	char input[64];
	int errCounter = 0;
	int isStart = 0;

	while (~scanf("%s", input))
	{
		if (strcmp(input, "newblack") == 0)//��������
		{
			if (isStart) {
				puts("Artificial Idiot���ϸ磿���ѣ��Ѿ���ʼ�ˣ�");
				continue;
			}
			else isStart = 1;
			errCounter = 0;
			point newMove = getGoodMove(black);
			makeMove(newMove, black);
			print();
			puts("Artificial Idiot��������");
		}
		else if (strcmp(input, "newwhite") == 0)//���Ժ���
		{
			if (isStart) {
				puts("Artificial Idiot���ϸ磿���ѣ��Ѿ���ʼ�ˣ�");
				continue;
			}
			else isStart = 1;
			errCounter = 0;
		
			puts("Artificial Idiot�������¾������£�����Ϊ��������ͻ�Ӯ��");
			continue;
		}
		else if (input[0] == 'm')//�������
		{
			errCounter = 0;
			int input_x, input_y;
			scanf("%d%d", &input_x, &input_y);
			if (!inboard(input_x, input_y)) {
				puts("Artificial Idiot ������ȥ���䣡");
				continue;
			}
			if (makeMove(point(input_x, input_y), white) == -1) {
				puts("Artificial Idiot�������������Գ��Ӷ���");
				continue;
			}
			print();
			if (gameover(point(input_x, input_y))) {
				return puts("Artificial Idiot��woc6����wsl����"), 0;
			}
			point newMove = getGoodMove(black);
			makeMove(newMove, black);
			print();

			printf("%d\n", counter);
			counter = 0;

			printf("Move: %d, %d\n", newMove.x, newMove.y);
			if (gameover(newMove)) {
				return puts("Artificial Idiot����ϲ�㣡������������Ϊ-INF��"), 0;
			}
			puts("Artificial Idiot��������");
		}
		else
		{
			switch (++errCounter) {
			case 1:
				puts("Artificial Idiot���ж����㿴���������ʲô����");
				break;
			case 2:
				puts("Artificial Idiot: ��������Ҫ������xjb�������ֱ��Ӯ��");
				break;
			case 3:
				puts("Artificial Idiot: ����ҪӮ�˰�����");
				break;
			case 4:
				return puts("Artificial Idiot: �ã���Ӯ�ˣ����~"), 0;
				break;
			}
			continue;
		}
	}
}





/*
c���Ա���ԭ��
ͷ�ļ��÷�
#ifndef��#def��#endif�Ⱥ���÷�
http://www.51hei.com/bbs/dpj-54868-1.html
http://www.51hei.com/bbs/dpj-28952-1.html
http://www.51hei.com/bbs/dpj-46187-1.html

*/