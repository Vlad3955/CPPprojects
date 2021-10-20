#include <iostream>
#include <random>
#include <stdlib.h>
#include <chrono>

using namespace std;

//===============================================================================
// ==============================================================================


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
	int32_t y{ 0 };
	int32_t x{ 0 };

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
	const uint16_t SIZE = 3;// Поле 3х3 будет
	Cell human;// Кто чем играет
	Cell ai;// --//--
	size_t turn = 0;// определение хода.Четный-человек, нечетный-ИИ
	GameProgress progress = IN_PROGRESS;
};
#pragma pack(pop)

//===============================================================================
//===============================================================================




// Очистка экрана
void clearScr()
{
	system("cls");
}

// C++ный сложный генератор чисел
int32_t __fastcall getRundomNum(int32_t min, int32_t max)
{
	const static auto seed = chrono::system_clock::now().time_since_epoch().count();
	static mt19937_64 generator(seed);
	uniform_int_distribution<int32_t> dis(min, max);
	return dis(generator);
}


//================================================================================
//================================================================================

void __fastcall initGame(Game& g)
{
	g.ppField = new Cell * [g.SIZE];
	for (size_t i = 0; i < g.SIZE; i++)// инициализируем строки  матрицы
	{
		g.ppField[i] = new Cell[g.SIZE];
	}

	for (size_t y = 0; y < g.SIZE; y++)
	{
		for (size_t x = 0; x < g.SIZE; x++)
		{
			g.ppField[y][x] = EMPTY;
		}
	}

	if (getRundomNum(0, 1000) > 500)
	{
		g.human = CROSS;
		g.ai = ZERO;
		g.turn = 0;
	}
	else
	{
		g.human = ZERO;
		g.ai = CROSS;
		g.turn = 1;
	}
}


void __fastcall deinitGame(Game& g)
{
	for (size_t i = 0; i < g.SIZE; i++)// удаляем строки матрицы
	{
		delete[] g.ppField[i];
	}
	delete[] g.ppField;
	g.ppField = nullptr;
		
}

// Рисуем поле игры
void __fastcall drawGame(const Game &g)
{
	// верхние и верхний боковой отступы,нумерация по Х
	cout << endl << "     ";
	for (size_t x = 0; x < g.SIZE; x++)
	{
		cout << x + 1 << "   ";
	}
	cout << endl;
	
	// само поле
	for (size_t y = 0; y < g.SIZE; y++)
	{
		cout << " " << y + 1 << " | ";
		for (size_t x = 0; x < g.SIZE; x++)
		{
			cout << g.ppField[y][x] << " | ";
		}
		cout << endl;
	}
	cout << endl << "Челик: " << g.human << endl << "Ботик: " << g.ai << endl;
}

GameProgress __fastcall getWon(const Game& g)
{
	return IN_PROGRESS;
}


Coord __fastcall getHumanCoord(const Game& g)
{
	Coord c;
	do
	{
		cout << "Enter X (1..3): ";
		cin >> c.x;
		cout << "Enter y (1..3): ";
		cin >> c.x;
		c.x--;
		c.y--;
	} while (c.x > 2 || c.y > 2 || g.ppField[c.y][c.x] != EMPTY);

	return c;
}

Coord __fastcall getAICoord(const Game& g)
{

}


//================================================================================
//================================================================================

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
			Coord c = getHumanCoord(g);
			g.ppField[c.y][c.x] = g.human;
		}
		else
		{
			Coord c = getAICoord(g);
			g.ppField[c.y][c.x] = g.ai;
		}

		clearScr();// после каждого хода чистим экран 
		drawGame(g);// отображаем обновленное поле
		g.turn++;// увеличиваем очередность хода на 1

		g.progress = getWon(g);// кто победил

	} while (g.progress = IN_PROGRESS);

	deinitGame(g);
	return 0;
}