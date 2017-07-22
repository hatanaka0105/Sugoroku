#ifndef _Board_
#define _Board_

#include <random>
#include "Square.h"

using namespace std;
using namespace sqStat;

class Board
{
private:
	int boardLength;
	vector<Square> square;
public:
	Board() {};
	Board(int BoardLength);
	int Length() { return boardLength; }
	Square GetSquare(int index) { return square[index]; }
};

#endif