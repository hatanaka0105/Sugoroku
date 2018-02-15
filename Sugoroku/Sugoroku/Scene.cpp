#include "Scene.h"

#define NumPlayer 4
#define WaitTime 500
#define WaitTime_Long 900

Scene::Scene()
{
	//決定的乱数生成(メルセンヌ・ツイスタ)
	random_device rnd;
	mt = mt19937(rnd());
	
	//ダイス用
	diceDist = uniform_int_distribution<int>(1, 6);
	//プレイヤーの順番用
	playerOrderDist = uniform_int_distribution<int>(0, NumPlayer);
	//マス生成用
	squareStateDist = uniform_int_distribution<int>(0, sqStat::Type::DoubleUp);
	
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
	Sleep(WaitTime);

	Player player = Player(0, icon, name, true);
	Player NPC1 = Player(1, 'C', "Curly", false);
	Player NPC2 = Player(2, 'M', "Moe", false);
	Player NPC3 = Player(3, 'L', "Larry", false);

	players.push_back(player);
	players.push_back(NPC1);
	players.push_back(NPC2);
	players.push_back(NPC3);

	board = Board(40);

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
			cout << player->GetName() << "の手番です\n";

			Sleep(WaitTime);

			if (player->CanMove())
			{
				int numRollOfDice = RollDice(&(*player));

				ProcessMovement(&(*player), numRollOfDice);
			}
			else
			{
				cout << "一回休みです";
				player->AddTurn();
			}

			Sleep(WaitTime);
			Draw();

			if (isGoal)
			{
				return;
			}
		}
	}
};

int Scene::RollDice(Player* player)
{
	if (player->IsHuman())
	{
		cout << "Enterキーでサイコロを振ります\n";
		getchar();
	}

	int roll = 0;
	int sum = 0;

	if (player->GetTurn() < 1)
		player->AddTurn();

	cout << "出た目の数は...";
	Sleep(WaitTime);

	for (int i = 0; i < player->GetNumDice(); i++)
	{
		if (i > 0)
		{
			cout << " + ";
			Sleep(WaitTime);
		}

		roll = diceDist(mt);
		sum += roll;
		cout << roll;
		Sleep(WaitTime);
	}

	if (player->GetNumDice() > 1)
	{
		cout << " = " << sum;

		player->ResetNumDice();
	}

	cout << "です\n";
	Sleep(WaitTime);

	return sum;
};

void Scene::ProcessMovement(Player* player, int numRollOfDice)
{
	//移動(1マスずつ移動する演出)
	MovePlayerByStep(player, numRollOfDice, 1);

	//移動先のマスの効果適用
	board.GetSquare(player->GetPos()).ApplyEffect(&(*player), precedingPlayer);
	if (board.GetSquare(player->GetPos()).GetType() != sqStat::Blank)
	{
		Sleep(WaitTime_Long);

		if (player->GetDestination() > 0)
		{
			MovePlayerByStep(player, player->GetDestination(), 1);
		}
		else if (player->GetDestination() < 0)
		{
			MovePlayerByStep(player, -player->GetDestination(), -1);
		}
	}
}

void Scene::MovePlayerByStep(Player* player, int numSteps, int step)
{
	for (int i = 0; i < numSteps; i++)
	{
		player->Move(step);
		Draw();
		Sleep(WaitTime);

		if (player->GetPos() >= 30)
		{
			player->SetPos(board.Length());
			Draw();
			winnerName = player->GetName();
			isGoal = true;
			return;
		}
	}

	player->SetDestination(0);

	for (auto itr = players.begin(); itr != players.end(); ++itr) {
		if (player->GetPos() < itr->GetPos())
		{
			break;
		}
		
		if(player->GetPos() > itr->GetPos())
		{
			precedingPlayer = &(*player);
		}
	}
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

		for (auto Character = players.begin(); Character != players.end(); ++Character)
		{
			if (drawIndex == Character->GetPos())
			{
				cout << Character->GetIcon();
			}
			else
			{
				cout << space;
			}
		}
	}

	cout << end;
};

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
			cout << "一回休み";
		else if (Character->GetNumDice() > 1)
			cout << "サイコロ+1";
		else
			cout << "ふつう";
		cout << "\n\n";
	}
};

void Scene::Result()
{
	cout << winnerName << "がゴール！\n";
	Sleep(WaitTime);
	cout << "到達までにかかった回数 : " << numTurn << "\n";
};