#pragma once
#include<iostream>
#include<GL/glut.h>

namespace UpDown {
	class Object {
	public:
		virtual void draw() = 0;
		void set_color(GLfloat r, GLfloat g, GLfloat b);
		void Translate(GLfloat dx, GLfloat dy);
		virtual void Scaling(GLfloat x, GLfloat y) = 0;
		void NormalizePos(GLfloat x, GLfloat y);
	protected:
		GLfloat x_, y_;
		GLfloat color_[3] = { 0,0,0 };
	};
}