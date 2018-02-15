#ifndef _Player_
#define _Player_

#define CLAMP(x, low, high) (x > high)? high : (x < low)? low : x

#include <iostream>
#include <string>

using namespace std;

class Player
{
private:
	enum {
		MAX_DICE = 2// 触れるさいころの最大数
	};
	
	string name_;
	int position_;     // マスの位置
	int order_;        // 順番
	bool canMove_;     // 休みでないか
	char icon_;        // 表示用キャラクタ
	int turn_;         // 動ける回数
	int numDice_;      // 触れるさいころの数
	bool isHuman_;     // AIでないか
	int destination_;  // 何歩進むか

public:
	Player();
	Player(int index, char icon, string name, bool isHuman);

	const string &GetName() const { return name_; }
	int GetOrder() const { return order_; }
	char GetIcon() const { return icon_; }
	bool IsHuman() const { return isHuman_; }
	
	// 位置
	int GetPos() const { return position_; }
	bool CanMove() const { return (turn_ > 0); }
	void Move(int step) {if (turn_ > 0) { position_ += step; }}
	void SetPos(int pos) { position_ = pos; }
	void SetDestination(int dest) { destination_ = dest; }
	int GetDestination() { return destination_; }
	void SwapPos(Player &target) ;

	// turn
	int GetTurn() const { return turn_; }
	void ChangeNumTurn(int turn) {turn_ = CLAMP(turn, 0, MAX_DICE);}
	void AddTurn();

	// さいころの数
	int GetNumDice() const { return numDice_; }
	void ChangeNumDice(int number) {numDice_ = CLAMP(number, 1, MAX_DICE);}
	void ResetNumDice() { numDice_ = 1; }
};


#endif
