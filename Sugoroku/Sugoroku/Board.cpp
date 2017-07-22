#include "Board.h"
#include <random>

Board::Board(int BoardLength)
{
	Board::boardLength = BoardLength;
	Board::square.resize(Board::boardLength);

	random_device rnd;
	mt19937 mt(rnd());
	uniform_int_distribution<int> dist(0, sqStat::DoubleUp * 2);
	uniform_int_distribution<int> effectDist(1, 2);

	for (int i = 0; i < Board::boardLength; i++)
	{
		int numTypes = dist(mt);

		if(numTypes == sqStat::Blank || i == 0 || i == Board::boardLength)
			Board::square[i].Initialize();
		else if(numTypes == sqStat::StepBack)
			Board::square[i].Initialize(sqStat::StepBack, effectDist(mt));
		else if (numTypes == sqStat::StepForward)
			Board::square[i].Initialize(sqStat::StepForward, effectDist(mt));
		else if (numTypes == sqStat::LoseTurn)
			Board::square[i].Initialize(sqStat::LoseTurn, 1);
		else if (numTypes == sqStat::DoubleUp)
			Board::square[i].Initialize(sqStat::DoubleUp, effectDist(mt));
		else
			Board::square[i].Initialize();
	}
};