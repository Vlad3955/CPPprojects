#include "Header.h"




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
	//////////////////////////////////////////////////////////////////////////////////////////
	// Сделал один вложеный цикл с объявлением и инициализацией,вместо двух отдельных 
	g.ppField = new Cell * [g.SIZE];
	for (size_t y = 0; y < g.SIZE; y++)// создаем строки  матрицы
	{
		g.ppField[y] = new Cell[g.SIZE];// создаем колонки  матрицы
		for (size_t x = 0; x < g.SIZE; x++)
		{
			g.ppField[y][x] = EMPTY;// инициализируем строки и колонки матрицы
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////

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
	for (size_t i = 0; i < g.SIZE; i++)
	{
		delete[] g.ppField[i];// удаляем строки и клонки матрицы
	}
	delete[] g.ppField;// чистим память
	g.ppField = nullptr;// зануляем указатель

}

// Рисуем поле игры
void __fastcall drawGame(const Game& g)
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
	cout << endl << "Человек: " << g.human << endl << "Бот: " << g.ai << endl;
}

// Кто выиграл
GameProgress __fastcall getWon(const Game& g)
{
	// Проверяем поле по строкам(Y) 
	for (size_t y = 0; y < g.SIZE; y++)
	{
		if (g.ppField[y][0] == g.ppField[y][1] && g.ppField[y][0] == g.ppField[y][2] && g.ppField[y][0] == g.ppField[y][3] && g.ppField[y][0] == g.ppField[y][4])
		{
			if (g.ppField[y][0] == g.human)
			{
				return WON_HUMAN;
			}

			if (g.ppField[y][0] == g.ai)
			{
				return WON_AI;
			}
		}
	}

	// Проверяем поле по столбцам(X)
	for (size_t x = 0; x < g.SIZE; x++)
	{
		if (g.ppField[0][x] == g.ppField[1][x] && g.ppField[0][x] == g.ppField[2][x] && g.ppField[0][x] == g.ppField[3][x] && g.ppField[0][x] == g.ppField[4][x])
		{
			if (g.ppField[0][x] == g.human)
			{
				return WON_HUMAN;
			}

			if (g.ppField[0][x] == g.ai)
			{
				return WON_AI;
			}
		}
	}

	// 1ая диагональ
	if (g.ppField[0][0] == g.ppField[1][1] && g.ppField[0][0] == g.ppField[2][2] && g.ppField[0][0] == g.ppField[3][3] && g.ppField[0][0] == g.ppField[4][4])
	{
		if (g.ppField[2][2] == g.human)
		{
			return WON_HUMAN;
		}

		if (g.ppField[2][2] == g.ai)
		{
			return WON_AI;
		}
	}

	// 2ая диагональ
	if (g.ppField[0][4] == g.ppField[1][3] && g.ppField[0][4] == g.ppField[2][2] && g.ppField[0][4] == g.ppField[3][1] && g.ppField[0][4] == g.ppField[4][0])
	{
		if (g.ppField[2][2] == g.human)
		{
			return WON_HUMAN;
		}

		if (g.ppField[2][2] == g.ai)
		{
			return WON_AI;
		}
	}

	// Проверка на ничью
	bool draw = true;
	for (size_t y = 0; y < g.SIZE; y++)
	{
		for (size_t x = 0; x < g.SIZE; x++)
		{
			if (g.ppField[y][x] == EMPTY)
			{
				draw = false;
				break;
			}
		}
		if (!draw)
		{
			break;
		}
	}

	if (draw)
	{
		return DRAW;
	}
	return IN_PROGRESS;
}


Coord __fastcall getHumanCoord(const Game& g)
{
	Coord c;
	do
	{
		cout << "Enter X (1..5): ";
		cin >> c.x;
		cout << "Enter y (1..5): ";
		cin >> c.y;
		c.x--;
		c.y--;
	} while (c.x > 4 || c.y > 4 || g.ppField[c.y][c.x] != EMPTY);

	return c;
}

Coord __fastcall getAICoord(const Game& g)
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Предвыигрыш и предпроигрыш.Было 2 вложеных цикла,сделал в одном
	for (size_t y = 0; y < g.SIZE; y++)
	{
		for (size_t x = 0; x < g.SIZE; x++)
		{
			if (g.ppField[y][x] == EMPTY)
			{
				g.ppField[y][x] = g.ai; // Гипотетический ход: комп проверяет ход на выигрышность
				if (getWon(g) == WON_AI) // если после этого хода выиграл
				{
					g.ppField[y][x] = EMPTY; // возвращает как было
					return { y, x }; // и ходит туда
				}
				g.ppField[y][x] = EMPTY; // в любом случае востанавливаем в пустое(скрываем читерство бота)


				g.ppField[y][x] = g.human; // Гипотетический ход от лица человека: комп ходит за человека,проверяет ход на выигрышность
				if (getWon(g) == WON_HUMAN) // если после этого хода,человек выиграл
				{
					g.ppField[y][x] = EMPTY; // возвращает как было
					return { y, x }; // и ходит туда,тем самым мешает человеку выиграть
				}
				g.ppField[y][x] = EMPTY; // в любом случае востанавливаем в пустое(скрываем читерство бота)
			}
		}

	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	if (g.ppField[2][2] == EMPTY)
	{
		return { 2, 2 };
	}

	Coord arr[20];
	size_t num = 0;
	if (g.ppField[0][0] == EMPTY) // Ищем все и сохраняем свободные углы
	{
		arr[num++] = { 0, 0 }; // сначало NUM используется(0), затем увеличивается на 1.
	}

	if (g.ppField[0][4] == EMPTY)
	{
		arr[num++] = { 0, 4 }; // NUM = 1(после использования = 2 и тд).
	}

	if (g.ppField[4][4] == EMPTY)
	{
		arr[num++] = { 4, 4 };
	}

	if (g.ppField[4][0] == EMPTY)
	{
		arr[num++] = { 4, 0 };
	}

	if (num > 0) // если есть свободные углы
	{
		const size_t index = getRundomNum(0, 1000) % num; // случайный индекс свободного угла
		return arr[index];
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Не углы.Цикл вместо ифов
	for (size_t y = 0; y < g.SIZE; y++)
	{
		for (size_t x = 0; x < g.SIZE; x++)
		{
			if (g.ppField[y][x] == EMPTY && g.ppField[y][x] != g.ppField[0][0] && g.ppField[y][x] != g.ppField[0][4] && g.ppField[y][x] != g.ppField[4][4] && g.ppField[y][x] != g.ppField[4][0])
			{
				arr[num++] = { y, x };
			}
		}
	}

	if (num > 0) // если есть свободные не углы
	{
		const size_t index = getRundomNum(0, 1000) % num; // случайный индекс свободного не угла
		return arr[index];
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

void __fastcall congrats(const Game& g)
{
	if (g.progress == WON_HUMAN)
	{
		cout << "Человек выиграл" << endl;
	}
	else if (g.progress == WON_AI)
	{
		cout << "Бот выиграл" << endl;
	}
	else if (g.progress == DRAW)
	{
		cout << "Ничья" << endl;
	}
}


//================================================================================
//================================================================================