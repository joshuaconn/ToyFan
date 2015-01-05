#include <algorithm>
#include <math.h>
#include "GL/glut.h"

#define PI 3.1415

// DATA TYPES
struct pos2i   { int x; int y; };
struct pos2f   { float x; float y; };

void jdcDrawGrid(
	float x,
	float y,
	float z,
	float w,
	float h,
	unsigned int h_units,
	unsigned int v_units);


void jdcDrawCircle(float r, pos2f center, unsigned int detail);
void jdcDrawCircle(float r, float x, float y);
void jdcDrawCircleOutline(float r, pos2f center, unsigned int detail);
void jdcDrawHexagon(float width, pos2f center);
void jdcDrawOctagon(float width, pos2f center);
void jdcDrawRect(int x1,int y1, int x2, int y2);
