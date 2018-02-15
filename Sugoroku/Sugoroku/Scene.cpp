#include "Scene.h"

#define numPlayer 4
#define wait 500
#define wait_more 900

Scene::Scene()
{
	//����I��������(�����Z���k�E�c�C�X�^)
	random_device rnd;
	mt = mt19937(rnd());
	
	//�_�C�X�p
	diceDist = uniform_int_distribution<int>(1, 6);
	//�v���C���[�̏��ԗp
	playerOrderDist = uniform_int_distribution<int>(0, numPlayer);
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

		//�C�e���[�^�𐶐����ă��X�g�ɓo�^���ꂽ�v���C���[���ɍs������
		for (auto Character = players.begin(); Character != players.end(); ++Character)
		{
			cout << Character->GetName() << "�̎�Ԃł�\n";

			if (Character->IsHuman())
			{
				cout << "Enter�L�[�ŃT�C�R����U��܂�\n";
				getchar();
			}

			int roll = 0;
			int sum = 0;

			if (Character->GetTurn() < 1)
				Character->AddTurn();

			cout << "�o���ڂ̐���...";
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
			cout << "�ł�\n";
			Sleep(wait);
			Character->ResetNumDice();

			//�����邩�ǂ���
			if (Character->CanMove())
			{
				//�ړ�
				Character->Move(sum);
				Draw();
				Sleep(wait_more);

				//�ړ���̃}�X�̌��ʓK�p
				board.GetSquare(Character->GetPos()).Effect(&(*Character));
				if (board.GetSquare(Character->GetPos()).GetType() != sqStat::Blank)
					Sleep(wait_more);
				Draw();

				//�S�[��(���ʃ}�X�ŃS�[������\��������̂ł����Ŏ��)
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
				cout << "���x�݂ł�";
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

	DrawFrame("��", "������", "������\n", 9);

	for (int i = 0; i < 2; i++)
	{
		DrawPlayerSpace("", "��", " ", "\n", 10);
		DrawFrame("��", "������", "������\n", 9);
	}

	DrawPlayerSpace("", "��", " ", "\n", 10);
	DrawFrame("��", "������", "������\n", 9);

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
	cout << WinnerName << "���S�[���I\n";
	Sleep(wait);
	cout << "���B�܂łɂ��������� : " << time << "\n";
};