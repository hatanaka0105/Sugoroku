#include "Square.h"

using namespace sqStat;

void Square::Initialize()
{
	Square::type_ = Type::Blank;
	Square::effectAmount_ = 0;
};

void Square::Initialize(sqStat::Type type, int amount)
{
	Square::type_ = type;
	Square::effectAmount_ = amount;
};

void Square::Effect(Player *target)
{
	switch (Square::type_)
	{
	case Type::Blank:
		break;

	case Type::StepForward:

		cout << effectAmount_ << "�}�X�i��\n";
		target->Move(effectAmount_);
		break;

	case Type::StepBack:
		cout << effectAmount_ << "�}�X�߂�\n";
		target->Move(-effectAmount_);
		break;

	case Type::LoseTurn:
		cout << effectAmount_ << "��x��\n";
		target->ChangeNumTurn(-effectAmount_);
		break;

	case Type::DoubleUp:
		cout << "���̃^�[���A�T�C�R��������� " << effectAmount_ << " ��U���\n";
		target->ChangeNumDice(effectAmount_);
		break;
	}
};