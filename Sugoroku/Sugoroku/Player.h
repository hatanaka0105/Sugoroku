#ifndef Player_H_
#define Player_H_

#include <iostream>
#include <string>

#define NOMINMAX
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define CLAMP(x, low, high) max(min(high, x), low)

using namespace std;

class Player
{
private:
	enum {
		MAX_DICE = 2,  // 触れるさいころの最大数
		MAX_TURN = 1   // 行動回数の最大数
	};
	
	string name_;
	int position_;     // マスの位置
	int order_;        // 順番
	char icon_;        // 表示用キャラクタ
	int turn_;         // 動ける回数
	int numDice_;      // 触れるさいころの数
	bool isHuman_;     // AIでないか
	int destination_;  // 前進・後退マスで移動する予約歩数

public:
	Player();
	Player(int index, char icon, string name, bool isHuman);

	const string &GetName() const { return name_; }
	int GetOrder() const { return order_; }
	char GetIcon() const { return icon_; }
	bool IsHuman() const { return isHuman_; }
	
	// 位置
	int GetPos() const { return position_; }
	void Move(int step) { position_ += step; }
	void SetPos(int pos) { position_ = pos; }
	void SetDestination(int dest) { destination_ = dest; }
	int GetDestination() { return destination_; }
	void SwapPos(Player &target) ;

	// 行動回数
	bool CanMove() const { return (turn_ > 0); }
	void ChangeNumTurn(int turn) { turn_ = CLAMP(turn, 0, MAX_TURN); }
	void Revive() { turn_ = 1; }

	// さいころの数
	int GetNumDice() const { return numDice_; }
	void ChangeNumDice(int number) { numDice_ = CLAMP(number, 1, MAX_DICE); }
	void ResetNumDice() { numDice_ = 1; }
};


#endif
