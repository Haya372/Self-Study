#pragma once
#include<iostream>
#include<GL/glut.h>

namespace UpDown {
	class Button {
	public:
		Button(GLfloat px, GLfloat py, GLfloat w, GLfloat h);
		void draw_Button();
		void set_color(GLfloat r, GLfloat g, GLfloat b);
		void Translate(GLfloat dx, GLfloat dy);
		void scaling(GLfloat x, GLfloat y);
		void reshape(GLfloat x, GLfloat y);
		bool on_Area(GLfloat mx, GLfloat my);
	private:
		GLfloat x, y, width, height;
		GLfloat color[3] = { 0,0,0 };
	};
}