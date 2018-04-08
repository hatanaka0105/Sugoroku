#ifndef Square_H_
#define Square_H_

#define NUM_SQUARE_TYPE Type::Swap

#include "Player.h"

namespace sqStat
{
	enum Type
	{
		Blank,		//通常マス
		StepBack,	//一つ戻る
		StepForward,//一つ進む
		LoseTurn,	//一回休み
		DoubleUp,	//次のターン、2回サイコロを振れる
		Swap,		//他のプレイヤーと位置を入れ替える
	};

	class Square
	{
	private:
		int position_;
		Type type_;
		int effectAmount_;

	public:
		void Initialize();
		void Initialize(Type state, int effectAmount);

		void SquareChange(Type state) { type_ = state; }

		void ApplyEffect(Player& player, Player& swapTarget);

		Type GetType() const { return type_; }
	};
};

#endif
