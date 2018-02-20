#include "Board.h"
#include <random>

Board::Board()
{
	Board(1);
}

Board::Board(int BoardLength)
{
	boardLength_ = BoardLength;
	square_.resize(boardLength_);

	random_device rnd;
	mt19937 mt(rnd());
	
	//�e�}�X�̕��z
	uniform_int_distribution<int> dist(0, NUM_SQUARE_TYPE * 2);
	
	//�O�i�A��ރ}�X�̌��ʂ̐U�蕝
	uniform_int_distribution<int> effectDist(1, 4);

	for (int i = 0; i < boardLength_; i++)
	{
		Square *square = &square_[i];

		//�ŏ��A�Ō�̃}�X�͋�
		if (i == 0 || i == boardLength_ - 1)
		{
			square->Initialize();
			continue;
		}

		int numTypes = dist(mt);
		switch (numTypes)
		{
		case sqStat::StepBack:
			square->Initialize(sqStat::StepBack, effectDist(mt));
			break;

		case sqStat::StepForward:
			square->Initialize(sqStat::StepForward, effectDist(mt));
			break;

		case sqStat::LoseTurn:
			square->Initialize(sqStat::LoseTurn, 1);
			break;

		case sqStat::DoubleUp:
			square->Initialize(sqStat::DoubleUp, 2);
			break;

		case sqStat::Swap:
			square->Initialize(sqStat::Swap, 0);
			break;

		case sqStat::Blank:

		default:
			square->Initialize();
			break;
		}
	}
};