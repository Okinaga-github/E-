#include<ctime>
#include<string>
#include<cstdlib>
#include<iostream>

using namespace std;

int battle_count = 0; //
int side; //〇〇側
int koutei, dorei; 
int lose ; //負け
int win ; //勝ち
void put_kd_select(void){ //ランダムに皇帝側と奴隷側を選択
	koutei = dorei = 1;
	win = lose = 0;
	side = battle_count % 2; //乱数発生(0~1)
	battle_count++;
}

class Player{
	friend class battle;

	string name; //名前
	int result; //判定結果
	int win; //勝利
	int lose; //敗北
	int draw; //引き分け

protected:
	int hand; //手

public:
	Player(string n) //コンストラクタ
	{
		name = n;
		win = lose = draw = 0;
	}
	virtual void newHand(void) = 0; //次の手（純粋仮想関数）

	void recordCount(void) //勝敗回数を更新
	{
		switch (result){
		case 0:draw++; break; //引き分け
		case 1:lose++; break; //負け
		case 2:win++; break; //勝ち
		}
	}
	string getName(void) //名前を返す
	{
		return(name);
	}

	void put_record(void) //勝敗数表示
	{
		cout << name << ":" << win << "勝" << lose << "負" << draw << "分けです\n";
	}
	
};



class HumanPlayer :public Player{ //自分

public:
	HumanPlayer(string n) :Player(n){}

	void newHand(void) //次の手
	{
		cin >> hand; //キーボードから読み取り
		//皇帝側の処理
		if (side == 0){
			if (hand == 0){
				if (koutei == 1){
					hand = 0;
					koutei = 0;
				}else if (koutei == 0){
					cout << "皇帝がありません。\n";
					newHand();
				}
			}
			else
				hand = 1;
		}

		//奴隷側の処理
		if (side == 1){
			if (hand == 1){
				if (dorei == 1){
					dorei = 0;
					hand = 2;
				}
				else if (dorei == 0){
					cout << "奴隷がありません。\n";
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

	void newHand(void) //次の手
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
	static string hd[3]; //hand数
	int x = 0, y;
	int total_win=0; //総合勝利
	int total_lose = 0; //総合敗北
public:
	battle(void) //コンストラクタ
	{
		time_t t;
		srand(time(&t) % RAND_MAX); //乱数の値を初期化
	}

	void put_start_message(void) //開始メッセージを表示
	{
		cout << "Eカード開始 \n";
		cout << "　　　　／　　／ /＼/　／＼＼＼\n";
		cout << "    | ／ / ／ | / ＼l | | l／　　＼ | ＼\n";
		cout << "           | ＝ == | == ＝＝　 || ⌒ |\n";
		cout << "           | ゝ ﾟ／／ ゝ ﾟ　ノ || .６ |\n";
		cout << "           | ／／　u　 ￣／ || |\n";
		cout << "           (__っ　　　／ u || _ノ＼\n";
		cout << "           ｜―――――　　 || | ＼\n";
		cout << "          ／ヽ　　二　  　／| / ヽ ＼\n";
		cout << "  ／ | 二二 / ヽ　　　　／  ｜ /     | 二二二＼\n";
		cout << "／   |     /   ヽ　   ／　  | /      |\n";
		cout << "     |  . /  || ヽ　／　 　 | / |    ｜\n";
		cout << "     ｜　/   ||  ＼　       || |      |\n";
		cout << "        / ／ ||    ＼＿＿／ || / ＼　 |\n";
		cout << "       / ／　　　　　　　　　　　　＼ | \n"; 

	}



	void put_battle_message(void) //「カードを出してください」を表示
	{
		if (side == 0)
		cout << "\n\aあなたは皇帝側です。\nカードを出してください";
		else if (side ==1)
			cout << "\n\aあなたは奴隷側です。\nカードを出してください";
		for (int i = 0; i < 2; i++)
			cout << "(" << i << ")" << hd[i+side] << "";
		cout << ";";
		
	}

	void put_hands(const Player &p1, const Player&p2) //プレイヤーの手を表示
	{
		cout << p1.name << "は" << hd[p1.hand] << "で" << p2.name << "は" << hd[p2.hand] << "です\n";
	}

	void judge(Player &p1, Player&p2) // 判定
	{
		p1.result = (p1.hand - p2.hand + 3) % 3; // p1の勝敗
		p2.result = (p2.hand - p1.hand + 3) % 3; // p2の勝敗
	}

	void disp_result(const Player &p1) //判定結果を表示
	{
		switch (p1.result){
		case 0:cout << "引き分けです\n"; break;
		case 1:cout << p1.name << "の負けです\n"; lose++; break;
		case 2:cout << p1.name << "の勝ちです\n"; win++; break;
		}
	}

	void put_total(void) //ゲームの勝敗
	{
		if (win == lose)
			cout << ">-------------引き分け----------<\n";
		else if (win > lose){
			cout << ">---------勝ち----------<\n";
			total_win++;
		}
		else if (lose > win){
			cout << ">---------負け----------<\n";
			total_lose++;
		}
	}

	void put_total_total(void) //総合結果
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

string battle::hd[] = { "皇帝", "市民", "奴隷" };
 

int main(void){
	battle game;
	HumanPlayer user("カイジ"); //人間
	ComPlayer comp("利根川"); //コンピュータ

	game.put_start_message(); //スタートメッセージの表示
	for (int j = 0; j < 5; j++){
		put_kd_select(); //皇帝、奴隷側の選択
	for (int i = 0; i < 3; i++){
		comp.newHand(); //コンピュータの手を生成
		game.put_battle_message(); //「カードを出してください」を表示
		user.newHand(); //ユーザの手を生成(読み込む)

		game.put_hands(user, comp); //手を表示
		game.judge(user, comp); //判定

		game.disp_result(user); //判定結果を表示

		user.recordCount(); //勝敗回数更新
		comp.recordCount(); //勝敗回数更新

	}

	user.put_record(); //人間の結果を表示
	comp.put_record(); //コンピュータの結果を表示
	game.put_total(); //そのゲームの勝敗
}
	game.put_total_total(); //総合結果の表示

	return(0);
}