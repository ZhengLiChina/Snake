#include"GameRuler.h"
#include"GlobalDefinition.h"
#include<ctime>

GameRuler::GameRuler(Chessboard& cb,SSnake& snk):chessboard(cb),snake(snk),direction(1,0)
{

	for(auto iter=snake.begin();iter!=snake.end();iter++)
	{
		chessboard.SetChessPoint(*iter,GridSnake);
	}
	AddFood();
}

GameRuler::~GameRuler()
{
}

Result GameRuler::Go()
{
	int id= chessboard.GetIdOfPoint( *snake.begin()+direction);
	if (id==0)
	{
		chessboard.SetChessPoint(*(snake.end()-1),GridSpace);
		snake.Move(direction);
		chessboard.SetChessPoint(*snake.begin(),GridSnake);//head has changed, so no need to +direction
		return Result::ToBeContinued;
	}
	if (id==-1||id==GridSnake)//edge of itself, die
	{
		return Result::Lose;
	}
	if (id==GridFood)
	{
		snake.Eat(*snake.begin()+direction);
		chessboard.SetChessPoint(*snake.begin(),GridSnake);//head has changed, so no need to +direction
		if (snake.Length()==chessboard.GetWidth()*chessboard.GetHeight())
		{
			return Result::Win;
		}
		AddFood();
	}
	return Result::ToBeContinued;
}

bool GameRuler::ChangeDirection(ChessPoint direction)
{
	if ((*(snake.begin())+direction)==*(snake.begin()+1))
	{
		return false;
	}
	this->direction=direction;
	return true;
}


ChessPoint GameRuler::AddFood()
{
	srand(time(0));
	ChessPoint cp(0,0);

	do
	{
		cp.x=rand()% chessboard.GetWidth();
		cp.y=rand()% chessboard.GetHeight();
	} while (!chessboard.SetChessPoint(cp,GridFood));

	return cp;
}
