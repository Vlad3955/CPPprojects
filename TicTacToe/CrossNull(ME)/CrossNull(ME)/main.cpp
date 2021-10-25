#include <iostream>
#include <random>
#include <stdlib.h>
#include <chrono>
#include "Header.h"
using namespace std;



// ������������ �����(���������) ����
enum Cell : char// ����� ������� ��������� ��������� ���
{
	CROSS = 'X',
	ZERO = '0',
	EMPTY = '_'
};

// ��������� � ������������
struct Coord
{
	size_t y{ 0 };
	size_t x{ 0 };

};

// ������������ ��������� ����
enum GameProgress
{
	IN_PROGRESS,
	WON_HUMAN,
	WON_AI,
	DRAW
};

#pragma pack(push, 1)
struct  Game
{
	Cell** ppField = nullptr;// ��������� �� ��������� ����� ����
	const uint16_t SIZE = 5;// ���� 5�5 �����
	Cell human;// ��� ��� ������
	Cell ai;// --//--
	size_t turn = 0;// ����������� ����.������-�������, ��������-��
	GameProgress progress = IN_PROGRESS;
};
#pragma pack(pop)




int main()
{
	setlocale(LC_ALL, "ru");
	Game g;
	initGame(g);
	clearScr();
	drawGame(g);

	do
	{
		if (g.turn % 2 == 0)
		{
			// Human
			Coord c = getHumanCoord(g);
			g.ppField[c.y][c.x] = g.human;
		}
		else
		{
			// Comp
			Coord c = getAICoord(g);
			g.ppField[c.y][c.x] = g.ai;
		}

		clearScr();// ����� ������� ���� ������ ����� 
		drawGame(g);// ���������� ����������� ����
		g.turn++;// ����������� ����������� ���� �� 1

		g.progress = getWon(g);// ��� �������

	} while (g.progress == IN_PROGRESS);

	congrats(g);

	deinitGame(g);
	return 0;
}