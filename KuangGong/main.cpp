#include <graphics.h>
#include <stdio.h>
#include <string>
#include <ctime>
#include <conio.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 480
void FoodLocetion();

/*

			Tab键	吃豆子自杀
			空格键	撞墙自杀
*/
bool Open_EalFood_Take = 0;			//ok




int Score = 0;
/*方向枚举*/
enum Face
{
	Up = 72,
	Down = 80,
	Left = 75,
	Right = 77
};
/*蛇结构体*/
struct Snake
{
	int x, y;
};
/*食物结构体*/
struct Food
{
	int x, y;
	bool exist;
};
/*蛇的方向*/
Face face;
/*蛇当前的结束*/
int n;
/*实例蛇*/
struct Snake snake[100];
/*食物*/
Food food;
/*游戏初始化*/
void GameInit()
{
	/*坐标初始化*/
	snake[0].x = 0;
	snake[0].y = 0;
	n = 3;
	/*设置方向*/
	face = Right;
	/*食物位置*/
	FoodLocetion();
}
/*画蛇*/
void DrawSnake()
{
	cleardevice();
	for (int i = 0; i < n; i++)
	{
		fillrectangle(snake[i].x, snake[i].y, snake[i].x + 15, snake[i].y + 15);
	}
}
/*外挂开关-吃死自己*/
void switch_Open_EalFood_Take()
{
	if (Open_EalFood_Take)
	{
		Open_EalFood_Take = 0;
	}
	else
	{
		Open_EalFood_Take = 1;
	}
}
/*捕获按键并设置方向*/
void KeyDown_SetFace()
{

	int Key = _getch();
	switch (Key)
	{
	case 9:
		/*外挂开关-吃死自己*/
		switch_Open_EalFood_Take();
		break;
	case Up:
		if (face != Down)
		{
			face = Up;
		}
		break;
	case Down:
		if (face != Up)
		{
			face = Down;
		}
		break;
	case Left:
		if (face != Right)
		{
			face = Left;
		}
		break;
	case Right:
		if (face != Left)
		{
			face = Right;
		}
		break;
	default:
		break;
	}
}
/*蛇移动*/
void SnackMove()
{
	for (int i = n; i > 0; i--)
	{
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}
	switch (face)
	{
	case Up:
		snake[0].y -= 15;
		break;
	case Down:
		snake[0].y += 15;
		break;
	case Left:
		snake[0].x -= 15;
		break;
	case Right:
		snake[0].x += 15;
		break;
	default:
		break;
	}
}
/*食物位置*/
void FoodLocetion()
{
	srand(unsigned int(time(NULL)));
	food.x = rand() % 800 + 1;
	food.y = rand() % 480 + 1;
	food.exist = true;
}
/*画食物*/
void DrawFood()
{
	fillcircle(food.x,food.y,10);
}
/*食物被吃掉*/
void is_Food()
{
	if (!food.exist)
	{
		FoodLocetion();
	}
}
/*是否吃到食物*/
void is_Eatshit()
{
	if (snake[0].x + 15 >= food.x && snake[0].x <= food.x + 10)
	{
		if (snake[0].y + 15 >= food.y && snake[0].y <= food.y + 10)
		{
			if (Open_EalFood_Take)
			{
				closegraph();
				MessageBox(NULL,"毒o(*￣▽￣*)o","你输了",NULL);
			}
			else
			{
				Score++;
				food.exist = false;
				n++;
			}
		}
	}
	//if(snake[0].x + 15)
}
/*打印分数*/
void outScore()
{
	TCHAR bus[20] = TEXT("");
	wsprintf(bus, _T("Number: %d"), Score);
	outtextxy(0, 0, bus);
}
int main()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	GameInit();
	while (1)
	{
		while (!_kbhit())
		{
			/*蛇移动*/
			SnackMove();
			/*画蛇*/
			DrawSnake();
			/*画食物*/
			DrawFood();
			/*是否吃到食物*/
			is_Eatshit();
			/*食物如果被吃掉重画*/
			is_Food();
			/*解决自动转型char的整数打印分数*/
			outScore();
			Sleep(100);
		}
		KeyDown_SetFace();
	}
	getchar();
	return 0;
}