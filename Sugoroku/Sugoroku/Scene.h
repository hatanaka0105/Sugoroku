#ifndef Scene_H_
#define Scene_H_

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
	uniform_int_distribution<int> squareStateDist;

	bool isGoal;

public:
	Scene();

	void TurnUpdate() { numTurn++; }

	void Run();
	int RollDice(Player &target);
	void ProcessMovement(Player &target, int numRollOfDice);
	void MovePlayerByStep(Player &target, int numSteps, int lengthByStep);
	void CheckPrecedingPlayer(Player &target);

	void Draw();
	void DrawRowFrame(string first, string middle, string end, int numTurn);
	void DrawPlayerSpace(string first, string middle, string space, string end, int numTurn);
	void DrawLineAtIntervals(string line, int intervals);

	void Result();
};

#endif
