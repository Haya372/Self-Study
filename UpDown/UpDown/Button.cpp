#include"Button.h"
#include"object.h"

namespace UpDown {

	Button::Button(GLfloat px, GLfloat py, GLfloat w, GLfloat h) {
		this->x_ = px;
		this->y_ = py;
		this->width_ = w;
		this->height_ = h;
	}

	void Button::draw() {
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

	void Button::Scaling(GLfloat x, GLfloat y) {
		if (y < 0)y = x;
		width_ *= x;
		height_ *= y;
	}

	bool Button::on_Area(GLfloat mx, GLfloat my) {
		if (mx<x_ || mx>x_ + width_)return false;
		if (my<y_ || my>y_ + height_)return false;
		return true;
	}
}