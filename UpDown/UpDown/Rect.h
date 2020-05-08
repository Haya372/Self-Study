#pragma on
#include"object.h"
#include<GL/glut.h>

namespace UpDown {
	class Rect :public Object {
	public:
		void draw();
		void Scaling(GLfloat x, GLfloat y);
	protected:
		GLfloat width_, height_;
	};
}