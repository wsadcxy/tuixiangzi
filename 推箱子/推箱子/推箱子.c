//0:空的;1:▊;3:☆;4:★;5:※;7:⊙;8:※
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define X 8
#define Y 8
/*
  1.先想，再了解
  2
	2.1：地图是贯穿整个游戏；全局数组
	2.2:游戏的划分，模块的划分：一个功能使用一个模块
		功能与功能尽量不要交叉
	2.3：函数设计
		2.3.1：函数的返回值--函数唯一的遗留物。
				 eg：判断胜负，最终结果--游戏结束（1）或游戏继续（0）。
		2.3.2：函数的参数
			   1.要操作的数据，但是不想改变数据
			   2.说明函数要操作的对象
  3.优化
*/
int map[X][Y] = {
	//0:空的   1:▊(墙)  
	//3:☆\4:★ (目的地和箱子)   
	//5:※(人) 
	//7:⊙(目的地(3)和箱子(4)在一起) 
	//8:※(目(4)的地和人(5)在一起)
	//满足多种情况
	0,0,0,1,1,1,0,0,
	0,0,0,1,3,1,0,0,
	1,1,1,1,4,1,0,0,
	1,3,0,4,5,1,1,1,
	1,1,1,1,0,4,3,1,
	0,0,1,1,1,1,1,1,
	

};
void drawmap();
void keyDown();
int gameover();
int main()
{
	while (1)
	{
		drawmap();
		if (gameover() == 3)
			break;
		keyDown();
		system("cls");
		//system("pause");
	}
	printf("恭喜过关！");
	//printf("0:空的;1:▊;3:☆;4:★;5:※;7:⊙;8:※");
	system("pause");
}
//地图绘制
void drawmap()
{
	//3:☆\4:★ (目的地和箱子)   
	//5:※(人) 
	//7:⊙(目的地(3)和箱子(4)在一起) 
	//8:※(目(4)的地和人(5)在一起)
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			switch (map[i][j])
			{
				//0:空的   1:▊(墙)
			case 0:
				printf("  "); break;
			case 1:
				printf("▊"); break;
			case 3:
				printf("☆"); break;
			case 4:
				printf("★"); break;
			case 7:
				printf("⊙"); break;
			case 5:
			case 8:
				printf("※"); break;
			}
		}
		printf("\n");

	}
}
//按键处理
void keyDown()
{
	int i, j;
	//分析按键过程
	//定位人在哪
	//人有两种情况：人，人和目的地一起
	for (i = 0; i < X; i++)
	{
		for (j = 0; j < Y; j++)
		{
			if (map[i][j] == 5 || map[i][j] == 8)
				break;
		}
		if (map[i][j] == 5 || map[i][j] == 8)
			break;
	}
	char ch;
	ch = _getch();
	switch (ch)
	{
		//72,80,75,77(键码)
	case 'w':
	case 'W':
	case 72:
		if (map[i - 1][j] == 0 || map[i - 1][j] == 3)
		{
			//新地方map[i-1][j]人来了
			map[i - 1][j] += 5;
			//老地方map[i][j]人走了
			map[i][j] -= 5;
		}
		//如果下一个地方是箱子，进一步判断能否走
		//注意点：箱子的两种状态--箱子 、箱子与目的地在一起
		else if (map[i - 1][j] == 4 || map[i - 1][j] == 7)
		{
			//做箱子的下一步判断能否走
			if (map[i - 2][j] == 0 || map[i - 2][j] == 3)
			{//箱子来了
				map[i - 2][j] += 4;
				//箱子位置：箱子走了，人来了；
				map[i - 1][j]++;
				//原来地方
				map[i][j] -= 5;
			}
		}
		break;
	case 's':
	case 'S':
	case 80:
		if (map[i + 1][j] == 0 || map[i + 1][j] == 3)
		{
			//新地方map[i-1][j]人来了
			map[i + 1][j] += 5;
			//老地方map[i][j]人走了
			map[i][j] -= 5;
		}
		else if (map[i - 1][j] == 4 || map[i - 1][j] == 7)
		{
			//做箱子的下一步判断能否走
			if (map[i + 2][j] == 0 || map[i + 2][j] == 3)
			{//箱子来了
				map[i + 2][j] += 4;
				//箱子位置：箱子走了，人来了；
				map[i + 1][j]++;
				//原来地方
				map[i][j] -= 5;
			}
		}
		break;
	case 'a':
	case 'A':
	case 75:
		if (map[i][j - 1] == 0 || map[i][j - 1] == 3)
		{
			//新地方map[i][j-1]人来了
			map[i][j - 1] += 5;
			//老地方map[i][j]人走了
			map[i][j] -= 5;
		}
		else if (map[i][j - 1] == 4 || map[i][j - 1] == 7)
		{
			//做箱子的下一步判断能否走
			if (map[i][j - 2] == 0 || map[i][j - 2] == 3)
			{
				//箱子来了
				map[i][j - 2] += 4;
				//箱子位置：箱子走了，人来了；
				map[i][j - 1]++;
				//原来地方
				map[i][j] -= 5;
			}
			break;
	case 'd':
	case 'D':
	case 77:
		if (map[i][j + 1] == 0 || map[i][j + 1] == 3)
		{
			//新地方map[i][j+1]人来了
			map[i][j + 1] += 5;
			//老地方map[i][j]人走了
			map[i][j] -= 5;
		}
		else if (map[i][j + 1] == 4 || map[i][j + 1] == 7)
		{
			//做箱子的下一步判断能否走
			if (map[i][j + 2] == 0 || map[i][j + 2] == 3)
			{
				//箱子来了
				map[i][j + 2] += 4;
				//箱子位置：箱子走了，人来了；
				map[i][j + 1]++;
				//原来地方
				map[i][j] -= 5;
			}
		}
		break;
		}
	}
}
//胜负判断
int gameover()
{
	int cnt = 0;
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			if (map[i][j] == 7)
				cnt++;
		}
	}
	return cnt;
}
