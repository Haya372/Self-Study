#include"Rect.h"
#include<GL/glut.h>

namespace UpDown {

	void Rect::draw() {
		glPushMatrix();
		glColor3fv(color_);
		glBegin(GL_QUADS);
		glVertex2f(x_, y_);
		glVertex2f(x_ + width_, y_);
		glVertex2f(x_ + width_, y_ + height_);
		glVertex2f(x_, y_ + height_);
		glEnd();
		glPopMatrix();
	}

	void Rect::Scaling(GLfloat x, GLfloat y) {
		if (y < 0)y = x;
		width_ *= x;
		height_ *= y;
	}

}
