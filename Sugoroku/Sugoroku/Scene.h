#ifndef _Scene_
#define _Scene_

#include <iostream>
#include <string>
#include <random>
#include <list>
#include <limits>
#include <windows.h>
#include "Player.h"
#include "Board.h"


using namespace std;

class Scene
{
private:
	list<Player> players;
	Player* precedingPlayer;

	Board board;

	int numTurn;
	int drawIndex;

	mt19937 mt;
	uniform_int_distribution<int> diceDist;
	uniform_int_distribution<int> playerOrderDist;
	uniform_int_distribution<int> squareStateDist;

	bool isGoal;
	string winnerName;

public:
	Scene();

	void TurnUpdate() { numTurn++; }

	void Run();
	int RollDice(Player*);
	void ProcessMovement(Player*, int);
	void MovePlayerByStep(Player*, int, int);

	void Draw();
	void DrawRowFrame(string, string, string, int);
	void DrawPlayerSpace(string, string, string, string, int);

	void Result();
};

#endif