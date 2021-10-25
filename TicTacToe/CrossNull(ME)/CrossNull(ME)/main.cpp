#include <iostream>
#include <random>
#include <stdlib.h>
#include <chrono>
#include "Header.h"
using namespace std;



// Перечисление ячеек(элементов) поля
enum Cell : char// Таким образом обЪявляем чаровский тип
{
	CROSS = 'X',
	ZERO = '0',
	EMPTY = '_'
};

// Структура с координатами
struct Coord
{
	size_t y{ 0 };
	size_t x{ 0 };

};

// Перечисление состояний игры
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
	Cell** ppField = nullptr;// указатель на указатель ячеек поля
	const uint16_t SIZE = 5;// Поле 5х5 будет
	Cell human;// Кто чем играет
	Cell ai;// --//--
	size_t turn = 0;// определение хода.Четный-человек, нечетный-ИИ
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

		clearScr();// после каждого хода чистим экран 
		drawGame(g);// отображаем обновленное поле
		g.turn++;// увеличиваем очередность хода на 1

		g.progress = getWon(g);// кто победил

	} while (g.progress == IN_PROGRESS);

	congrats(g);

	deinitGame(g);
	return 0;
}