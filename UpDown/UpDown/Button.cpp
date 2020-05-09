#include"Button.h"
#include"object.h"

namespace UpDown {

	Button::Button(GLfloat px, GLfloat py, GLfloat w, GLfloat h) {
		this->x_ = px;
		this->y_ = py;
		this->width_ = w;
		this->height_ = h;
	}

	bool Button::on_Area(GLfloat mx, GLfloat my) {
		if (mx<x_ || mx>x_ + width_)return false;
		if (my<y_ || my>y_ + height_)return false;
		return true;
	}
}