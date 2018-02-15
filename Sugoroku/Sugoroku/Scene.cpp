#include "Scene.h"

#define numPlayer 4
#define wait 500
#define wait_more 900

Scene::Scene()
{
	//決定的乱数生成(メルセンヌ・ツイスタ)
	random_device rnd;
	mt = mt19937(rnd());
	
	//ダイス用
	diceDist = uniform_int_distribution<int>(1, 6);
	//プレイヤーの順番用
	playerOrderDist = uniform_int_distribution<int>(0, numPlayer);
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
	Sleep(wait);

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

int Scene::DiceRoll()
{
	return diceDist(mt);
};

void Scene::RunnningSequence()
{
	for (;;)
	{
		TimeUpdate();

		//イテレータを生成してリストに登録されたプレイヤー毎に行動する
		for (auto Character = players.begin(); Character != players.end(); ++Character)
		{
			cout << Character->GetName() << "の手番です\n";

			if (Character->IsHuman())
			{
				cout << "Enterキーでサイコロを振ります\n";
				getchar();
			}

			int roll = 0;
			int sum = 0;

			if (Character->GetTurn() < 1)
				Character->AddTurn();

			cout << "出た目の数は...";
			roll = DiceRoll();
			sum += roll;
			cout << sum;
			for (int i = 1; i < Character->GetNumDice(); i++)
			{
				Sleep(wait);
				roll = DiceRoll();
				sum += roll;

				if (Character->GetNumDice() > 1)
				{
					cout << "+" << roll;
				}
			}
			if (Character->GetNumDice() > 1)
			{
				cout << " = " << sum;
			}
			cout << "です\n";
			Sleep(wait);
			Character->ResetNumDice();

			//動けるかどうか
			if (Character->CanMove())
			{
				//移動
				Character->Move(sum);
				Draw();
				Sleep(wait_more);

				//移動先のマスの効果適用
				board.GetSquare(Character->GetPos()).Effect(&(*Character));
				if (board.GetSquare(Character->GetPos()).GetType() != sqStat::Blank)
					Sleep(wait_more);
				Draw();

				//ゴール(効果マスでゴールする可能性があるのでここで取る)
				if (Character->GetPos() >= 30)
				{
					Character->SetPos(board.Length());
					Draw();
					WinnerName = Character->GetName();
					return;
				}
			}
			else
			{
				cout << "一回休みです";
				Draw();
			}
		}
	}
};

void Scene::DrawFrame(string first, string middle, string end, int time)
{
	cout << first;
	for (int j = 0; j < time; j++)
	{
		cout << middle;
	}
	cout << end;
};

void Scene::DrawPlayerSpace(string first, string middle, string space, string end, int time)
{
	cout << first;
	for (int j = 0; j <= time - 1; j++)
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

	cout << middle << end;
};

void Scene::Draw()
{
	drawIndex = 0;

	system("cls");

	DrawFrame("┌", "──┬", "──┐\n", 9);

	for (int i = 0; i < 2; i++)
	{
		DrawPlayerSpace("", "│", " ", "\n", 10);
		DrawFrame("├", "──┼", "──┤\n", 9);
	}

	DrawPlayerSpace("", "│", " ", "\n", 10);
	DrawFrame("└", "──┴", "──┘\n", 9);

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
	cout << WinnerName << "がゴール！\n";
	Sleep(wait);
	cout << "到達までにかかった回数 : " << time << "\n";
};