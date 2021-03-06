// TOY FAN++++++++++++++++++++++++++++++++++++++++++++
// Author: Joshua Conn
// VERY simple simulation of a box fan
////////////////////////////////////////////////////////////////////////////////

// INCLUDES
////////////////////////////////////////////////////////////////////////////////
//#include <glut.h>
// #include <algorithm>
#include "color.h"
#include "shape2d.h"


// CONSTANTS
////////////////////////////////////////////////////////////////////////////////
#define SPEED_DELTA 0.02
#define MAX_SPEED 0.15
#define MAX_BLADE_WDT 32
#define MIN_BLADE_WDT 4
#define MAX_BLADE_LEN 64
#define MIN_BLADE_LEN 32

// PSUEDO FUNCTIONS
#define CALC_BLADE_SPACING blade_spacing = 360/blades;

// Types
////////////////////////////////////////////////////////////////////////////////
typedef enum { BOX, CIRCULAR } Grill_type;

// GLOBALS
////////////////////////////////////////////////////////////////////////////////
pos2i window_corner = { 400, 400 };
bool stretch_image = false;
bool center_image = true; //meaningless if stretch_image is true
int img_len = 400;
pos2i mousePos;
pos2i cursorPos;

float x_axis = 0, y_axis = 0;
float r = 0;
float speed = 0;

unsigned short blades = 5;
float blade_spacing;
float blade_len = MAX_BLADE_LEN;
float blade_wdt = 25;
color3f blade_col;
color3f grate_col;
color3f motor_col;
Grill_type cur_grill_type = BOX;
color3f bkg_col = black;
color3f cursorCol = white;

color3f jdcPalletColors[] =
	{beige,brown,burgundy,red,orange,yellow,lime,green,
	teal,blue,purple,pink,cyan,white,gray};
short jdcNumPalletColors = 16;


// just for my son, Christian who requested this feature -
// draws frowning faces on each of the fan blades
bool frowning_fan_faces = false;

int motor_radius = 10;

void jdcDrawFanBlade(float x, float y, float z, float l, float w);
void jdcDrawCursor(pos2i pos);
void jdcDrawCursor(int x, int y);
void jdcDrawCursor();
void jdcDrawVPallet();

void setColor(color3f c);

////////////////////////////////////////////////////////////////////////////////
//FUNCTION DEFINITIONS
////////////////////////////////////////////////////////////////////////////////

void jdcDrawBoxGrill() {
    glLineWidth(2);
	setColor(grate_col);
	jdcDrawGrid(
             x_axis-MAX_BLADE_LEN,
             y_axis-MAX_BLADE_LEN,
             1,
             MAX_BLADE_LEN*2,
             MAX_BLADE_LEN*2, 32, 16);
	glLineWidth(8);
	jdcDrawGrid(
            x_axis-MAX_BLADE_LEN,
            y_axis-MAX_BLADE_LEN,
            1,
            MAX_BLADE_LEN*2,
            MAX_BLADE_LEN*2, 1, 1);

	glColor3f(1,1,1);
	glLineWidth(1);
}

void jdcDrawCircularGrill() {
    float diag = MAX_BLADE_LEN/sqrt(2);
    setColor(grate_col);
    pos2f fan_center = {x_axis,y_axis};
    glLineWidth(8);
    jdcDrawCircleOutline(MAX_BLADE_LEN+1, fan_center, 0x20);
    glLineWidth(2);
    jdcDrawCircleOutline(MAX_BLADE_LEN*0.75, fan_center, 0x20);
    jdcDrawCircleOutline(MAX_BLADE_LEN*0.50, fan_center, 0x20);
    jdcDrawCircleOutline(MAX_BLADE_LEN*0.25, fan_center, 0x10);
    glBegin(GL_LINES);
        glVertex2i(x_axis,y_axis+MAX_BLADE_LEN);
        glVertex2i(x_axis,y_axis-MAX_BLADE_LEN);
        glVertex2i(x_axis+MAX_BLADE_LEN,y_axis);
        glVertex2i(x_axis-MAX_BLADE_LEN,y_axis);
        glVertex2i(x_axis+diag,y_axis+diag);
        glVertex2i(x_axis-diag,y_axis-diag);
        glVertex2i(x_axis+diag,y_axis-diag);
        glVertex2i(x_axis-diag,y_axis+diag);
    glEnd();
    glLineWidth(1);
}

void jdcDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

		glTranslatef(x_axis,y_axis,0.0);

        //Motion blur circle
		if(speed>=MAX_SPEED) {
			setColor(mix(bkg_col,blade_col,0.6));
			jdcDrawCircle(blade_len,0,0);
		}

		glRotatef(r,0.0,0.0,1.0);
		for(short b=1;b<blades;b++){
			jdcDrawFanBlade(0,0,0,blade_len,blade_wdt);
			glRotatef( 360/blades,0.0,0.0,1.0);
		}
		jdcDrawFanBlade(0,0,0,blade_len,blade_wdt);


	glPopMatrix();

	setColor(motor_col);
	jdcDrawCircle(motor_radius,x_axis,y_axis);
	glColor3f(
		motor_col.r*0.8,
		motor_col.g*0.8,
		motor_col.b*0.8);
	jdcDrawCircle(motor_radius*0.9,x_axis,y_axis);

	//jdcDrawBoxGrill();
	switch(cur_grill_type) {
        case BOX:
            jdcDrawBoxGrill();
            break;
        default:
            jdcDrawCircularGrill();
    }

	jdcDrawVPallet();

	jdcDrawCursor();

	glutSwapBuffers();
}

void jdcReshapeWindow(int width, int height) {
	window_corner.x=width;
	window_corner.y=height;

	if (stretch_image)
	{
		glViewport(0,0,width,height);
	}
	else
	{
		img_len = std::min(width,height);
		if(center_image)
		{
			if(img_len<height) {
				glViewport(0,(height-img_len)/2,img_len,img_len);
			} else {
				glViewport((width-img_len)/2,height-img_len,img_len,img_len);
			}
		}
		else
		{
			glViewport(0,height-img_len,img_len,img_len);
		}
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-1*100,100,-1*100,100,100.0,-100.0);
	gluOrtho2D(-1*100,100,-1*100,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void jdcDrawCursor(int x, int y) {
	setColor(cursorCol);
	glBegin(GL_TRIANGLES);
		glVertex2f(x  ,  y);
		glVertex2f(x+7,  y-7);
		glVertex2f(x  ,y-10);
	glEnd();
}

void jdcDrawCursor(pos2i pos) {
	jdcDrawCursor(pos.x, pos.y);
}

void jdcDrawCursor(){
	jdcDrawCursor(cursorPos);
}

void jdcDrawFanBlade(float x, float y, float z, float l, float w) {
	glBegin(GL_POLYGON);
		setColor(blade_col);
		glVertex3f(x,y,1.0);
		glVertex3f(x+w*0.4,y+l*0.5,1.0);
		glVertex3f(x+w*0.5,y+l*0.8,1.0);
		glVertex3f(x+w*0.4,y+l*0.9,1.0);
		glVertex3f(x+w*0.1,y+l,1.0);
		setColor(mix(black,blade_col));
		glVertex3f(x-w*0.1,y+l,1.0);
		glVertex3f(x-w*0.4,y+l*0.9,1.0);
		glVertex3f(x-w*0.5,y+l*0.8,1.0);
		glVertex3f(x-w*0.4,y+l*0.5,1.0);
	glEnd();
	if (frowning_fan_faces) {
        //jdcDrawHexagon(w/20,(pos2f){x+w*0.2,y+l*0.6});
        //jdcDrawHexagon(w/20,(pos2f){x-w*0.2,y+l*0.6});
        glLineWidth(4);
        glBegin(GL_LINES);
            glVertex3f(x+w*0.5,y+l*0.8,1.0);
            glVertex3f(x+w*0.2,y+l*0.7,1.0);
            glVertex3f(x+w*0.2,y+l*0.7,1.0);
            glVertex3f(x-w*0.2,y+l*0.7,1.0);
            glVertex3f(x-w*0.2,y+l*0.7,1.0);
            glVertex3f(x-w*0.5,y+l*0.8,1.0);
        glEnd();
        glLineWidth(1);
	}
}

void jdcDrawVPallet() {
	int top;
	for(short c=0; c<jdcNumPalletColors; c++) {
		top = 100-c*10;
		setColor(jdcPalletColors[c]);
		jdcDrawRect(-100,top-10,-90,top);
	}
}

void jdcUpdateMousePos(int x, int y) {
	mousePos.x=x;
	mousePos.y=y;
	if(stretch_image) {
		cursorPos.x=(200*mousePos.x/window_corner.x)-100;
		cursorPos.y=100-(200*(mousePos.y)/window_corner.y);
	} else {
		cursorPos.x=(200*mousePos.x/img_len)-100;
		cursorPos.y=100-(200*(mousePos.y)/img_len);
	}
}

void jdcSpecialKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_DOWN:
            y_axis--;
			break;
		case GLUT_KEY_UP:
			y_axis++;
			break;
		case GLUT_KEY_LEFT:
			x_axis--;
			break;
		case GLUT_KEY_RIGHT:
			x_axis++;
			break;
		case GLUT_KEY_PAGE_UP:
			if(speed<MAX_SPEED)
				speed+=SPEED_DELTA;
			break;
		case GLUT_KEY_PAGE_DOWN:
			if(speed>0)
				speed=std::max(0.0,speed-SPEED_DELTA);
			break;
		case GLUT_KEY_HOME:
			r++;
			break;
		case GLUT_KEY_END:
			r--;
			break;
	}
	glutPostRedisplay();
}

