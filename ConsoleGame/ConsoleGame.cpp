// ConsoleGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <map>
using namespace std;

const int MAP_HEIGHT = 5;
const int MAP_WIDTH = 30;

// Карта игрового поля
const BYTE MAP_OF_GAME[MAP_HEIGHT][MAP_WIDTH] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0,},
	{0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1,},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,},
};

map<BYTE, char> mappingOfObjects = {
	{0, ' '},
	{1, '#'},
};

const int HEIGHT = MAP_HEIGHT;
const int WIDTH = MAP_HEIGHT;

struct Player
{
	int x;
	int y;
};


/*Функция создает буфер (буфер создается с дополнительным элементом - концом строки)*/
char** createBuffer()
{
	char** buffer = new char*[HEIGHT];
	for (int i = 0; i < HEIGHT; i++)
	{
		buffer[i] = new char[WIDTH + 1];
		buffer[i][WIDTH] = '\0';
	}
	return buffer;
}


Player* createPlayer()
{
	Player* player = new Player;
	player->x = 0;
	player->y = 0;
	return player;
}

/* Функция возвращает вид ячейки по координате,
   относительно показываемого окна
*/
int getValueOfMap(char** buffer, Player* player, int x, int y)
{
	return MAP_OF_GAME[y][player->x + x];
}

void drawMap(char** buffer, Player* player)
{
	for (int j = 0; j < WIDTH; j++)
	{
		for (int i = 0; i < HEIGHT; i++)
		{
			buffer[i][j] = mappingOfObjects[getValueOfMap(buffer, player, j, i)];
		}
	}
}

void drawPlayer(char** buffer, Player* player)
{
	buffer[player->y][0] = '$';
}


/*Функция возвращает true, если клавиша key нажата*/
bool isDown(char key)
{
	return GetKeyState(key) & 0x8000;
}

bool isBlockOnLeft(char** buffer, Player* player)
{
	return MAP_OF_GAME[player->y][player->x - 1] == 1;
}

bool isBlockOnRight(char** buffer, Player* player)
{
	return MAP_OF_GAME[player->y][player->x + 1] == 1;
}

bool isBlockOnTop(char** buffer, Player* player)
{
	return MAP_OF_GAME[player->y - 1][player->x] == 1;
}

bool isBlockOnBottom(char** buffer, Player* player)
{
	return MAP_OF_GAME[player->y + 1][player->x] == 1;
}


/*Функция отображает содержания буфера на экран*/
void show(char** buffer, Player* player)
{
	system("cls");
	for (int i = 0; i < HEIGHT; i++)
	{
		printf("%s\n", buffer[i]);
	}

	// вывод дополнительнаой информации
	printf("x:%d\ny:%d\n", player->x, player->y);

	printf("\n");
	printf(" W:%d\n", !isBlockOnTop(buffer, player));
	printf("A:%d D:%d\n", !isBlockOnLeft(buffer, player), !isBlockOnRight(buffer, player));
	printf(" S:%d\n", !isBlockOnBottom(buffer, player));


	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (i == player->y && j == player->x)
			{
				printf("$");
			}
			else
			{
				printf("%c", mappingOfObjects[MAP_OF_GAME[i][j]]);
			}
		}
		printf("\n");
	}
}

/*Функция в которой находится логика игры*/
void gameFunctionn(char** buffer, Player* player)
{
	//Ссылка с кодами клавиш
	//https://docs.microsoft.com/ru-ru/windows/desktop/inputdev/virtual-key-codes

	if (isDown(VK_SPACE))
	{
	}
	if (isDown('A'))
	{
		if (
			player->x > 0
			&& !isBlockOnLeft(buffer, player)
		)
		{
			player->x--;
		}
	}
	if (isDown('W'))
	{
		if (
			player->y > 0
			&& !isBlockOnTop(buffer, player)
		)
		{
			player->y--;
		}
	}
	if (isDown('S'))
	{
		if (
			player->y < MAP_HEIGHT - 1
			&& !isBlockOnBottom(buffer, player)
		)
		{
			player->y++;
		}
	}
	if (isDown('D'))
	{
		if (
			player->x < MAP_WIDTH - 1
			&& !isBlockOnRight(buffer, player)
		)
		{
			player->x++;
		}
	}
}

/*Функция рисования в буфере*/
void draw(char** buffer, Player* player)
{
	drawMap(buffer, player);
	drawPlayer(buffer, player);
}

/*Основной цикл игры*/
void mainCycle(char** buffer, Player* player)
{
	while (true)
	{
		if (isDown('Q'))
		{
			break;
		}
		draw(buffer, player);
		gameFunctionn(buffer, player);
		show(buffer, player);
		Sleep(50);
	}
}


/*Точка входа (Главная функция программы - запускается первой)*/
int main()
{
	char** buffer = createBuffer();
	Player* player = createPlayer();
	printf("For exit from program Enter Q\n");
	system("pause");
	mainCycle(buffer, player);
	system("pause");
	return 0;
}