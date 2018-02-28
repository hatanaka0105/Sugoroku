#include "Scene.h"

#define WAIT_TIME 500
#define WAIT_TIME_LONG 900
#define BOARD_LENGTH 40

Scene::Scene()
{
	//決定的乱数生成(メルセンヌ・ツイスタ)
	random_device rnd;
	mt = mt19937(rnd());
	
	//ダイス用
	diceDist = uniform_int_distribution<int>(1, 6);
	//マス生成用
	squareStateDist = uniform_int_distribution<int>(0, NUM_SQUARE_TYPE);
	
	//プレイヤー生成と初期化
	string name;
	cout << "プレイヤーの名前を設定します\n 名前 : ";
	cin >> name;

	char icon;
	cout << "\n次に、 " << name << " さんのアイコンを設定します\n アイコン : ";
	cin >> icon;

	cout << "ゲームが始まります";
	cin.clear();
	cin.ignore(500,'\n');
	Sleep(WAIT_TIME);

	Player player = Player(0, icon, name, true);
	Player NPC1 = Player(1, 'C', "Curly", false);
	Player NPC2 = Player(2, 'M', "Moe", false);
	Player NPC3 = Player(3, 'L', "Larry", false);

	players.push_back(player);
	players.push_back(NPC1);
	players.push_back(NPC2);
	players.push_back(NPC3);

	board = Board(BOARD_LENGTH);

	Draw();
};

void Scene::Run()
{
	for (;;)
	{
		TurnUpdate();

		//イテレータを生成してリストに登録されたプレイヤー毎に行動する
		for (auto player = players.begin(); player != players.end(); ++player)
		{
			DrawLineAtIntervals(player->GetName() + "の手番です\n", WAIT_TIME);

			if (player->CanMove())
			{
				int numRollOfDice = RollDice(*player);

				ProcessMovement(&(*player), numRollOfDice);
			}
			else
			{
				cout << "一回休みです";
				player->Revive();
			}

			Sleep(WAIT_TIME);
			Draw();

			if (isGoal)
			{
				return;
			}
		}
	}
};

int Scene::RollDice(Player &player)
{
	if (player.IsHuman())
	{
		cout << "Enterキーでサイコロを振ります\n";
		getchar();
	}

	DrawLineAtIntervals("出た目の数は...", WAIT_TIME);

	int roll = 0;
	int sum = 0;

	//サイコロの数だけ振る
	for (int i = 0; i < player.GetNumDice(); i++)
	{
		if (i > 0)
		{
			DrawLineAtIntervals(" + ", WAIT_TIME);
		}

		roll = diceDist(mt);
		sum += roll;
		DrawLineAtIntervals(std::to_string(roll), WAIT_TIME);
	}

	if (player.GetNumDice() > 1)
	{
		cout << " = " << sum;

		player.ResetNumDice();
	}
	
	DrawLineAtIntervals("です\n", WAIT_TIME);

	return sum;
};

void Scene::ProcessMovement(Player* player, int numRollOfDice)
{
	//移動(1マスずつ移動する演出)
	MovePlayerByStep(player, numRollOfDice, 1);

	int playerPos = player->GetPos();

	//移動先のマスの効果適用
	board.GetSquare(playerPos).ApplyEffect(&(*player), precedingPlayer);

	if (board.GetSquare(playerPos).GetType() != sqStat::Blank)
	{
		Sleep(WAIT_TIME_LONG);

		//前進・後退マスに入っていた場合、その分だけ1マスずつ移動
		if (player->GetDestination() > 0)
		{
			MovePlayerByStep(player, player->GetDestination(), 1);
		}
		else if (player->GetDestination() < 0)
		{
			MovePlayerByStep(player, -player->GetDestination(), -1);
		}
	}

	//行動を終える前にこのプレイヤーが先頭を行っているか確認する
	for (auto itr = players.begin(); itr != players.end(); ++itr) {
		if (playerPos < itr->GetPos())
		{
			break;
		}

		if (playerPos > itr->GetPos())
		{
			precedingPlayer = &(*player);
		}
	}
}

void Scene::MovePlayerByStep(Player* player, int numSteps, int lengthByStep)
{
	for (int i = 0; i < numSteps; i++)
	{
		player->Move(lengthByStep);
		Draw();
		Sleep(WAIT_TIME);

		if (player->GetPos() >= board.GetLength())
		{
			player->SetPos(board.GetLength());
			
			winnerName = player->GetName();
			isGoal = true;

			return;
		}
	}

	player->SetDestination(0);
}

void Scene::DrawRowFrame(string first, string middle, string end, int numTurn)
{
	cout << first;
	for (int j = 0; j < numTurn; j++)
	{
		cout << middle;
	}
	cout << end;
};

void Scene::DrawPlayerSpace(string first, string middle, string space, string end, int numTurn)
{
	cout << first;
	for (int j = 0; j <= numTurn - 1; j++)
	{
		drawIndex++;

		cout << middle;

		for (auto player = players.begin(); player != players.end(); ++player)
		{
			if (drawIndex == player->GetPos())
			{
				cout << player->GetIcon();
			}
			else
			{
				cout << space;
			}
		}
	}

	cout << end;
}

void Scene::DrawLineAtIntervals(string line, int intervals)
{
	cout << line;
	Sleep(intervals);
}

void Scene::Draw()
{
	drawIndex = 0;

	system("cls");

	DrawRowFrame("┌", "─────┬", "─────┐\n", 9);

	for (int i = 0; i < 2; i++)
	{
		DrawPlayerSpace("", "│ ", " ", "│\n", 10);
		DrawRowFrame("├", "─────┼", "─────┤\n", 9);
	}

	DrawPlayerSpace("", "│ ", " ", "│\n", 10);
	DrawRowFrame("└", "─────┴", "─────┘\n", 9);

	for (auto Character = players.begin(); Character != players.end(); ++Character)
	{
		cout << "\n " << Character->GetName() << " : ";

		if (!Character->CanMove())
		{
			cout << "一回休み";
		}
		else if (Character->GetNumDice() > 1)
		{
			cout << "サイコロ+1";
		}
		else
		{
			cout << "ふつう";
		}

		cout << "\n\n";
	}
};

void Scene::Result()
{
	DrawLineAtIntervals(winnerName + "がゴール！\n", WAIT_TIME);
	cout << "到達までにかかった回数 : " << numTurn << "\n";
};
