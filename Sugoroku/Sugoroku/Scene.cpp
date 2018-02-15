#include "Scene.h"

#define NumPlayer 4
#define WaitTime 500
#define WaitTime_Long 900

Scene::Scene()
{
	//����I��������(�����Z���k�E�c�C�X�^)
	random_device rnd;
	mt = mt19937(rnd());
	
	//�_�C�X�p
	diceDist = uniform_int_distribution<int>(1, 6);
	//�v���C���[�̏��ԗp
	playerOrderDist = uniform_int_distribution<int>(0, NumPlayer);
	//�}�X�����p
	squareStateDist = uniform_int_distribution<int>(0, sqStat::Type::DoubleUp);
	
	//�v���C���[�����Ə�����
	string name;
	cout << "�v���C���[�̖��O��ݒ肵�܂�\n ���O : ";
	cin >> name;

	char icon;
	cout << "\n���ɁA " << name << " ����̃A�C�R����ݒ肵�܂�\n �A�C�R�� : ";
	cin >> icon;

	cout << "�Q�[�����n�܂�܂�";
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

		//�C�e���[�^�𐶐����ă��X�g�ɓo�^���ꂽ�v���C���[���ɍs������
		for (auto player = players.begin(); player != players.end(); ++player)
		{
			cout << player->GetName() << "�̎�Ԃł�\n";

			Sleep(WaitTime);

			if (player->CanMove())
			{
				int numRollOfDice = RollDice(&(*player));

				ProcessMovement(&(*player), numRollOfDice);
			}
			else
			{
				cout << "���x�݂ł�";
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
		cout << "Enter�L�[�ŃT�C�R����U��܂�\n";
		getchar();
	}

	int roll = 0;
	int sum = 0;

	if (player->GetTurn() < 1)
		player->AddTurn();

	cout << "�o���ڂ̐���...";
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

	cout << "�ł�\n";
	Sleep(WaitTime);

	return sum;
};

void Scene::ProcessMovement(Player* player, int numRollOfDice)
{
	//�ړ�(1�}�X���ړ����鉉�o)
	MovePlayerByStep(player, numRollOfDice, 1);

	//�ړ���̃}�X�̌��ʓK�p
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

	DrawRowFrame("��", "������������", "������������\n", 9);

	for (int i = 0; i < 2; i++)
	{
		DrawPlayerSpace("", "�� ", " ", "��\n", 10);
		DrawRowFrame("��", "������������", "������������\n", 9);
	}

	DrawPlayerSpace("", "�� ", " ", "��\n", 10);
	DrawRowFrame("��", "������������", "������������\n", 9);

	for (auto Character = players.begin(); Character != players.end(); ++Character)
	{
		cout << "\n " << Character->GetName() << " : ";
		if (!Character->CanMove())
			cout << "���x��";
		else if (Character->GetNumDice() > 1)
			cout << "�T�C�R��+1";
		else
			cout << "�ӂ�";
		cout << "\n\n";
	}
};

void Scene::Result()
{
	cout << winnerName << "���S�[���I\n";
	Sleep(WaitTime);
	cout << "���B�܂łɂ��������� : " << numTurn << "\n";
};