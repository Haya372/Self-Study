#define _USE_MATH_DEFINES
#include<cmath>
#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include<GL/glut.h>
#include<wchar.h>
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

		reverse(deck_.begin(),deck_.end());
		before_is_joker_ = true;
		//ShuffleDeck();

		int num = deck_[0];		

		/*while (true) {
			if (get(num).first != JOKER)break;
			ShuffleDeck();
			num = deck_[0];
		}
		before_is_joker_ = false;*/
		deck_.erase(deck_.begin());
		used_card_.push_back(num);		

		right_before_card_ = get(num);

	}

	void PlayingCard::DrawCard(int predict) {

		int num = deck_[0];
		deck_.erase(deck_.begin());

		used_card_.push_back(num);

		pair<int, int>drawn_card = get(num);

		int correct = Judge(drawn_card);

		if (correct == JOKER || predict == JOKER) {
			if (correct == predict) {
				//DrawString(L"Everyone Out!!!", g_hDC);
				str_ = "OK!";
			}
			else {
				//DrawString(L"JOKER MISS!!!", g_hDC);
				str_ = "MISS";
			}
		}
		else if (correct == STAY || predict == STAY) {
			if (correct == predict) {
				//DrawString(L"You can choose person who will receive punishment!!", g_hDC);
				str_ = "OK!";
			}
			else {
				//DrawString(L"STAY MISS!!", g_hDC);
				str_ = "MISS";
			}
		}
		else {
			if (correct == predict) {
				//DrawString(L"OK", g_hDC);
				str_ = "OK!";
			}
			else {
				//DrawString(L"MISS!", g_hDC);
				str_ = "MISS";
			}
		}

		//引いたカードがジョーカーでなければ前のカードを更新
		if (correct != JOKER) {
			before_is_joker_ = false;
			right_before_card_ = drawn_card;
		}
		else {
			before_is_joker_ = true;
		}

	}

	void PlayingCard::draw() {

		if (before_is_joker_) {
			draw_Joker();
			return;
		}

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
		draw_num();
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

	void PlayingCard::draw_Joker() {
		glColor3f(0.8, 0, 0.8);
		draw_circle(-1.5, 0.5, 1.5);
	}

	void PlayingCard::DrawString(GLfloat x, GLfloat y, HDC g_hDC) {
		int list = 0;

		if (str_.empty()) {
			return;
		}

		//文字列変換(string => wchat_t)
		wchar_t format[50];
		size_t formatLen = 0;
		mbstowcs_s(&formatLen, format, sizeof(str_), str_.c_str(), _TRUNCATE);

		list = glGenLists(formatLen);

		for (int i = 0; i < formatLen; i++) {
			wglUseFontBitmapsW(g_hDC, format[i], 1, list + (DWORD)i);
		}

		glColor3f(0, 0, 0);
		glRasterPos2f(x, y);
		//ディスプレイリストで描画
		for (int i = 0; i < formatLen; i++) {
			glCallList(list + i);
		}

		//ディスプレイリスト破棄
		glDeleteLists(list, formatLen);
	}

	void PlayingCard::draw_num() {
		glColor3f(1, 1, 1);
		glLineWidth(8);
		if (right_before_card_.second == 1) {
			glBegin(GL_LINES);
			glVertex2f(-1.5, 1);
			glVertex2f(-1.5, 0);
			glVertex2f(-1.5, 1);
			glVertex2f(-1.6, 0.8);
			glVertex2f(-1.65, 0);
			glVertex2f(-1.35, 0);
			glEnd();
		}
		else if (right_before_card_.second == 2) {
			glBegin(GL_LINES);
			glVertex2f(-1.75, 1);
			glVertex2f(-1.25, 1);
			glVertex2f(-1.25, 1);
			glVertex2f(-1.25, 0.5);
			glVertex2f(-1.25, 0.5);
			glVertex2f(-1.75, 0.5);
			glVertex2f(-1.75, 0.5);
			glVertex2f(-1.75, 0);
			glVertex2f(-1.75, 0);
			glVertex2f(-1.25, 0);
			glEnd();
		}
		else if (right_before_card_.second == 3) {
			glBegin(GL_LINES);
			glVertex2f(-1.75, 1);
			glVertex2f(-1.25, 1);
			glVertex2f(-1.25, 1);
			glVertex2f(-1.25, 0);
			glVertex2f(-1.75, 0.5);
			glVertex2f(-1.25, 0.5);
			glVertex2f(-1.75, 0);
			glVertex2f(-1.25, 0);
			glEnd();
		}
		else if (right_before_card_.second == 4) {
			glBegin(GL_LINES);
			glVertex2f(-1.75, 1);
			glVertex2f(-1.75, 0.5);
			glVertex2f(-1.75, 0.5);
			glVertex2f(-1.25, 0.5);
			glVertex2f(-1.25, 1);
			glVertex2f(-1.25, 0);
			glEnd();
		}
		else if (right_before_card_.second == 5) {
			glBegin(GL_LINES);
			glVertex2f(-1.75, 1);
			glVertex2f(-1.25, 1);
			glVertex2f(-1.75, 1);
			glVertex2f(-1.75, 0.5);
			glVertex2f(-1.75, 0.5);
			glVertex2f(-1.25, 0.5);
			glVertex2f(-1.25, 0.5);
			glVertex2f(-1.25, 0);
			glVertex2f(-1.25, 0);
			glVertex2f(-1.75, 0);
			glEnd();
		}
		else if (right_before_card_.second == 6) {
			glBegin(GL_LINES);
			glVertex2f(-1.25, 1);
			glVertex2f(-1.75, 1);
			glVertex2f(-1.75, 1);
			glVertex2f(-1.75, 0.5);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex2f(-1.75, 0.5);
			glVertex2f(-1.25, 0.5);
			glVertex2f(-1.25, 0);
			glVertex2f(-1.75, 0);
			glEnd();
		}
		else if (right_before_card_.second == 7) {
			glBegin(GL_LINES);
			glVertex2f(-1.75, 1);
			glVertex2f(-1.25, 1);
			glVertex2f(-1.25, 1);
			glVertex2f(-1.25, 0);
			glEnd();
		}
		else if (right_before_card_.second == 8) {
			glBegin(GL_LINE_LOOP);
			glVertex2f(-1.75, 1);
			glVertex2f(-1.25, 1);
			glVertex2f(-1.25, 0);
			glVertex2f(-1.75, 0);
			glEnd();
			glBegin(GL_LINES);
			glVertex2f(-1.75, 0.5);
			glVertex2f(-1.25, 0.5);
			glEnd();
		}
		else if (right_before_card_.second == 9) {
			glBegin(GL_LINE_LOOP);
			glVertex2f(-1.75, 1);
			glVertex2f(-1.25, 1);
			glVertex2f(-1.25, 0.5);
			glVertex2f(-1.75, 0.5);
			glEnd();
			glBegin(GL_LINES);
			glVertex2f(-1.25, 0.5);
			glVertex2f(-1.25, 0);
			glEnd();
		}
		else if (right_before_card_.second == 10) {
			glBegin(GL_LINE_LOOP);
			glVertex2f(-1.5, 1);
			glVertex2f(-1, 1);
			glVertex2f(-1, 0);
			glVertex2f(-1.5, 0);
			glEnd();
			glBegin(GL_LINES);
			glVertex2f(-1.75, 1);
			glVertex2f(-1.75, 0);
			glEnd();
		}
		else if (right_before_card_.second == 11) {
			//ちょっと汚い
			glBegin(GL_LINES);
			glVertex2f(-1.25, 1);
			glVertex2f(-1.25, 0.25);
			glEnd();
			glBegin(GL_LINES);
			GLfloat x = -1.5, y = 0.25;
			for (float i = 0.05; i < 1; i += 0.05) {
				glVertex2f(x + 0.25*cos((i - 0.05)*M_PI), y - 0.25*sin((i - 0.05)*M_PI));
				glVertex2f(x + 0.25*cos(i*M_PI), y - 0.25*sin(i*M_PI));
			}
			glEnd();
		}
		else if (right_before_card_.second == 12) {
			GLfloat x = -1.5, y = 0.5;
			glBegin(GL_LINE_LOOP);
			for (float i = 0; i < 2 * M_PI; i += 0.01) {
				glVertex2f(x + 0.25*cos(i), y + 0.5*sin(i));
			}
			glEnd();
			glBegin(GL_LINES);
			glVertex2f(-1.4, 0.2);
			glVertex2f(-1.1, 0);
			glEnd();
		}
		else if (right_before_card_.second == 13) {
			glBegin(GL_LINES);
			glVertex2f(-1.75, 1);
			glVertex2f(-1.75, 0);
			glVertex2f(-1.25, 1);
			glVertex2f(-1.75, 0.45);
			glVertex2f(-1.65, 0.5);
			glVertex2f(-1.25, 0);
			glEnd();
			}
	}
}
