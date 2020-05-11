#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<GL/glut.h>
#include<Windows.h>

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
		void draw();
		void DrawString(GLfloat x, GLfloat y, HDC g_hDC);
	private:
		pair<int, int>right_before_card_;
		vector<int> deck_;
		vector<int> used_card_;
		bool before_is_joker_;
		string str_;
		pair<int, int>get(int num);
		int Judge(pair<int, int>card);
		void draw_circle(GLfloat x, GLfloat y, float r);
		void draw_Spade();
		void draw_Clover();
		void draw_Heart();
		void draw_Dia();
		void draw_Joker();
		void draw_num();
	};
}
