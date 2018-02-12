#ifndef _Player_
#define _Player_

#include <iostream>
#include <string>

using namespace std;

class Player
{
private:
	enum{
		MAX_DICE = 2;// 触れるさいころの最大数
	}
	
	string name_;
	int position_; // マスの位置
	int order_;    // 順番
	bool canMove_; // 休みでないか
	char icon_;    // 表示用キャラクタ
	int turn_;     // ???
	int numDice_;  // 触れるさいころの数
	bool isHuman_; // AIでないか

	void ResetNumDice() { numDice_ = 1; }
public:
	Player();
	Player(int index, char icon, string name, bool isHuman);

//	Player* Get() { return this; }

	const string &GetName() const { return name_; }
	int GetOrder() const { return order_; }
	char GetIcon() const { return icon_; }
	bool IsHuman() const { return isHuman_; }
	
	// 位置
	int GetPos() const { return position_; }
	bool CanMove() const { return (turn_ > 0); }
	void Move(int step) {if (turn_ > 0) { position_ += step; }}
	void SetPos(int pos) { position_ = pos; }
	void Swap(Player &target) ;// SwapPos

	// turn
	int GetTurn() const { return turn_; }
	void ChangeNumTurn(int turn) {turn_ = std::clamp(turn, 0, MAX_DICE);}
	void AddTurn();

	// さいころの数
	int GetNumDice() const { return numDice; }
	void ChangeNumDice(int number) {numDice _ = std::clamp(number, 1, MAX_DICE);}
};


#endif
