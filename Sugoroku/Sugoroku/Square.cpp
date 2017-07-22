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

		cout << effectAmount << "マス進む\n";
		target->Move(effectAmount);
		break;

	case Type::StepBack:
		cout << effectAmount << "マス戻る\n";
		target->Move(-effectAmount);
		break;

	case Type::LoseTurn:
		cout << effectAmount << "回休み\n";
		target->ChangeNumTurn(-effectAmount);
		break;

	case Type::DoubleUp:
		cout << "次のターン、サイコロをさらに " << effectAmount << " 回振れる\n";
		target->ChangeNumDice(effectAmount);
		break;
	}
};