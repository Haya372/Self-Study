#pragma once
#include<iostream>
#include<GL/glut.h>
#include"object.h"
#include"Rect.h"

namespace UpDown {
	class Button :public Rect {
	public:
		Button(GLfloat px, GLfloat py, GLfloat w, GLfloat h);
		bool on_Area(GLfloat mx, GLfloat my);
	};
}