#include"SSnake.h"
#include"GlobalDefinition.h"
SSnake::SSnake()
{
	length=SnakeLength;
	for (int i = 0; i < length; i++)
	{
		snake.push_back(ChessPoint(SnakeX[i],SnakeY[i]));
	}

	//snake.push_back(
}

SSnake::~SSnake()
{
}

SSnake::iterator SSnake::begin()
{
	return snake.begin();
}
SSnake::iterator SSnake::end()
{
	return snake.end();
}

void SSnake::Eat(ChessPoint	cp)
{
	snake.insert(snake.begin(),cp);
	length++;
}

void SSnake::Move(ChessPoint	cp)
{
	for(auto iter=snake.rbegin();iter!=snake.rend()-1;iter++)
	{
		*iter=*(iter+1);
	}
	snake.front()=snake.front()+cp;
}

int SSnake::Length()
{
	return length;
}
