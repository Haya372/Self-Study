#include"object.h"

namespace UpDown {

	void Object::set_color(GLfloat r, GLfloat g, GLfloat b) {
		color_[0] = r;
		color_[1] = g;
		color_[2] = b;
	}

	void Object::Translate(GLfloat dx, GLfloat dy) {
		x_ += dx;
		y_ += dy;
	}

	void Object::NormalizePos(GLfloat x, GLfloat y) {
		x_ *= x;
		y_ *= y;
	}

}