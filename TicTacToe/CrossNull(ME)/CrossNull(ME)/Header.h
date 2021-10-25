#pragma once
enum Cell;
struct Coord;
enum GameProgress;
struct  Game;
void clearScr();
void __fastcall initGame(Game& g);
void __fastcall deinitGame(Game& g);
void __fastcall drawGame(const Game& g);
GameProgress __fastcall getWon(const Game& g);
Coord __fastcall getHumanCoord(const Game& g);
Coord __fastcall getAICoord(const Game& g);
void __fastcall congrats(const Game& g);
int32_t __fastcall getRundomNum(int32_t min, int32_t max);