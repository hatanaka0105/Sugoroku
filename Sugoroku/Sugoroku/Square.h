#ifndef _Square_
#define _Square_

#include "Player.h"

namespace sqStat
{
	enum Type
	{
		Blank,
		StepBack,
		StepForward,
		LoseTurn,
		DoubleUp,
	};

	class Square
	{
	private:
		int Position;
		Type type;
		int effectAmount;
		string color;
	public:
		void Initialize();
		void Initialize(Type, int);
		void SquareChange(Type state) { this->type = state; }
		void Effect(Player*);
		Type GetType() { return type; }
	};
};

#endif