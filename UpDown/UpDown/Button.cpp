#include"Button.h"
#include"object.h"
#include<string>
#include <windows.h>
#include<stdio.h>



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

	bool Button::on_Area(GLfloat mx, GLfloat my) {
		if (mx<x_ || mx>x_ + width_)return false;
		if (my<y_ || my>y_ + height_)return false;
		return true;
	}

	void Button::set_Str(string s, GLfloat r, GLfloat g, GLfloat b) {
		str_ = s;
		str_color_[0] = r;
		str_color_[1] = g;
		str_color_[2] = b;
	}


	void Button::DrawString(HDC g_hDC){
		int list = 0;

		if (str_.empty()){
			return;
		}

		//文字列変換(string => wchat_t)
		wchar_t format[50];
		size_t formatLen = 0;
		mbstowcs_s(&formatLen, format, sizeof(str_), str_.c_str(), _TRUNCATE);

		list = glGenLists(formatLen);

		for (int i = 0; i < formatLen; i++){
			wglUseFontBitmapsW(g_hDC, format[i], 1, list + (DWORD)i);
		}

		float raster_dx = (width_ - 32. * (float)str_.size() * 8. / 600.) / 2.;
		float raster_dy = (height_ - 32. * 8. / 600.) / 2.;

		glColor3fv(str_color_);
		glRasterPos2f(x_ + raster_dx, y_ + raster_dy);
		//ディスプレイリストで描画
		for (int i = 0; i < formatLen; i++){
			glCallList(list + i);
		}

		//ディスプレイリスト破棄
		glDeleteLists(list, formatLen);
	}
}