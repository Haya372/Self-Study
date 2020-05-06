#include"object.h"

namespace UpDown {

	Button::Button(GLfloat px, GLfloat py, GLfloat w, GLfloat h) {
		this->x = px;
		this->y = py;
		this->width = w;
		this->height = h;
	}

	void Button::draw_Button() {
		glPushMatrix();
		glColor3fv(color);
		glBegin(GL_QUADS);
		glVertex2f(x, y);
		glVertex2f(x + width, y);
		glVertex2f(x + width, y + height);
		glVertex2f(x, y + height);
		glEnd();
		glPopMatrix();
	}

	void Button::set_color(GLfloat r, GLfloat g, GLfloat b) {
		this->color[0] = r;
		this->color[1] = g;
		this->color[2] = b;
	}

	void Button::Translate(GLfloat dx, GLfloat dy) {
		x += dx;
		y += dy;
	}

	void Button::scaling(GLfloat x) {
		width *= x;
		height *= x;
	}

	bool Button::on_Area(GLfloat mx, GLfloat my) {
		if (mx<x || mx>x + width)return false;
		if (my<y || my>y + height)return false;
		return true;
	}
}