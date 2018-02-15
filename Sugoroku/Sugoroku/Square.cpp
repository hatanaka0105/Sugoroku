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

		cout << effectAmount_ << "マス進む\n";
		target->Move(effectAmount_);
		break;

	case Type::StepBack:
		cout << effectAmount_ << "マス戻る\n";
		target->Move(-effectAmount_);
		break;

	case Type::LoseTurn:
		cout << effectAmount_ << "回休み\n";
		target->ChangeNumTurn(-effectAmount_);
		break;

	case Type::DoubleUp:
		cout << "次のターン、サイコロをさらに " << effectAmount_ << " 回振れる\n";
		target->ChangeNumDice(effectAmount_);
		break;
	}
};