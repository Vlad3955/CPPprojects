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

		clearScr();// после каждого хода чистим экран 
		drawGame(g);// отображаем обновленное поле
		g.turn++;// увеличиваем очередность хода на 1

		g.progress = getWon(g);// кто победил

	} while (g.progress == IN_PROGRESS);

	congrats(g);

	deinitGame(g);
	return 0;
}