#ifndef Board_H_
#define Board_H_

#include <random>
#include "Square.h"

using namespace std;
using namespace sqStat;

class Board
{
private:
	int boardLength_;
	vector<Square> square_;

public:
	Board();
	Board(int BoardLength);
	
	int GetLength() const { return boardLength_; }
	Square GetSquare(int index) const { return square_[index]; }
};

#endif