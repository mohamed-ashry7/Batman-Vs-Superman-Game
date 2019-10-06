#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <glut.h>

int pp0[2];
int pp1[2];
int pp2[2];
int pp3[2];
int tar = 4;


//this is the method used to print text in OpenGL
//there are three parameters,
//the first two are the coordinates where the text is display,
//the third coordinate is the string containing the text to display
void print(int x, int y, char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

int* bezierr(float t, int* p0, int* p1, int* p2, int* p3)
{
	int res[2];
	res[0] = pow((1 - t), 3) * p0[0] + 3 * t * pow((1 - t), 2) * p1[0] + 3 * pow(t, 2) * (1 - t) * p2[0] + pow(t, 3) * p3[0];
	res[1] = pow((1 - t), 3) * p0[1] + 3 * t * pow((1 - t), 2) * p1[1] + 3 * pow(t, 2) * (1 - t) * p2[1] + pow(t, 3) * p3[1];
	return res;
}

void Displa() {
	glClear(GL_COLOR_BUFFER_BIT);

	print(750, 500, "Bezier Control Points");
	glColor3f(1, 0, 0);
	char* p0s[20];
	sprintf((char*)p0s, "P0={%d,%d}", pp0[0], pp0[1]);
	print(785, 450, (char*)p0s);
	glColor3f(0, 1, 0);
	char* p1s[20];
	sprintf((char*)p1s, "P1={%d,%d}", pp1[0], pp1[1]);
	print(785, 400, (char*)p1s);
	glColor3f(0, 0, 1);
	char* p2s[20];
	sprintf((char*)p2s, "P2={%d,%d}", pp2[0], pp2[1]);
	print(785, 350, (char*)p2s);
	glColor3f(1, 1, 1);
	char* p3s[20];
	sprintf((char*)p3s, "P3={%d,%d}", pp3[0], pp3[1]);
	print(785, 300, (char*)p3s);

	glPointSize(1);
	glColor3f(1, 1, 0);
	glBegin(GL_POINTS);
	for (float t = 0; t < 1; t += 0.001)
	{
		int* p = bezierr(t, pp0, pp1, pp2, pp3);
		glVertex3f(p[0], p[1], 0);
	}
	glEnd();
	glPointSize(9);
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	glVertex3f(pp0[0], pp0[1], 0);
	glColor3f(0, 1, 0);
	glVertex3f(pp1[0], pp1[1], 0);
	glColor3f(0, 0, 1);
	glVertex3f(pp2[0], pp2[1], 0);
	glColor3f(1, 1, 1);
	glVertex3f(pp3[0], pp3[1], 0);
	glEnd();

	glFlush();
}

void mo(int x, int y)
{
	y = 600 - y;
	if (x < 0)
		x = 0;
	if (x > 700)
		x = 700;
	if (y < 0)
		y = 0;
	if (y > 600)
		y = 600;
	if (tar == 0)
	{
		pp0[0] = x;
		pp0[1] = y;
	}
	else if (tar == 1)
	{
		pp1[0] = x;
		pp1[1] = y;
	}
	else if (tar == 2)
	{
		pp2[0] = x;
		pp2[1] = y;
	}
	if (tar == 3)
	{
		pp3[0] = x;
		pp3[1] = y;
	}
	glutPostRedisplay();
}

void mou(int b, int s, int x, int y)
{
	y = 600 - y;
	if (b == GLUT_LEFT_BUTTON && s == GLUT_DOWN)
	{
		if (pp0[0]<x + 9 && pp0[0]>x - 9 && pp0[1]<y + 9 && pp0[1]>y - 9)
		{
			tar = 0;
		}
		else if (pp1[0]<x + 9 & pp1[0]>x - 9 && pp1[1]<y + 9 && pp1[1]>y - 9)
		{
			tar = 1;
		}
		else if (pp2[0]<x + 9 && pp2[0]>x - 9 && pp2[1]<y + 9 && pp2[1]>y - 9)
		{
			tar = 2;
		}
		else if (pp3[0]<x + 9 && pp3[0]>x - 9 && pp3[1]<y + 9 && pp3[1]>y - 9)
		{
			tar = 3;
		}
	}
	if (b == GLUT_LEFT_BUTTON && s == GLUT_UP)
		tar = 4;
}

void mainn(int argc, char** argr) {
	glutInit(&argc, argr);

	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(150, 150);

	pp0[0] = 100;
	pp0[1] = 100;

	pp1[0] = 100;
	pp1[1] = 500;

	pp2[0] = 500;
	pp2[1] = 500;

	pp3[0] = 500;
	pp3[1] = 100;

	glutCreateWindow("OpenGL - 2D Template");
	glutDisplayFunc(Displa);
	glutMotionFunc(mo);
	glutMouseFunc(mou);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 1000, 0.0, 600);

	glutMainLoop();
}
