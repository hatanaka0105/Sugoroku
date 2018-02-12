#include "Player.h"

Player::Player()
{
}

Player::Player(int PlayerIndex, char CharacterIcon, string name, bool IsHuman)
{
	Player::position = 1;
	Player::index = PlayerIndex;
	Player::icon = CharacterIcon;
	Player::numDice = 1;
	Player::turn = 1;
	Player::name = name;
	Player::isHuman = IsHuman;
}

void Player::Swap(Player opponent)
{
	int ownPos = Player::GetPos();
	Player::ChangePos(opponent.GetPos());
	opponent.ChangePos(ownPos);
};

void Player::AddTurn() 
{
	ResetNumDice();// ターン終わりにはさいころの数を戻す
	turn_++; 
}
