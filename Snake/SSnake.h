#ifndef SSNAKE_ZHENGLI
#define SSNAKE_ZHENGLI

#include<vector>
#include"Chessboard.h"
class SSnake
{
public:
	SSnake();
	~SSnake();

	typedef std::vector<ChessPoint>::iterator iterator;

	iterator begin();
	iterator end();
	void Eat(ChessPoint	cp);
	void Move(ChessPoint	cp);
	int Length();

private:
	std::vector<ChessPoint> snake;
	int length;
};


#endif