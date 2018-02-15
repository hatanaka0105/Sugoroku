#include "Player.h"

Player::Player()
{
}

Player::Player(int PlayerIndex, char CharacterIcon, string name, bool IsHuman)
{
	Player::position_ = 1;
	Player::order_ = PlayerIndex;
	Player::icon_ = CharacterIcon;
	Player::numDice_ = 1;
	Player::turn_ = 1;
	Player::name_ = name;
	Player::isHuman_ = IsHuman;
}

void Player::SwapPos(Player& opponent)
{
	int ownPos = Player::GetPos();
	Player::SetPos(opponent.GetPos());
	opponent.SetPos(ownPos);
};


void Player::AddTurn()
{
	turn_++; 
}
