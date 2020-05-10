#define _USE_MATH_DEFINES
#include<cmath>
#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include<GL/glut.h>
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

	void PlayingCard::draw() {
		if (right_before_card_.first == 0) {
			//SPADE
			draw_Spade();
		}
		else if (right_before_card_.first == 1) {
			//CLOVER
			draw_Clover();
		}
		else if (right_before_card_.first == 2) {
			//HEART
			draw_Heart();
		}
		else if (right_before_card_.first == 3) {
			//DIAMOND
			draw_Dia();
		}
		else if (right_before_card_.first == 4) {
			//JOKER
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

	void PlayingCard::draw_circle(GLfloat x, GLfloat y, float r) {
		glBegin(GL_POLYGON);
		for (float i = 0; i < 2*M_PI; i+=0.1) {
			glVertex2f(x + r * cos(i), y + r * sin(i));
		}
		glEnd();
	}

	void PlayingCard::draw_Spade() {
		glColor3f(0, 0, 0);
		draw_circle(-2.21, 0.3, 0.79);
		draw_circle(-0.79, 0.3, 0.79);
		glBegin(GL_QUADS);
		glVertex2f(-1.5, 0.3);
		glVertex2f(-2.6, 0.985);
		glVertex2f(-1.5, 2);
		glVertex2f(-0.4, 0.985);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex2f(-1.5, 0.3);
		glVertex2f(-1.7, -1);
		glVertex2f(-1.3, -1);
		glEnd();
	}

	void PlayingCard::draw_Clover() {
		glColor3f(0, 0, 0);
		draw_circle(-2.21, 0.3, 0.79);
		draw_circle(-0.79, 0.3, 0.79);
		draw_circle(-1.5, 1.2, 0.79);
		glBegin(GL_TRIANGLES);
		glVertex2f(-1.5, 0.3);
		glVertex2f(-1.7, -1);
		glVertex2f(-1.3, -1);
		glEnd();
	}

	void PlayingCard::draw_Heart() {
		glColor3f(1, 0, 0);
		draw_circle(-2.21, 1, 0.79);
		draw_circle(-0.79, 1, 0.79);
		glBegin(GL_QUADS);
		glVertex2f(-1.5, 1.0);
		glVertex2f(-2.6, 0.315);
		glVertex2f(-1.5, -0.7);
		glVertex2f(-0.4, 0.315);
		glEnd();
	}

	void PlayingCard::draw_Dia() {
		glColor3f(1, 0, 0);
		glBegin(GL_QUADS);
		glVertex2f(-1.5, 2);
		glVertex2f(-0.5625, 0.5);
		glVertex2f(-1.5, -1);
		glVertex2f(-2.4375, 0.5);
		glEnd();
	}
}
