#pragma once
// Структуры и перечесления(struct & enum)
// =====================================================================
// =====================================================================

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

//=======================================================================
//=======================================================================

// Функции
void clearScr();
void __fastcall initGame(Game& g);
void __fastcall deinitGame(Game& g);
void __fastcall drawGame(const Game& g);
GameProgress __fastcall getWon(const Game& g);
Coord __fastcall getHumanCoord(const Game& g);
Coord __fastcall getAICoord(const Game& g);
void __fastcall congrats(const Game& g);
int32_t __fastcall getRundomNum(int32_t min, int32_t max);