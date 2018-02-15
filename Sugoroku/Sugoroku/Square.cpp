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

void Square::ApplyEffect(Player *target, Player *swapTarget)
{
	switch (Square::type_)
	{
	case Type::Blank:
		break;

	case Type::StepForward:
		cout << effectAmount_ << "�}�X�i��\n";
		target->SetDestination(effectAmount_);

		break;

	case Type::StepBack:
		if (target->GetPos() > effectAmount_)
		{
			cout << effectAmount_ << "�}�X�߂�\n";
			target->SetDestination(-effectAmount_);
		}
		else
		{
			cout << target->GetPos() << "�}�X�߂�\n";
			//�X�^�[�g�n�_��ʂ�߂��Ă��܂��ꍇ
			target->SetDestination(-target->GetPos());
		}

		break;

	case Type::LoseTurn:
		cout << effectAmount_ << "��x��\n";
		target->ChangeNumTurn(-effectAmount_);

		break;

	case Type::DoubleUp:
		cout << "���̃^�[���A�T�C�R��������� " << effectAmount_ - 1 << " ��U���\n";
		target->ChangeNumDice(effectAmount_);

		break;
		
	case Type::Swap:
		cout << "�ł��S�[���ɋ߂��v���C���[�ƈʒu�����ւ���";
		target->SwapPos(*swapTarget);

		break;
	}
};