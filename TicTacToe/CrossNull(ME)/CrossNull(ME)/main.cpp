#include "Header.h"




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