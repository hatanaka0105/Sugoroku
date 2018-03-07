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

void Square::ApplyEffect(Player &target, Player &swapTarget)
{
	switch (Square::type_)
	{
	case Type::Blank:
		break;

	case Type::StepForward:
		cout << effectAmount_ << "マス進む\n";
		target.SetDestination(effectAmount_);

		break;

	case Type::StepBack:
		if (target.GetPos() > effectAmount_)
		{
			cout << effectAmount_ << "マス戻る\n";
			target.SetDestination(-effectAmount_);
		}
		else
		{
			//スタート地点を通り過ぎてしまう場合
			cout << target.GetPos() << "マス戻る\n";
			target.SetDestination(-target.GetPos());
		}

		break;

	case Type::LoseTurn:
		cout << effectAmount_ << "回休み\n";
		target.ChangeNumTurn(-effectAmount_);

		break;

	case Type::DoubleUp:
		cout << "次のターン、サイコロをさらに " << effectAmount_ - 1 << " 回振れる\n";
		target.ChangeNumDice(effectAmount_);

		break;
		
	case Type::Swap:
		cout << "Swapマスです\n";
		cout << "最もゴールに近いプレイヤーと位置を入れ替える\n";
		cout << "入れ替え相手は " << swapTarget.GetName() << " です";
		target.SwapPos(swapTarget);

		break;
	}
};