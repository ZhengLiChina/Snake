#ifndef CHESSBOARD_ZHENGLI
#define CHESSBOARD_ZHENGLI

struct ChessPoint
{
	int x;
	int y;
	ChessPoint(int a,int b)
	{
		x=a;y=b;
	}
};

ChessPoint operator+(const ChessPoint& l,const ChessPoint& r);
ChessPoint operator-(const ChessPoint& l,const ChessPoint& r);
bool operator==(const ChessPoint& l,const ChessPoint& r);

class Chessboard
{
public:
	Chessboard(int w=10,int h=10);
	~Chessboard();
	int GetWidth()const{return width;}
	int GetHeight()const{return height;}
	bool SetChessPoint(const ChessPoint& cp,int id);
	//int** const GetPoints()const
	//{
	//	return cb;
	//}
	int GetSum()const
	{
		return sum;
	}
	int GetIdOfPoint(const ChessPoint& cp)const;

private:
	int width;
	int height;
	char *cb;
	int sum;

	bool isPointValid(const ChessPoint& cp)const;
};

#endif


