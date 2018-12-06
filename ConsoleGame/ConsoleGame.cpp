// ConsoleGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <time.h>
const int WIDTH = 80;
const int HEIGHT = 20; 


/*Функция создает буфер (буфер создается с дополнительными элементом - концом строки)*/
char **createBuffer() {
	char **buffer = new char*[HEIGHT];
	for (int i = 0; i < HEIGHT;i++) {
		buffer[i] = new char[WIDTH+1];
		buffer[i][WIDTH] = '\0';
	}
	return buffer;
}
/*Функция заполняет буфер заданными символами*/
void initBackground(char **buffer) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			buffer[i][j] = '*';
		}
	}
}
/*Функция отрисоывает на экран буфер*/
void drawBuffer(char **buffer) {
	for (int i = 0; i < HEIGHT; i++) {
		printf("%s\n", buffer[i]);
	}
}
/*Функция возвращает true, если клавиша key нажата*/
bool isDown(char key) {
	return GetKeyState(key) & 0x8000;
}

/*Функция в которой должна находится логика игры*/
void gameFunctionn(char **buffer) {
	//Ссылка с кодами клавиш
	//https://docs.microsoft.com/ru-ru/windows/desktop/inputdev/virtual-key-codes

	if (isDown(VK_SPACE))
	{
		buffer[0][0] = ' ';
	}
	if (isDown('A'))
	{
		buffer[1][0] = 'A';
	}
	if (isDown('W'))
	{
		buffer[0][1] = 'W';
	}
	if (isDown('S'))
	{
		buffer[1][1] = 'S';
	}
	if (isDown('D'))
	{
		buffer[1][2] = 'D';
	}
}
/*Основной цикл игры*/
void mainCycle(char **buffer) {
	while (true)
	{
		if (isDown('Q'))
		{
			break;
		}
		system("cls");
		initBackground(buffer);
		gameFunctionn(buffer);
		drawBuffer(buffer);
		Sleep(20);
	}
}
/*Точка входа (Главная функция программы - запускается первой)*/
int main()
{
	char **buffer = createBuffer();
	printf("For exit from program Enter Q\n");
	system("pause");
	mainCycle(buffer);
	system("pause");
    return 0;
}

