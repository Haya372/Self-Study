#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include"PlayingCard.h"

#define UP 0
#define DOWN 1
#define STAY 2
#define JOKER 4

using namespace std;


namespace UpDown {
	void PlayingCard::Init() {

		deck_.clear();
		used_card_.clear();

		for (int i = 0; i < 54; i++) {
			deck_.push_back(i);
		}

		ShuffleDeck();

		int num = deck_[0];
		deck_.erase(deck_.begin());

		used_card_.push_back(num);

		right_before_card_ = get(num);
		cout << right_before_card_.second << endl;

	}

	void PlayingCard::DrawCard(int predict) {

		int num = deck_[0];
		deck_.erase(deck_.begin());

		used_card_.push_back(num);

		pair<int, int>drawn_card = get(num);

		int correct = Judge(drawn_card);

		if (correct == JOKER || predict == JOKER) {
			if (correct == predict) {
				cout << "Everyone Out!!!" << endl;
			}
			else {
				cout << "JOKER MISS!!!" << endl;
			}
		}
		else if (correct == STAY || predict == STAY) {
			if (correct == predict) {
				cout << "You can choose person who will receive punishment!!" << endl;
			}
			else {
				cout << "STAY MISS!!" << endl;
			}
		}
		else {
			if (correct == predict) {
				cout << "OK" << endl;
			}
			else {
				cout << "MISS!" << endl;
			}
		}

		//引いたカードがジョーカーでなければ前のカードを更新
		if (correct != JOKER) {
			right_before_card_ = drawn_card;
			cout << right_before_card_.second << endl;
		}

	}

	void PlayingCard::ShuffleDeck() {

		random_device seed_gen;
		mt19937 engine(seed_gen());
		shuffle(deck_.begin(), deck_.end(), engine);

	}

	pair<int, int> PlayingCard::get(int num) {
		//Joker
		if (num >= 52) {
			return pair<int, int>(JOKER, num % 52);
		}

		int mark = num / 13;
		int card_num = (num % 13) + 1;
		return pair<int, int>(mark, card_num);
	}

	int PlayingCard::Judge(pair<int, int>card) {
		if (card.first == JOKER)return JOKER;
		if (card.second < right_before_card_.second - 1)return DOWN;
		else if (card.second > right_before_card_.second + 1)return UP;
		else return STAY;
	}
}
