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
	Board board;
	int time;
	int drawIndex;
	mt19937 mt;
	uniform_int_distribution<int> diceDist;
	uniform_int_distribution<int> playerOrderDist;
	uniform_int_distribution<int> squareStateDist;
	string WinnerName;
public:
	Scene();
	void TimeUpdate() { time++; }
	int DiceRoll();
	void RunnningSequence();
	void Draw();
	void DrawFrame(string, string, string, int);
	void DrawPlayerSpace(string, string, string, string, int);
	void Result();
};

#endif