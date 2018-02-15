#ifndef _Square_
#define _Square_

#include "Player.h"

namespace sqStat
{
	enum Type
	{
		Blank,		//通常マス
		StepBack,	//一つ戻る
		StepForward,	//一つ進む
		LoseTurn,	//一回休み
		DoubleUp,	//次のターン、2回サイコロを振れる
	};

	class Square
	{
	private:
		int position_;
		Type type_;
		int effectAmount_;
		string color_;
	public:
		void Initialize();
		void Initialize(Type, int);
		void SquareChange(Type state) { type_ = state; }
		void Effect(Player*);
		Type GetType() { return type_; }
	};
};

#endif
