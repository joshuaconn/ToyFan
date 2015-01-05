#include "shape2d.h"

void jdcDrawCircle(float r, pos2f center, unsigned int detail) {
    float angle = 0;
	float a_factor = 2*PI/detail;
	glBegin(GL_POLYGON);
		for(int i=detail; i>0; i--) {
			angle = i*a_factor;
			glVertex3f(sin(angle)*r+center.x,cos(angle)*r+center.y,0.0f);
		}
	glEnd();
}

void jdcDrawCircleOutline(float r, pos2f center, unsigned int detail) {
    float angle = 0;
	float a_factor = 2*PI/detail;
	glBegin(GL_LINE_LOOP);
		for(int i=detail; i>0; i--) {
			angle = i*a_factor;
			glVertex3f(sin(angle)*r+center.x,cos(angle)*r+center.y,0.0f);
		}
	glEnd();
}

void jdcDrawCircle(float r, float x, float y) {
	jdcDrawCircle(r, (pos2f){x, y}, 0x10);
}

void jdcDrawCircle(float r, pos2f center) {
	jdcDrawCircle(r, center, 0x10);
}

void jdcDrawHexagon(float width, pos2f center) {
    jdcDrawCircle(width, center, 6u);
}

void jdcDrawOctagon(float width, pos2f center) {
    jdcDrawCircle(width, center, 8u);
}

void jdcDrawRect(int x1,int y1, int x2, int y2) {
	glBegin(GL_TRIANGLE_STRIP);
		glVertex2i(x1,y1);
		glVertex2i(x2,y1);
		glVertex2i(x1,y2);
		glVertex2i(x2,y2);
	glEnd();
}

void jdcDrawGrid(float x, float y, float z, float w, float h, unsigned int h_units,  unsigned int v_units) {
	float vspacing = h/h_units;
	float hspacing = w/v_units;
	glBegin(GL_LINES);
		for(unsigned int i=0; i<=h_units; i++){
			glVertex3f(x,y,z);
			glVertex3f(x+w,y,z);
			y+=vspacing;
		}
		y-=vspacing;
		for(unsigned int i=0; i<=v_units; i++){
			glVertex3f(x,y,z);
			glVertex3f(x,y-h,z);
			x+=hspacing;
		}
	glEnd();
}
