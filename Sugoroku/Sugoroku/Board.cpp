#include "Board.h"
#include <random>

Board::Board(int BoardLength)
{
	Board::boardLength = BoardLength;
	Board::square.resize(Board::boardLength);

	random_device rnd;
	mt19937 mt(rnd());
	
	//各マスの分布
	uniform_int_distribution<int> dist(0, sqStat::Swap * 2);
	
	//前進、後退マスの効果の振り幅
	uniform_int_distribution<int> effectDist(1, 4);

	for (int i = 0; i < Board::boardLength; i++)
	{
		int numTypes = dist(mt);

		switch (numTypes)
		{
		case sqStat::Blank:
			Board::square[i].Initialize();
			break;

		case sqStat::StepBack:
			Board::square[i].Initialize(sqStat::StepBack, effectDist(mt));
			break;

		case sqStat::StepForward:
			Board::square[i].Initialize(sqStat::StepForward, effectDist(mt));
			break;

		case sqStat::LoseTurn:
			Board::square[i].Initialize(sqStat::LoseTurn, 1);
			break;

		case sqStat::DoubleUp:
			Board::square[i].Initialize(sqStat::DoubleUp, 2);
			break;

		case sqStat::Swap:
			Board::square[i].Initialize(sqStat::Swap, 0);

		default:
			Board::square[i].Initialize();
			break;
		}

		//最初、最後のマスは空白に
		Board::square[0].Initialize();
		Board::square[boardLength - 1].Initialize();
	}
};