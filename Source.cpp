#include<ctime>
#include<string>
#include<cstdlib>
#include<iostream>

using namespace std;

int battle_count = 0; //
int side; //�Z�Z��
int koutei, dorei; 
int lose ; //����
int win ; //����
void put_kd_select(void){ //�����_���ɍc�鑤�Ɠz�ꑤ��I��
	koutei = dorei = 1;
	win = lose = 0;
	side = battle_count % 2; //��������(0~1)
	battle_count++;
}

class Player{
	friend class battle;

	string name; //���O
	int result; //���茋��
	int win; //����
	int lose; //�s�k
	int draw; //��������

protected:
	int hand; //��

public:
	Player(string n) //�R���X�g���N�^
	{
		name = n;
		win = lose = draw = 0;
	}
	virtual void newHand(void) = 0; //���̎�i�������z�֐��j

	void recordCount(void) //���s�񐔂��X�V
	{
		switch (result){
		case 0:draw++; break; //��������
		case 1:lose++; break; //����
		case 2:win++; break; //����
		}
	}
	string getName(void) //���O��Ԃ�
	{
		return(name);
	}

	void put_record(void) //���s���\��
	{
		cout << name << ":" << win << "��" << lose << "��" << draw << "�����ł�\n";
	}
	
};



class HumanPlayer :public Player{ //����

public:
	HumanPlayer(string n) :Player(n){}

	void newHand(void) //���̎�
	{
		cin >> hand; //�L�[�{�[�h����ǂݎ��
		//�c�鑤�̏���
		if (side == 0){
			if (hand == 0){
				if (koutei == 1){
					hand = 0;
					koutei = 0;
				}else if (koutei == 0){
					cout << "�c�邪����܂���B\n";
					newHand();
				}
			}
			else
				hand = 1;
		}

		//�z�ꑤ�̏���
		if (side == 1){
			if (hand == 1){
				if (dorei == 1){
					dorei = 0;
					hand = 2;
				}
				else if (dorei == 0){
					cout << "�z�ꂪ����܂���B\n";
					newHand();
				}
			}
			else
				hand = 1;
		}
			
	}

};

class ComPlayer :public Player{ //CPU

public:
	ComPlayer(string n) :Player(n){}

	void newHand(void) //���̎�
	{
		if (side == 1){
			if (koutei == 1){
				if (rand() % 4 == 0){
					hand = 1;
				}
				else {
					hand = 0;
					koutei = 0;
				}
			}
			else hand = 1;
		}
		else if(side == 0){
			if (dorei == 1){
				if (rand() % 4 == 0){
					hand = 2;
					dorei = 0;
				}
				else{
					hand = 1;
				}
			}
			else hand = 1;
		}
	}
};

class battle{
	static string hd[3]; //hand��
	int x = 0, y;
	int total_win=0; //��������
	int total_lose = 0; //�����s�k
public:
	battle(void) //�R���X�g���N�^
	{
		time_t t;
		srand(time(&t) % RAND_MAX); //�����̒l��������
	}

	void put_start_message(void) //�J�n���b�Z�[�W��\��
	{
		cout << "E�J�[�h�J�n \n";
		cout << "�@�@�@�@�^�@�@�^ /�_/�@�^�_�_�_\n";
		cout << "    | �^ / �^ | / �_l | | l�^�@�@�_ | �_\n";
		cout << "           | �� == | == �����@ || �� |\n";
		cout << "           | �T ߁^�^ �T ߁@�m || .�U |\n";
		cout << "           | �^�^�@u�@ �P�^ || |\n";
		cout << "           (__���@�@�@�^ u || _�m�_\n";
		cout << "           �b�\�\�\�\�\�@�@ || | �_\n";
		cout << "          �^�R�@�@��@  �@�^| / �R �_\n";
		cout << "  �^ | ��� / �R�@�@�@�@�^  �b /     | ����_\n";
		cout << "�^   |     /   �R�@   �^�@  | /      |\n";
		cout << "     |  . /  || �R�@�^�@ �@ | / |    �b\n";
		cout << "     �b�@/   ||  �_�@       || |      |\n";
		cout << "        / �^ ||    �_�Q�Q�^ || / �_�@ |\n";
		cout << "       / �^�@�@�@�@�@�@�@�@�@�@�@�@�_ | \n"; 

	}



	void put_battle_message(void) //�u�J�[�h���o���Ă��������v��\��
	{
		if (side == 0)
		cout << "\n\a���Ȃ��͍c�鑤�ł��B\n�J�[�h���o���Ă�������";
		else if (side ==1)
			cout << "\n\a���Ȃ��͓z�ꑤ�ł��B\n�J�[�h���o���Ă�������";
		for (int i = 0; i < 2; i++)
			cout << "(" << i << ")" << hd[i+side] << "";
		cout << ";";
		
	}

	void put_hands(const Player &p1, const Player&p2) //�v���C���[�̎��\��
	{
		cout << p1.name << "��" << hd[p1.hand] << "��" << p2.name << "��" << hd[p2.hand] << "�ł�\n";
	}

	void judge(Player &p1, Player&p2) // ����
	{
		p1.result = (p1.hand - p2.hand + 3) % 3; // p1�̏��s
		p2.result = (p2.hand - p1.hand + 3) % 3; // p2�̏��s
	}

	void disp_result(const Player &p1) //���茋�ʂ�\��
	{
		switch (p1.result){
		case 0:cout << "���������ł�\n"; break;
		case 1:cout << p1.name << "�̕����ł�\n"; lose++; break;
		case 2:cout << p1.name << "�̏����ł�\n"; win++; break;
		}
	}

	void put_total(void) //�Q�[���̏��s
	{
		if (win == lose)
			cout << ">-------------��������----------<\n";
		else if (win > lose){
			cout << ">---------����----------<\n";
			total_win++;
		}
		else if (lose > win){
			cout << ">---------����----------<\n";
			total_lose++;
		}
	}

	void put_total_total(void) //��������
	{
		if (total_win == total_lose)
			cout << ">-------------DRAW----------<\n";
		else if (total_win > total_lose){
			cout << ">---------YOU WIN----------<\n";
		}
		else if (total_lose > total_win){
			cout << ">---------YOU LOSE----------<\n";
		}
	}

};

string battle::hd[] = { "�c��", "�s��", "�z��" };
 

int main(void){
	battle game;
	HumanPlayer user("�J�C�W"); //�l��
	ComPlayer comp("������"); //�R���s���[�^

	game.put_start_message(); //�X�^�[�g���b�Z�[�W�̕\��
	for (int j = 0; j < 5; j++){
		put_kd_select(); //�c��A�z�ꑤ�̑I��
	for (int i = 0; i < 3; i++){
		comp.newHand(); //�R���s���[�^�̎�𐶐�
		game.put_battle_message(); //�u�J�[�h���o���Ă��������v��\��
		user.newHand(); //���[�U�̎�𐶐�(�ǂݍ���)

		game.put_hands(user, comp); //���\��
		game.judge(user, comp); //����

		game.disp_result(user); //���茋�ʂ�\��

		user.recordCount(); //���s�񐔍X�V
		comp.recordCount(); //���s�񐔍X�V

	}

	user.put_record(); //�l�Ԃ̌��ʂ�\��
	comp.put_record(); //�R���s���[�^�̌��ʂ�\��
	game.put_total(); //���̃Q�[���̏��s
}
	game.put_total_total(); //�������ʂ̕\��

	return(0);
}