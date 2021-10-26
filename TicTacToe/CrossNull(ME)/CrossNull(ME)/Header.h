#pragma once
// ��������� � ������������(struct & enum)
// =====================================================================
// =====================================================================

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

//=======================================================================
//=======================================================================

// �������
void clearScr();
void __fastcall initGame(Game& g);
void __fastcall deinitGame(Game& g);
void __fastcall drawGame(const Game& g);
GameProgress __fastcall getWon(const Game& g);
Coord __fastcall getHumanCoord(const Game& g);
Coord __fastcall getAICoord(const Game& g);
void __fastcall congrats(const Game& g);
int32_t __fastcall getRundomNum(int32_t min, int32_t max);