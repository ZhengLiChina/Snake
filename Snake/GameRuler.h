#ifndef GAMERULER_ZHENGLI
#define GAMERULER_ZHENGLI

#include"Chessboard.h"
#include"SSnake.h"

enum Result {Win,Lose,ToBeContinued,Error };


class GameRuler
{
public:
	GameRuler(Chessboard& cb,SSnake& snk);
	~GameRuler();
	Result Go();
	bool ChangeDirection(ChessPoint direction);

private:
	Chessboard& chessboard;
	SSnake& snake;
	ChessPoint AddFood();
	ChessPoint direction;
};



#endif