#include "Scene.h"

#define NUM_PLAYER 4
#define WAIT_TIME 500
#define WAIT_TIME_LONG 900
#define BOARD_LENGTH 40

Scene::Scene()
{
	//����I��������(�����Z���k�E�c�C�X�^)
	random_device rnd;
	mt = mt19937(rnd());
	
	//�_�C�X�p
	diceDist = uniform_int_distribution<int>(1, 6);
	//�v���C���[�̏��ԗp
	playerOrderDist = uniform_int_distribution<int>(0, NUM_PLAYER);
	//�}�X�����p
	squareStateDist = uniform_int_distribution<int>(0, NUM_SQUARE_TYPE);
	
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

		//�C�e���[�^�𐶐����ă��X�g�ɓo�^���ꂽ�v���C���[���ɍs������
		for (auto player = players.begin(); player != players.end(); ++player)
		{
			DrawLineAtIntervals(player->GetName() + "�̎�Ԃł�\n", WAIT_TIME);

			if (player->CanMove())
			{
				int numRollOfDice = RollDice(&(*player));

				ProcessMovement(&(*player), numRollOfDice);
			}
			else
			{
				cout << "���x�݂ł�";
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

int Scene::RollDice(Player* player)
{
	if (player->IsHuman())
	{
		cout << "Enter�L�[�ŃT�C�R����U��܂�\n";
		getchar();
	}

	DrawLineAtIntervals("�o���ڂ̐���...", WAIT_TIME);

	int roll = 0;
	int sum = 0;

	//�T�C�R���̐������U��
	for (int i = 0; i < player->GetNumDice(); i++)
	{
		if (i > 0)
		{
			DrawLineAtIntervals(" + ", WAIT_TIME);
		}

		roll = diceDist(mt);
		sum += roll;
		DrawLineAtIntervals(std::to_string(roll), WAIT_TIME);
	}

	if (player->GetNumDice() > 1)
	{
		cout << " = " << sum;

		player->ResetNumDice();
	}
	
	DrawLineAtIntervals("�ł�\n", WAIT_TIME);

	return sum;
};

void Scene::ProcessMovement(Player* player, int numRollOfDice)
{
	//�ړ�(1�}�X���ړ����鉉�o)
	MovePlayerByStep(player, numRollOfDice, 1);

	int playerPos = player->GetPos();

	//�ړ���̃}�X�̌��ʓK�p
	board.GetSquare(playerPos).ApplyEffect(&(*player), precedingPlayer);

	if (board.GetSquare(playerPos).GetType() != sqStat::Blank)
	{
		Sleep(WAIT_TIME_LONG);

		//�O�i�E��ރ}�X�ɓ����Ă����ꍇ�A���̕�����1�}�X���ړ�
		if (player->GetDestination() > 0)
		{
			MovePlayerByStep(player, player->GetDestination(), 1);
		}
		else if (player->GetDestination() < 0)
		{
			MovePlayerByStep(player, -player->GetDestination(), -1);
		}
	}

	//�s�����I����O�ɂ��̃v���C���[���擪���s���Ă��邩�m�F����
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
			Draw();
			
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
		{
			cout << "���x��";
		}
		else if (Character->GetNumDice() > 1)
		{
			cout << "�T�C�R��+1";
		}
		else
		{
			cout << "�ӂ�";
		}

		cout << "\n\n";
	}
};

void Scene::Result()
{
	DrawLineAtIntervals(winnerName + "���S�[���I\n", WAIT_TIME);
	cout << "���B�܂łɂ��������� : " << numTurn << "\n";
};