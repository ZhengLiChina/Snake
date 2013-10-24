#include"Instances.h"


Chessboard& GetChessboard()
{
	static Chessboard cb(MapWidth,MapHeight);
	return cb;
}
SSnake& GetSnake()
{
	static SSnake snake;
	return snake;
}
GameRuler& GetGameRuler()
{
	static GameRuler gr(GetChessboard(),GetSnake());
	return gr;
}