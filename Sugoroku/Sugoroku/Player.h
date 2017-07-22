#ifndef _Player_
#define _Player_

#include <iostream>
#include <string>

using namespace std;

class Player
{
private:
	string name;
	int position;
	int index;
	bool canMove;
	char icon;
	int turn;
	int numDice;
	bool isHuman;

public:
	Player();
	Player(int, char, string, bool);
	Player* Get() { return this; }
	string GetName() { return this->name; }
	void Move(int step) {
		if (turn > 0) { position += step; }
	}
	void ChangePos(int value) { this->position = value; }
	int GetPos() { return this->position; }
	void ChangeNumTurn(int turn) { 
		if (turn < 0) { this->turn = 0; }
		if (turn > 2) { this->turn = 2; }
		this->turn = turn;
	}
	void AddTurn() { this->turn++; }
	void ChangeNumDice(int number) {
		if (number < 1) { this->numDice = 1; }
		if (number > 2) { this->numDice = 2; }
		this->numDice = number; }
	void ResetNumDice() { this->numDice = 1; }
	int GetNumDice() { return numDice; }

	int GetOrder() { return this->index; }
	bool CanMove() { if (this->turn > 0) { return true; } else { return false; } }
	int GetTurn() { return this->turn; }
	char GetIcon() { return this->icon; }
	bool IsHuman() { return this->isHuman; }
	void Swap(Player);
};

#endif