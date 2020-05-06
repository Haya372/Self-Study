#pragma once
#include<iostream>
#include<vector>
#include<algorithm>

#define UP 0
#define DOWN 1
#define STAY 2
#define JOKER 4

using namespace std;

namespace UpDown {
	class PlayingCard {
	public:
		void ShuffleDeck();
		void Init();
		void DrawCard(int predict);
	private:
		pair<int, int>right_before_card_;
		vector<int> deck_;
		vector<int> used_card_;
		pair<int, int>get(int num);
		int Judge(pair<int, int>card);
	};
}
