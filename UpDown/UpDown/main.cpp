#include<iostream>
#include<vector>
#include<algorithm>
#include<GL/glut.h>
#include <windows.h>
#include"PlayingCard.h"
#include"Button.h"

#define UP 0
#define DOWN 1
#define STAY 2
#define JOKER 4

#define CORRECTION 150

#define MY_FONT L"ＭＳゴシック"

using namespace std;
using namespace UpDown;

GLuint width = 600, height = 600;

Button Up(1, 2.09, 2.5, 1.55);
Button Down(1, -1.73, 2.5, 1.55);
Button Stay(1, 0.18, 2.5, 1.55);
Button Joker(1, -3.64, 2.5, 1.55);

Button ReturnTo(-2.75, -3.64, 2.5, 1.55);

PlayingCard updown;

HFONT g_hFont;
HDC	g_hDC;

// フォント作成。
void CreateFont(const wchar_t* _pFontName, int _Size)
{
	g_hFont = CreateFontW(
		_Size,				// フォントの高さ
		_Size,				// 平均文字幅
		0,				// 文字送り方向の角度
		0,				// ベースラインの角度
		FW_REGULAR,			// フォントの太さ
		FALSE,				// 斜体にするかどうか
		FALSE,				// 下線を付けるかどうか
		FALSE,				// 取り消し線を付けるかどうか
		SHIFTJIS_CHARSET,		// 文字セットの識別子
		OUT_DEFAULT_PRECIS,		// 出力精度
		CLIP_DEFAULT_PRECIS,		// クリッピング精度
		ANTIALIASED_QUALITY,		// 出力品質
		FIXED_PITCH | FF_MODERN,	// ピッチとファミリ
		_pFontName);			// フォント名

	g_hDC = wglGetCurrentDC();
	SelectObject(g_hDC, g_hFont);
}


void disp() {
	glClear(GL_COLOR_BUFFER_BIT);
	updown.draw();
	updown.DrawString(-2.3, 3, g_hDC);
	updown.DrawRemainedDecks(g_hDC);
	Up.draw();
	Up.DrawString(g_hDC);
	Down.draw();
	Down.DrawString(g_hDC);
	Stay.draw();
	Stay.DrawString(g_hDC);
	Joker.draw();
	Joker.DrawString(g_hDC);
	ReturnTo.draw();
	ReturnTo.DrawString(g_hDC);
	glLoadIdentity();
	glOrtho(-(GLdouble)width / CORRECTION, (GLdouble)width / CORRECTION, -(GLdouble)height / CORRECTION, (GLdouble)height / CORRECTION, -1, 1);
	glutSwapBuffers();
}

void init() {
	glClearColor(1, 1, 1, 1);
	Up.set_color(1, 0, 0);
	Up.set_Str("UP", 0, 0, 0);
	Down.set_color(0., 0.8, 0.);
	Down.set_Str("DOWN", 0, 0, 0);
	Stay.set_color(0, 0, 0.8);
	Stay.set_Str("STAY", 0, 0, 0);
	Joker.set_color(0.8, 0.8, 0.2);
	Joker.set_Str("JOKER", 0, 0, 0);
	ReturnTo.set_color(0.5, 0.5, 0.5);
	ReturnTo.set_Str("BACK", 0, 0, 0);
	updown.Init();
	CreateFont(MY_FONT, 32);
}

void timer(int t) {
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	switch (button) {
	case(GLUT_LEFT_BUTTON):
		if (state == GLUT_DOWN) {
			double px = ((double)x - width / 2) * 2 / CORRECTION;
			double py = -((double)y - height / 2) * 2 / CORRECTION;
			
			if (Up.on_Area(px, py)) {
				updown.DrawCard(UP);
			}
			else if (Down.on_Area(px, py)) {
				updown.DrawCard(DOWN);
			}
			else if (Stay.on_Area(px, py)) {
				updown.DrawCard(STAY);
			}
			else if (Joker.on_Area(px, py)) {
				updown.DrawCard(JOKER);
			}
			else if (ReturnTo.on_Area(px, py)) {
				updown.ReturnJoker();
			}
		}
		break;
	default:
		break;
	}
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	float x = (float)w / width;
	float y = (float)h / height;
	Up.NormalizePos(x, y);
	Up.Scaling(x, y);
	Down.NormalizePos(x, y);
	Down.Scaling(x, y);
	Stay.NormalizePos(x, y);
	Stay.Scaling(x, y);
	Joker.NormalizePos(x, y);
	Joker.Scaling(x, y);
	width = w;
	height = h;
	glutPostRedisplay();
}

void keyboard(unsigned char c, int x, int y) {
	switch (c) {
	case 27:
		exit(0);
		break;
	case 'q':
		exit(0);
		break;
	default:
		break;
	}
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
	glutKeyboardFunc(keyboard);

	init();
	glutMainLoop();
	return 0;
}