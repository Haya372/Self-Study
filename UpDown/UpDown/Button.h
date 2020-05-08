#pragma once
#include<iostream>
#include<GL/glut.h>
#include"object.h"

namespace UpDown {
	class Button :public Object {
	public:
		Button(GLfloat px, GLfloat py, GLfloat w, GLfloat h);
		void draw();
		void Scaling(GLfloat x, GLfloat y);
		bool on_Area(GLfloat mx, GLfloat my);
	private:
		GLfloat width_, height_;
	};
}