void jdcCharKey(unsigned char key, int x, int y) {
    int modifiers = glutGetModifiers();

	switch (key) {
		case '2':
			blades = 2;
			CALC_BLADE_SPACING
			break;
		case '3':
			blades = 3;
			CALC_BLADE_SPACING
			break;
		case '4':
			blades = 4;
			CALC_BLADE_SPACING
			break;
		case '5':
			blades = 5;
			CALC_BLADE_SPACING
			break;
		case '6':
			blades = 6;
			CALC_BLADE_SPACING
			break;
		case '+':
		    if(modifiers & GLUT_ACTIVE_ALT) {
                if (blade_len<MAX_BLADE_LEN)
                    blade_len++;
			} else
                if(blade_wdt<MAX_BLADE_WDT)
                    blade_wdt++;
			break;
		case '-':
		    if(modifiers & GLUT_ACTIVE_ALT ) {
                if (blade_len>MIN_BLADE_LEN)
                    blade_len--;
			} else
                if(blade_wdt>MIN_BLADE_WDT)
                    blade_wdt--;
			break;

        case 'g':
            if(cur_grill_type==BOX)
                cur_grill_type=CIRCULAR;
            else
               cur_grill_type=BOX;
            break;
        case 'f': //Easter Egg: toggle faces on the blades

            frowning_fan_faces = !frowning_fan_faces;
            break;
		case 27:	//ESC
			exit(0);
	}
}

void jdcMouseFunc(int x, int y) {
	jdcUpdateMousePos(x, y);
}

void jdcSetFanColor(color3f c) {
	blade_col = mix(c,black,0.6);
	grate_col = c;
	motor_col = mix(c,black,0.8);
}

void jdcMouseClickFunc(int button, int state, int x, int y) {
	jdcUpdateMousePos(x, y);
	int top;
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
		for(short c=0; c<jdcNumPalletColors; c++) {
			top = 100-c*10;
			if(cursorPos.x>=-100 && cursorPos.x<=-90 && cursorPos.y<=top && cursorPos.y>=top-10) {
				jdcSetFanColor(jdcPalletColors[c]);
			}
		}
	}
}

void jdcIdleFunc(){
	r+=speed;
	glutPostRedisplay();
}

void setColor(color3f c) {
	glColor3f(c.r,c.g,c.b);
}

int main (int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(window_corner.x,window_corner.y);
	glutCreateWindow("Toy Fan");
	glClearColor(bkg_col.r,bkg_col.g,bkg_col.b,1.0);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	CALC_BLADE_SPACING
	glutSetCursor(GLUT_CURSOR_NONE);
	glutDisplayFunc(jdcDisplay);
	glutReshapeFunc(jdcReshapeWindow);

	jdcSetFanColor(white);

	//input handlers
	glutKeyboardFunc(jdcCharKey);
	glutSpecialFunc(jdcSpecialKey);
	glutPassiveMotionFunc(jdcMouseFunc);
	glutMouseFunc(jdcMouseClickFunc);

	glutIdleFunc(jdcIdleFunc);
	glutMainLoop();
	return 0;
}
