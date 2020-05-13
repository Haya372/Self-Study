#pragma once
#include<iostream>
#include<string>
#include<GL/glut.h>
#include <windows.h>
#include"object.h"
#include"Rect.h"

using namespace std;

namespace UpDown {
	class Button :public Rect {
	public:
		Button(GLfloat px, GLfloat py, GLfloat w, GLfloat h);
		void draw();
		bool on_Area(GLfloat mx, GLfloat my);
		void set_Str(string s, GLfloat r, GLfloat g, GLfloat b);
		void DrawString(HDC g_hDC);
	private:
		string str_;
		GLfloat str_color_[3];
	};
}