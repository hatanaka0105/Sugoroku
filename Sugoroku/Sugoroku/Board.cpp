#include "Board.h"
#include <random>

Board::Board(int BoardLength)
{
	Board::boardLength = BoardLength;
	Board::square.resize(Board::boardLength);

	random_device rnd;
	mt19937 mt(rnd());
	
	//�e�}�X�̕��z
	uniform_int_distribution<int> dist(0, sqStat::Swap * 2);
	
	//�O�i�A��ރ}�X�̌��ʂ̐U�蕝
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

		//�ŏ��A�Ō�̃}�X�͋󔒂�
		Board::square[0].Initialize();
		Board::square[boardLength - 1].Initialize();
	}
};