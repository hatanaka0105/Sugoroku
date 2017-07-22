#include "Square.h"

using namespace sqStat;

void Square::Initialize()
{
	Square::type = Type::Blank;
	Square::effectAmount = 0;
};

void Square::Initialize(sqStat::Type type, int amount)
{
	Square::type = type;
	Square::effectAmount = amount;
};

void Square::Effect(Player *target)
{
	switch (Square::type)
	{
	case Type::Blank:
		break;

	case Type::StepForward:

		cout << effectAmount << "�}�X�i��\n";
		target->Move(effectAmount);
		break;

	case Type::StepBack:
		cout << effectAmount << "�}�X�߂�\n";
		target->Move(-effectAmount);
		break;

	case Type::LoseTurn:
		cout << effectAmount << "��x��\n";
		target->ChangeNumTurn(-effectAmount);
		break;

	case Type::DoubleUp:
		cout << "���̃^�[���A�T�C�R��������� " << effectAmount << " ��U���\n";
		target->ChangeNumDice(effectAmount);
		break;
	}
};