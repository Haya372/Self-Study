#include<iostream>
#include<vector>
#include<algorithm>
#include<GL/glut.h>
#include"PlayingCard.h"
#include"object.h"

#define UP 0
#define DOWN 1
#define STAY 2
#define JOKER 4

#define CORRECTION 150

using namespace std;
using namespace UpDown;

GLuint width = 300, height = 400;

Button Up(0, 0, 1, 1);
PlayingCard updown;

void disp() {
	glClear(GL_COLOR_BUFFER_BIT);
	Up.draw_Button();
	glLoadIdentity();
	glOrtho(-(GLdouble)width / CORRECTION, (GLdouble)width / CORRECTION, -(GLdouble)height / CORRECTION, (GLdouble)height / CORRECTION, -1, 1);
	glutSwapBuffers();
}

void init() {
	glClearColor(1, 1, 1, 1);
	Up.set_color(1, 0, 0);
	updown.Init();
}

void timer(int t) {
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	switch (button) {
	case(GLUT_LEFT_BUTTON):
		if (state == GLUT_DOWN) {
			double p_x = ((double)x - width / 2) * 2 / CORRECTION;
			double p_y = -((double)y - height / 2) * 2 / CORRECTION;
			
			if (Up.on_Area(p_x, p_y)) {
				updown.DrawCard(UP);
			}
		}
		break;
	default:
		break;
	}
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	glutPostRedisplay();
}


int main(int argc, char**argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("UpDown");

	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutTimerFunc(100, timer, 0);
	glutDisplayFunc(disp);

	init();
	glutMainLoop();
	return 0;
}