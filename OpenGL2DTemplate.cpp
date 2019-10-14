#include <stdlib.h> 
#include <glut.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <cmath>
#include <Windows.h>




int windowY = 700;
int windowX = 1500;

// variables for handling the moving rod ; 
double movingRod = 0;
bool goRight = true;
double disappearTime = 0;
// to know which turn is it ; 
bool batmanTurn = true; // true means -> batman  ; 

int batmanX = 150;
int batmanY = 150;
int supermanX = 1150;
int supermanY = 150;

int p0[2]; // batmanPos
int p1[2]; // batmanControl 
int p2[2]; // supermanControl ; 
int p3[2];//supermanPos  ;

// to check if iam pressing the mouse to shoot 
bool isDown = false;
// the amount of power given 
int power = 0;

double t = 0;

bool hasBeenClicked = false;
bool finishTheShot = false;
// to check  if the batman of the dog has been attacked  
bool regularBatman = true;
bool regularSuperman = true;

// to set the time which the batman or the superman will be angry 
double angryTime = 1;


// health of competetors 
int healthSuperman = 240;
int healBatman = 240;

// current position of the projectile ; 
int curX = 0;
int curY = 0;

// to track the winners ;
bool batmanWin = false;
bool supermanWin = false;

double waterDropY = 510;
double waterDropX = 0;
double cloudX = 100;
double lightTime = 4.5;

double movingCurrentArrow = 0;
bool upward = true;

// for the birds 
double DoveX = 500;
double DoveY = 700;
double deltaDoveX = -0.1;
double deltaDoveY = 0.1;


double canaryX = 100;
double canaryY = 500;
double deltacanaryX = 0.1;
double deltacanaryY = -0.1;
double rot = 0;


double flameTime = 0;
double FX = 0;
double FY = 0;

void drawCircle(double cx, double cy, double r, int acc, double red, double green, double blue) {



	glBegin(GL_POLYGON);
	glColor3f(red, green, blue);
	for (int i = 0; i < acc; i++) {
		double theta = 2.0f * 3.14159265359 * double(i) / double(acc);
		double x = cx + r * cosf(theta);
		double y = cy + r * sinf(theta);

		glVertex3f(x, y, 0);
	}


	glEnd();
}

void drawEllipse(double cx, double cy, double rx, double ry, int num_segments, double r, double g, double b) {

	double theta = 2 * 3.1415926 / float(num_segments);
	double c = cosf(theta);//precalculate the sine and cosine
	double s = sinf(theta);
	double t;

	double x = 1;//we start at angle = 0 
	double y = 0;

	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
	for (int ii = 0; ii < num_segments; ii++)
	{
		//apply radius and offset
		glVertex3f(x * rx + cx, y * ry + cy, 0);//output vertex 

		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}
	glEnd();
}


void drawMouth(double cx, double cy, double rad, int acc, double r, double g, double b) {

	glPointSize(2);
	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
	for (int i = 0; i < acc; i++) {
		double theta = 2.0f * 3.14159265359 * double(i) / double(acc);
		double cosT = cosf(theta);
		double sinT = sinf(theta);
		double x = cx + rad * cosT;
		double y = cy + rad * sinT;
		if (cosT <= 0 && sinT <= 0 || cosT >= 0 && sinT <= 0) {
			glVertex3f(x, y, 0);
		}


	}


	glEnd();
}


void drawBird(double x, double y, double r, double g, double b) {
	double width = 50;
	double height = 50;
	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
	glVertex3f(x, y, 0);
	glVertex3f(x + width, y, 0);
	glVertex3f(x + width, y + height, 0);
	glVertex3f(x, y + height, 0);
	glEnd();

	drawEllipse(x, y + height / 2 + movingCurrentArrow / 4.0, 20, 10, 20, r, g, b);
	drawEllipse(x + width, y + height / 2 + movingCurrentArrow / 4.0, 20, 10, 20, r, g, b);

	drawCircle(x + width / 3.0, y + 3 * height / 4.0, 5, 10, 1, 1, 1);
	drawCircle(x + 2 * width / 3.0, y + 3 * height / 4.0, 5, 10, 1, 1, 1);

	// draw iris 
	glPointSize(2);
	glColor3f(0, 0, 0);
	glBegin(GL_POINTS);
	glVertex2f(x + width / 3.0, y + 3 * height / 4.0);
	glVertex2f(x + 2 * width / 3.0, y + 3 * height / 4.0);

	glEnd();

	glColor3f(0.647, 0.286, 0.165); // brown  ; 

	glBegin(GL_TRIANGLES);
	glVertex2f(x + width / 2.0 - 7, y + height / 4.0 + 3);
	glVertex2f(x + width / 2.0 + 7, y + height / 4.0 + 3);
	glVertex2f(x + width / 2.0, y + height / 4.0 + 10);


	glVertex2f(x + width / 2.0 - 7, y + height / 4.0 + 3);
	glVertex2f(x + width / 2.0 + 7, y + height / 4.0 + 3);
	glVertex2f(x + width / 2.0, y + height / 4.0 - 4);

	glEnd();

	glBegin(GL_LINES);
	glVertex2f(x + width / 3, y);
	glVertex2f(x + width / 3, y - 10);


	glVertex2f(x + width / 3, y - 5);
	glVertex2f(x + width / 3 - 6, y - 7);


	glVertex2f(x + width / 3, y - 5);
	glVertex2f(x + width / 3 + 6, y - 7);


	glVertex2f(x + 2 * width / 3, y);
	glVertex2f(x + 2 * width / 3, y - 10);


	glVertex2f(x + 2 * width / 3, y - 5);
	glVertex2f(x + 2 * width / 3 - 6, y - 7);


	glVertex2f(x + 2 * width / 3, y - 5);
	glVertex2f(x + 2 * width / 3 + 6, y - 7);

	glEnd();

}


void drawDove()
{
	drawBird(DoveX, DoveY, 0, 0.512, 1);
}

void drawCanary() {
	drawBird(canaryX, canaryY, 1, 0.749, 0);
}

//void drawCat(int shift = 0) {
//	int x = batmanX;
//	int y = batmanY + shift;
//	int width = 100;
//	int height = 100;
//	glBegin(GL_POLYGON);
//	glColor3f(0.5, 0.6, 0.44);
//	glVertex3f(x, y, 0);
//	glVertex3f(x + width, y, 0);
//	glVertex3f(x + width, y + height, 0);
//	glVertex3f(x, y + height, 0);
//	glEnd();
//
//	glPointSize(25);
//	glBegin(GL_POINTS);
//	glColor3f(0, 0, 0);
//	glVertex3f(x, y + height, 0);
//	glVertex3f(x + width, y + height, 0);
//	glEnd();
//
//
//	// to draw a nose; 
//	double noseX = x + double(width / 2);
//	double noseY = y + double(height / 4);
//	glBegin(GL_TRIANGLES);
//	glColor3f(0.7, 0.6, 0.4);
//	glVertex3f(noseX - 10, noseY, 0);
//	glVertex3f(noseX + 10, noseY, 0);
//	glVertex3f(noseX, noseY + 10, 0);
//	glEnd();
//
//
//	// to draw mustaches ; 
//	glBegin(GL_LINES);
//	glColor3f(0, 0, 0);
//	glVertex3f(noseX + 10, noseY, 0);
//	glVertex3f(noseX + 20, noseY, 0);
//	glVertex3f(noseX - 10, noseY, 0);
//	glVertex3f(noseX - 20, noseY, 0);
//	glVertex3f(noseX - 5, noseY + 5, 0);
//	glVertex3f(noseX - 15, noseY + 5, 0);
//	glVertex3f(noseX + 5, noseY + 5, 0);
//	glVertex3f(noseX + 15, noseY + 5, 0);
//	glEnd();
//
//	// draw leftEye
//	drawCircle(noseX - 20, noseY + 30, 10, 20, 1, 1, 1);
//	// draw iris 
//	drawCircle(noseX - 20, noseY + 30, 4, 20, 0, 0, 0);
//
//	//drawRightEye ; 
//	drawCircle(noseX + 20, noseY + 30, 10, 20, 1, 1, 1);
//	drawCircle(noseX + 20, noseY + 30, 4, 20, 0, 0, 0);
//
//}
//void drawDog(int shift = 0) {
//	int x = supermanX;
//	int y = supermanY + shift;
//	int width = 100;
//	int height = 100;
//	glBegin(GL_POLYGON);
//	glColor3f(0.5, 0.6, 0.44);
//	glVertex3f(x, y, 0);
//	glVertex3f(x + width, y, 0);
//	glVertex3f(x + width, y + height, 0);
//	glVertex3f(x, y + height, 0);
//	glEnd();
//
//	//drawing ears 
//	glBegin(GL_POLYGON);
//	glColor3f(0, 0, 0);
//	glVertex3f(x - 20 / 1.4 + 1, y + height - 20 / 1.4 - 1, 0);
//	glVertex3f(x + 1, y + height - 1, 0);
//	glVertex3f(x - 20 + 1, y + height + 20 - 1, 0);
//	glVertex3f(x - 20 / 1.4 - 20 + 1, y + height - 20 / 1.4 + 20 - 1, 0);
//	glEnd();
//
//	glBegin(GL_POLYGON);
//	glColor3f(0, 0, 0);
//	glVertex3f(x + width - 1, y + height - 1, 0);
//	glVertex3f(x + width + 20 / 1.4 - 1, y + height - 20 / 1.4 - 1, 0);
//	glVertex3f(x + width + 20 / 1.4 + 20 - 1, y + height - 20 / 1.4 + 20 - 1, 0);
//	glVertex3f(x + width + 20 - 1, y + height + 20 - 1, 0);
//
//
//	glEnd();
//	// to draw a nose; 
//	double noseX = x + double(width / 2.0);
//	double noseY = y + double(height / 4.0);
//	glBegin(GL_QUADS);
//	glColor3f(0.6, 0.2, 0.7);
//	glVertex3f(noseX - 10, noseY, 0);
//	glVertex3f(noseX + 10, noseY, 0);
//	glVertex3f(noseX + 10, noseY + 20, 0);
//	glVertex3f(noseX - 10, noseY + 20, 0);
//	glEnd();
//
//
//	// to draw mustaches ; 
//	glBegin(GL_LINES);
//	glColor3f(0, 0, 0);
//
//	glVertex3f(noseX + 10, noseY, 0);
//	glVertex3f(noseX + 20, noseY, 0);
//
//	glVertex3f(noseX + 10, noseY + 10, 0);
//	glVertex3f(noseX + 20, noseY + 10, 0);
//
//	glVertex3f(noseX - 10, noseY, 0);
//	glVertex3f(noseX - 20, noseY, 0);
//
//	glVertex3f(noseX - 10, noseY + 10, 0);
//	glVertex3f(noseX - 20, noseY + 10, 0);
//	glEnd();
//
//	// draw leftEye
//	drawCircle(noseX - 20, noseY + 30, 10, 20, 1, 1, 1);
//	drawCircle(noseX - 20, noseY + 30, 4, 20, 0, 0, 0);
//
//	//drawRightEye ; 
//	drawCircle(noseX + 20, noseY + 30, 10, 20, 1, 1, 1);
//	drawCircle(noseX + 20, noseY + 30, 4, 20, 0, 0, 0);
//
//}

void drawBatmanLogo(double x = 0, double y = 0) {
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	for (double xcord = 7; xcord >= 0; xcord -= 0.01)
	{
		double ycordPos = 2 * sqrt((double)(-1 * (abs(abs(xcord) - 1)) * abs(3 - abs(xcord)) / ((abs(xcord) - 1) * (3 - abs(xcord))))) *
			(1 + abs(abs(xcord) - 3) / (abs(xcord) - 3)) * sqrt((double)(1 - pow((xcord / 7), 2))) +
			(5 + 0.97 * (abs(xcord - 0.5) + abs(xcord + 0.5)) - 3 * (abs(xcord - 0.75) + abs(xcord + 0.75))) *
			(1 + abs(1 - abs(xcord)) / (1 - abs(xcord)));
		glVertex3d(xcord, ycordPos, 0);

		double ycordNeg = -3 * sqrt((double)(1 - pow((xcord / 7), 2))) * sqrt((double)(abs(abs(xcord) - 4) / (abs(xcord) - 4)));
		glVertex3d(xcord, ycordNeg, 0);
		glVertex3d(-xcord, ycordPos, 0);
		glVertex3d(-xcord, ycordNeg, 0);

	}

	for (double xcord = 3.99; xcord >= 0; xcord -= 0.01)
	{
		double ycordPos;
		if (xcord >= 3 || xcord <= 1)
		{
			ycordPos = 2 * sqrt((double)(-1 * (abs(abs(xcord) - 1)) * abs(3 - abs(xcord)) / ((abs(xcord) - 1) * (3 - abs(xcord))))) *
				(1 + abs(abs(xcord) - 3) / (abs(xcord) - 3)) * sqrt((double)(1 - pow((xcord / 7), 2))) +
				(5 + 0.97 * (abs(xcord - 0.5) + abs(xcord + 0.5)) - 3 * (abs(xcord - 0.75) + abs(xcord + 0.75))) *
				(1 + abs(1 - abs(xcord)) / (1 - abs(xcord)));
		}
		else
		{
			ycordPos = 2.71052 + (1.5 - 0.5 * abs(xcord)) - 1.35526 * sqrt((double)(4 - pow(abs(xcord) - 1, 2))) *
				sqrt((double)(abs(abs(xcord) - 1) / (abs(xcord) - 1))) + 0.9;
		}
		glVertex3d(xcord, ycordPos, 0);

		double ycordNeg = abs(xcord / 2) - 0.0913722 * pow(xcord, 2) - 3 + sqrt((double)(1 - pow((abs(abs(xcord) - 2) - 1), 2)));
		glVertex3d(xcord, ycordNeg, 0);
		glVertex3d(-xcord, ycordPos, 0);
		glVertex3d(-xcord, ycordNeg, 0);

	}

	glEnd();
}

void drawBatmanMissile(double x, double y) {

	glPushMatrix();
	glTranslated(x, y, 0);
	glScaled(3, 3, 0);

	glRotatef(rot, 0, 0, 1);

	drawBatmanLogo();
	glPopMatrix();

}

void drawBombMissile(double x, double y) {
	double r = 4;

	glPushMatrix();
	glTranslated(x, y, 0);
	glScaled(3, 3, 0);

	glRotatef(rot, 0, 0, 1);
	drawCircle(0, 0, 4, 20, 0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(-2, r - 0.5, 0);
	glVertex3f(2, r - 0.5, 0);
	glVertex3f(2, r + 1.5, 0);
	glVertex3f(-2, r + 1.5, 0);
	glEnd();


	glBegin(GL_LINES);
	glVertex3f(0, r + 1.5, 0);
	glVertex3f(0, r + 5, 0);
	glEnd();

	if (upward) {
		glColor3f(1, 0, 0);
		glBegin(GL_LINES);
		glVertex3f(0, r + 3, 0);
		glVertex3f(-2, r + 5, 0);
		glEnd();
	}
	else {
		glColor3f(1, 0, 0);
		glBegin(GL_LINES);
		glVertex3f(0, r + 3, 0);
		glVertex3f(2, r + 5, 0);
		glEnd();
	}
	glPopMatrix();
}

void drawBatman(double shiftX = 0, double shiftY = 0, double W = 0, double H = 0) {
	double x = batmanX + shiftX;
	double y = batmanY + shiftY;
	double headWidth = 50 + W;
	double headHeight = 50 + H;
	// drawing head ; 
	glColor3f(0.941, 0.7607, 0.4901);
	glBegin(GL_QUADS);
	glVertex3f(x, y, 0);
	glVertex3f(x + headWidth, y, 0);
	glVertex3f(x + headWidth, y + headHeight, 0);
	glVertex3f(x, y + headHeight, 0);
	glEnd();

	// draw mask 
	glBegin(GL_QUADS);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(x, y + headHeight / 2, 0);
	glVertex3f(x + headWidth, y + headHeight / 2, 0);
	glVertex3f(x + headWidth, y + headHeight, 0);
	glVertex3f(x, y + headHeight, 0);
	glEnd();

	//draw eyes ; 
	drawEllipse(x + headWidth / 4, y + 3 * headHeight / 4, 5, 4, 20, 1, 1, 1);
	drawEllipse(x + 3 * headWidth / 4, y + 3 * headHeight / 4, 5, 4, 20, 1, 1, 1);

	//draw mouth
	//drawMouth(x + headWidth / 2, y + headHeight / 3, 10, 20, 1, 1, 1);
	glBegin(GL_QUADS);
	glVertex3f(x + headWidth / 2 - 10, y + headHeight / 3 - 5, 0);
	glVertex3f(x + headWidth / 2 + 10, y + headHeight / 3 - 5, 0);
	glVertex3f(x + headWidth / 2 + 10, y + headHeight / 3, 0);
	glVertex3f(x + headWidth / 2 - 10, y + headHeight / 3, 0);
	glEnd();
	// draw the ears ;
	glBegin(GL_TRIANGLES);
	glColor3f(0.2, 0.2, 0.2);

	glVertex3f(x, y + headHeight, 0);
	glVertex3f(x + 20, y + headHeight, 0);
	glVertex3f(x + 10, y + headHeight + 10, 0);

	glVertex3f(x + headWidth - 20, y + headHeight, 0);
	glVertex3f(x + headWidth, y + headHeight, 0);
	glVertex3f(x + headWidth - 10, y + headHeight + 10, 0);
	glEnd();
	// draw Cloak
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex3f(x - 50, y - 100, 0);
	glVertex3f(x + headWidth + 50, y - 100, 0);
	glVertex3f(x + headWidth + 20, y, 0);
	glVertex3f(x - 20, y, 0);

	glVertex3f(x - 20, y - 70, 0);
	glVertex3f(x + headWidth + 20, y - 70, 0);
	glVertex3f(x + headWidth + 20, y, 0);
	glVertex3f(x - 20, y, 0);
	glEnd();

	//drawing Body 
	glBegin(GL_QUADS);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(x - 20, y - 70, 0);
	glVertex3f(x + headWidth + 20, y - 70, 0);
	glVertex3f(x + headWidth + 20, y, 0);
	glVertex3f(x - 20, y, 0);
	glEnd();

	//draw LOGO ; 

	drawEllipse(x + headWidth / 2, y - 20, 20, 15, 20, 1, 1, 0);
	glPushMatrix();
	glTranslated(x + headWidth / 2, y - 20, 0);
	glScaled(2, 2, 0);
	drawBatmanLogo();
	glPopMatrix();

	//draw belt ; 

	glBegin(GL_QUADS);
	glColor3f(0.95, 0.95, 0);
	glVertex3f(x - 20, y - 70, 0);
	glVertex3f(x + headWidth + 20, y - 70, 0);
	glVertex3f(x + headWidth + 20, y - 50, 0);
	glVertex3f(x - 20, y - 50, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(x - 20, y - 70, 0);
	glVertex3f(x - 20, y - 50, 0);

	glVertex3f(x - 5, y - 70, 0);
	glVertex3f(x - 5, y - 50, 0);

	glVertex3f(x + 10, y - 70, 0);
	glVertex3f(x + 10, y - 50, 0);

	glVertex3f(x + 25, y - 70, 0);
	glVertex3f(x + 25, y - 50, 0);

	glVertex3f(x + 40, y - 70, 0);
	glVertex3f(x + 40, y - 50, 0);

	glVertex3f(x + 55, y - 70, 0);
	glVertex3f(x + 55, y - 50, 0);

	glVertex3f(x + 70, y - 70, 0);
	glVertex3f(x + 70, y - 50, 0);

	glEnd();

	//draw legs 
	glBegin(GL_QUADS);


	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(x + headWidth / 2 - 20, y - 120, 0);
	glVertex3f(x + headWidth / 2, y - 120, 0);
	glVertex3f(x + headWidth / 2, y - 70, 0);
	glVertex3f(x + headWidth / 2 - 20, y - 70, 0);

	glVertex3f(x + headWidth / 2 + 5, y - 120, 0);
	glVertex3f(x + headWidth / 2 + 25, y - 120, 0);
	glVertex3f(x + headWidth / 2 + 25, y - 70, 0);
	glVertex3f(x + headWidth / 2 + 5, y - 70, 0);

	// draw foot
	glColor3f(0, 0, 0);
	glVertex3f(x + headWidth / 2 - 20, y - 120, 0);
	glVertex3f(x + headWidth / 2, y - 120, 0);
	glVertex3f(x + headWidth / 2, y - 110, 0);
	glVertex3f(x + headWidth / 2 - 20, y - 110, 0);

	glVertex3f(x + headWidth / 2 + 5, y - 120, 0);
	glVertex3f(x + headWidth / 2 + 25, y - 120, 0);
	glVertex3f(x + headWidth / 2 + 25, y - 110, 0);
	glVertex3f(x + headWidth / 2 + 5, y - 110, 0);
	glEnd();


}


void drawSupermanLogo(double x, double y) {

	glBegin(GL_POLYGON);
	glColor3f(0.8, 0, 0);
	glVertex3f(x - 20, y, 0);
	glVertex3f(x, y - 20, 0);
	glVertex3f(x + 20, y, 0);
	glVertex3f(x + 10, y + 10, 0);
	glVertex3f(x - 10, y + 10, 0);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(1, 1, 0);
	glVertex3f(x - 16, y, 0);
	glVertex3f(x, y - 16, 0);
	glVertex3f(x + 16, y, 0);
	glVertex3f(x + 6, y + 6, 0);
	glVertex3f(x - 6, y + 6, 0);

	glEnd();

	/*glBegin(GL_QUADS);
	glColor3f(0.8, 0, 0);
	glVertex3f(x-10,y-15,0);
	glVertex3f(x + 10, y +5, 0);
	glVertex3f(x + 10, y +5, 0);
	glVertex3f(x - 10, y - 15, 0);

	glEnd(); */
}

void drawSuperman(double shiftX = 0, double shiftY = 0, double W = 0, double H = 0) {
	double x = supermanX + shiftX;
	double y = supermanY + shiftY;
	double headWidth = 50 + W;
	double headHeight = 50 + H;
	// drawing head ; 
	//drawEllipse(x+headWidth/2 , y + headHeight/2 , 28,32 ,20, 0.941, 0.7607, 0.4901);

	glBegin(GL_QUADS);
	glColor3f(0.941, 0.7607, 0.4901);
	glVertex3f(x, y, 0);
	glVertex3f(x + headWidth, y, 0);
	glVertex3f(x + headWidth, y + headHeight, 0);
	glVertex3f(x, y + headHeight, 0);
	glEnd();

	//draw hair
	drawCircle(x, y + headHeight, 0.2 * headWidth, 20, 0, 0, 0);
	drawCircle(x + 0.3 * headWidth, y + headHeight, 0.2 * headWidth, 20, 0, 0, 0);
	drawCircle(x + 0.4 * headWidth / 2, y + headHeight, 0.2 * headWidth, 20, 0, 0, 0);
	drawCircle(x + 0.6 * headWidth, y + headHeight, 0.2 * headWidth, 20, 0, 0, 0);
	drawCircle(x + 0.8 * headWidth, y + headHeight, 0.2 * headWidth, 20, 0, 0, 0);
	drawCircle(x + 0.9 * headWidth, y + headHeight - headHeight / 10, 0.2 * headWidth, 20, 0, 0, 0);

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(x + headWidth / 4 - 3, y + 3 * headHeight / 4 - 4, 0);
	glVertex3f(x + headWidth / 4 + 7, y + 3 * headHeight / 4 - 4, 0);

	glVertex3f(x + 3 * headWidth / 4 - 7, y + 3 * headHeight / 4 - 4, 0);
	glVertex3f(x + 3 * headWidth / 4 + 3, y + 3 * headHeight / 4 - 4, 0);
	glEnd();


	//draw eyes ; 


	drawCircle(x + headWidth / 4 + 2, y + 3 * headHeight / 4 - 8, 2, 20, 0, 0, 0);
	drawCircle(x + 3 * headWidth / 4 - 2, y + 3 * headHeight / 4 - 8, 2, 20, 0, 0, 0);

	//draw mouth
	//drawMouth(x + headWidth / 2, y + headHeight / 3, 10, 20, 1, 1, 1);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);

	glVertex3f(x + headWidth / 2 - 10, y + headHeight / 3 - 5, 0);
	glVertex3f(x + headWidth / 2 + 10, y + headHeight / 3 - 5, 0);
	glVertex3f(x + headWidth / 2 + 10, y + headHeight / 3, 0);
	glVertex3f(x + headWidth / 2 - 10, y + headHeight / 3, 0);
	glEnd();
	// draw the ears ;

	// draw Cloak
	glBegin(GL_QUADS);
	glColor3f(0.6, 0, 0);
	glVertex3f(x - 50, y - 100, 0);
	glVertex3f(x + headWidth + 50, y - 100, 0);
	glVertex3f(x + headWidth + 20, y, 0);
	glVertex3f(x - 20, y, 0);

	glVertex3f(x - 20, y - 70, 0);
	glVertex3f(x + headWidth + 20, y - 70, 0);
	glVertex3f(x + headWidth + 20, y, 0);
	glVertex3f(x - 20, y, 0);
	glEnd();

	//drawing Body 
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0.8);
	glVertex3f(x - 20, y - 70, 0);
	glVertex3f(x + headWidth + 20, y - 70, 0);
	glVertex3f(x + headWidth + 20, y, 0);
	glVertex3f(x - 20, y, 0);
	glEnd();

	//draw LOGO ; 


	drawSupermanLogo(x + headWidth / 2, y - 20);


	//draw belt ; 

	glBegin(GL_QUADS);
	glColor3f(0.95, 0.95, 0);
	glVertex3f(x - 20, y - 70, 0);
	glVertex3f(x + headWidth + 20, y - 70, 0);
	glVertex3f(x + headWidth + 20, y - 50, 0);
	glVertex3f(x - 20, y - 50, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(x - 20, y - 70, 0);
	glVertex3f(x - 20, y - 50, 0);

	glVertex3f(x - 5, y - 70, 0);
	glVertex3f(x - 5, y - 50, 0);

	glVertex3f(x + 10, y - 70, 0);
	glVertex3f(x + 10, y - 50, 0);

	glVertex3f(x + 25, y - 70, 0);
	glVertex3f(x + 25, y - 50, 0);

	glVertex3f(x + 40, y - 70, 0);
	glVertex3f(x + 40, y - 50, 0);

	glVertex3f(x + 55, y - 70, 0);
	glVertex3f(x + 55, y - 50, 0);

	glVertex3f(x + 70, y - 70, 0);
	glVertex3f(x + 70, y - 50, 0);

	glEnd();

	//draw legs 
	glBegin(GL_QUADS);


	glColor3f(0, 0, 0.8);
	glVertex3f(x + headWidth / 2 - 20, y - 120, 0);
	glVertex3f(x + headWidth / 2, y - 120, 0);
	glVertex3f(x + headWidth / 2, y - 70, 0);
	glVertex3f(x + headWidth / 2 - 20, y - 70, 0);

	glVertex3f(x + headWidth / 2 + 5, y - 120, 0);
	glVertex3f(x + headWidth / 2 + 25, y - 120, 0);
	glVertex3f(x + headWidth / 2 + 25, y - 70, 0);
	glVertex3f(x + headWidth / 2 + 5, y - 70, 0);

	// draw foot

	glColor3f(0.6, 0, 0);
	glVertex3f(x + headWidth / 2 - 20, y - 120, 0);
	glVertex3f(x + headWidth / 2, y - 120, 0);
	glVertex3f(x + headWidth / 2, y - 110, 0);
	glVertex3f(x + headWidth / 2 - 20, y - 110, 0);

	glVertex3f(x + headWidth / 2 + 5, y - 120, 0);
	glVertex3f(x + headWidth / 2 + 25, y - 120, 0);
	glVertex3f(x + headWidth / 2 + 25, y - 110, 0);
	glVertex3f(x + headWidth / 2 + 5, y - 110, 0);
	glEnd();

}

void drawCurve(double cx, double cy, double r, int acc, int quad) {

	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	for (int i = 0; i < acc; i++) {
		double theta = 2.0f * 3.14159265359 * double(i) / double(acc);
		double cosT = cosf(theta);
		double sinT = sinf(theta);
		double x = cx + r * cosT;
		double y = cy + r * sinT;
		if (quad == 1) {
			if (cosT >= 0 && sinT >= 0) {
				glVertex3f(x, y, 0);
			}
		}
		else if (quad == 2) {
			if (cosT <= 0 && sinT >= 0) {
				glVertex3f(x, y, 0);
			}
		}
		else if (quad == 3) {
			if (cosT <= 0 && sinT <= 0) {
				glVertex3f(x, y, 0);
			}
		}
		else {
			if (cosT >= 0 && sinT <= 0) {
				glVertex3f(x, y, 0);
			}
		}


	}


	glEnd();
}


void drawAngerSign(double x, double y) {
	double width = 10;
	double lineLen = 10;
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(x, y, 0);  // left top 
	glVertex3f(x, y - lineLen, 0);

	glVertex3f(x - width - lineLen, y - lineLen - width, 0);
	glVertex3f(x - width, y - lineLen - width, 0);

	glVertex3f(x, y - lineLen - 2 * width - 5, 0);  // left down 
	glVertex3f(x, y - 2 * lineLen - 2 * width - 5, 0);

	glVertex3f(x - width - lineLen, y - lineLen - width - 5, 0);
	glVertex3f(x - width, y - lineLen - width - 5, 0);

	glVertex3f(x + 5, y, 0); // right top 
	glVertex3f(x + 5, y - lineLen, 0);

	glVertex3f(x + width + 5 + lineLen, y - lineLen - width, 0);
	glVertex3f(x + width + 5, y - lineLen - width, 0);


	glVertex3f(x + 5, y - lineLen - 2 * width - 5, 0);  // right down 
	glVertex3f(x + 5, y - 2 * lineLen - 2 * width - 5, 0);

	glVertex3f(x + width + 5 + lineLen, y - lineLen - width - 5, 0);
	glVertex3f(x + width + 5, y - lineLen - width - 5, 0);

	glEnd();
	// note the order of curves is not the order of the signs ; 
	drawCurve(x - width, y - lineLen, width, 40, 4); // left top 

	drawCurve(x - width, y - lineLen - 2 * width - 5, width, 40, 1); // left down  

	drawCurve(x + width + 5, y - lineLen, width, 40, 3); // right top  

	drawCurve(x + width + 5, y - lineLen - 2 * width - 5, width, 40, 2); // right down  


}





void drawWall() {
	int x = windowX / 2;


	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.8, 0.47);
	glVertex3f(x - 15, 0, 0);
	glVertex3f(x + 15, 0, 0);
	glVertex3f(x + 15, 400, 0);
	glVertex3f(x - 15, 400, 0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.6, 0.8, 0.2);
	glVertex3f(x - 10, 40, 0);
	glVertex3f(x + 10, 40, 0);
	glVertex3f(x + 10, 360, 0);
	glVertex3f(x - 10, 360, 0);
	glEnd();

}

void drawMovingRod() {

	glBegin(GL_POLYGON);
	glColor3f(0.72, 0, 0);
	glVertex3f(movingRod, windowY / 2 + 60, 0);
	glVertex3f(movingRod + 200, windowY / 2 + 60, 0);
	glVertex3f(movingRod + 200, windowY / 2 + 100, 0);
	glVertex3f(movingRod, windowY / 2 + 100, 0);
	glEnd();


	glBegin(GL_LINES);
	glColor3f(0.6, 0.5, 0.4);

	for (int i = 0; i < 200; i += 20) {
		glVertex3f(movingRod+i, windowY / 2 + 60, 0);
		glVertex3f(movingRod+i, windowY / 2 + 100, 0);
	}


	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.6, 0.5, 0.4);
	glVertex3f(movingRod, windowY / 2 + 60, 0);
	glVertex3f(movingRod, windowY / 2 + 100, 0);
	glVertex3f(movingRod - 25, windowY / 2 + 80, 0);


	glColor3f(0.6, 0.5, 0.4);
	glVertex3f(movingRod + 200, windowY / 2 + 60, 0);
	glVertex3f(movingRod + 200, windowY / 2 + 100, 0);
	glVertex3f(movingRod + 200 + 25, windowY / 2 + 80, 0);

	glEnd();



}

void drawHealthBarBatman() {
	int x = 10;
	int y = windowY - 40;
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex3f(x, y, 0);
	glVertex3f(x + healBatman, y, 0);
	glVertex3f(x + healBatman, y + 30, 0);
	glVertex3f(x, y + 30, 0);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 1, 0);
	glVertex3f(x, y, 0);
	glVertex3f(x + 240, y, 0);
	glVertex3f(x + 240, y + 30, 0);
	glVertex3f(x, y + 30, 0);

	glEnd();
}

void drawHealthBarSuperman() {
	int x = windowX - 10 - healthSuperman;
	int y = windowY - 40;
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex3f(x, y, 0);
	glVertex3f(windowX - 10, y, 0);
	glVertex3f(windowX - 10, y + 30, 0);
	glVertex3f(x, y + 30, 0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0, 1, 0);
	glVertex3f(windowX - 10 - 240, y, 0);
	glVertex3f(windowX - 10, y, 0);
	glVertex3f(windowX - 10, y + 30, 0);
	glVertex3f(windowX - 10 - 240, y + 30, 0);

	glEnd();
}


void drawFlames(double x, double y) {
	glBegin(GL_TRIANGLES);
	glColor3f(0.8, 0, 0);
	glVertex3f(x, y, 0);
	glVertex3f(x + 40, y, 0);
	if (upward) {
		glVertex3f(x + 15, y + 40, 0);
	}
	else {
		glVertex3f(x + 10, y + 40, 0);
	}

	glColor3f(1, 1, 0);
	glVertex3f(x + 5, y + 5, 0);
	glVertex3f(x + 35, y + 5, 0);
	if (upward) {
		glVertex3f(x + 15, y + 30, 0);
	}
	else {
		glVertex3f(x + 10, y + 35, 0);
	}


	glColor3f(0.8, 0, 0);
	glVertex3f(x, y, 0);
	glVertex3f(x + 40, y, 0);
	if (upward) {
		glVertex3f(x + 45, y + 40, 0);
	}
	else {
		glVertex3f(x + 40, y + 40, 0);
	}

	glColor3f(1, 1, 0);
	glVertex3f(x + 5, y + 5, 0);
	if (upward) {
		glVertex3f(x + 35, y + 5, 0);
		glVertex3f(x + 45, y + 35, 0);
	}
	else {
		glVertex3f(x + 30, y + 5, 0);
		glVertex3f(x + 40, y + 30, 0);
	}
	glEnd();
}

void drawPowerLine(int x, int y) {

	int len = fmin(power, 1200);

	double r = 0;
	double g = 0;
	double b = 0;
	if (len <= 200) {
		g = power / 200.0;
	}
	else if (len <= 400) {
		r = power / 400.0;
		g = 1;
	}
	else if (len < 600) {
		r = 1;
		g = 1 - len / 1200.0;
		b = 0.5 - len / 2400.0;
	}
	else if (len < 800) {
		r = 1;
		g = 0.5 - len / 2500.0;
		b = 0.5 - len / 4900.0;
	}
	else if (len < 1000) {
		r = 1;
		g = 0.3 - len / 5000.0;
		b = 0.3 - len / 6000.0;
	}
	else if (len <= 1200) {
		r = len / 1200.0;
		b = 0.2 - len / 6000.0;
		g = 0.1 - len / 12000.0;
	}
	glBegin(GL_POLYGON);
	glColor3f(r, g, b);
	glVertex3f(x, y, 0);
	glVertex3f(x + len / 5, y, 0);
	glVertex3f(x + len / 5, y + 30, 0);
	glVertex3f(x, y + 30, 0);
	glEnd();
}


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

void bezier(float t, int* p0, int* p1, int* p2, int* p3)
{

	curX = pow((1 - (double)t), 3) * p0[0] + 3 * (double)t * pow((1 - (double)t), 2) * p1[0] + 3 * pow(t, 2) * (1 - (double)t) * p2[0] + pow(t, 3) * p3[0];
	curY = pow((1 - (double)t), 3) * p0[1] + 3 * (double)t * pow((1 - (double)t), 2) * p1[1] + 3 * pow(t, 2) * (1 - (double)t) * p2[1] + pow(t, 3) * p3[1];

}



bool collideWithObstacle(int x, int y) {

	int xx = windowX / 2;
	if ((x >= xx - 15 && x <= xx + 15 && y >= 0 && y <= 400) || x<0 || x>windowX || y < 0) {
		flameTime = 5;
		FX = x;
		FY = y;
		return true;
	}
	if ((x >= movingRod && x <= movingRod + 200 && y >= windowY / 2 + 60 && y <= windowY / 2 + 100) && disappearTime <= 0) {
		disappearTime = 5;
		flameTime = 2;
		FX = x;
		FY = y;
		return true;
	}
	return false;
}


bool collideWithOpponent(int x, int y) {
	if (batmanTurn) {
		if (x >= supermanX && x <= supermanX + 50 && y >= supermanY && y <= supermanY + 50 ||
			x >= supermanX - 20 && x <= supermanX + 50 + 20 && y >= supermanY - 70 && y <= supermanY) {
			regularSuperman = false;
			healthSuperman -= 48;
			flameTime = 5;
			FX = x;
			FY = y;
			return true;
		}
	}
	else {
		if (x >= batmanX && x <= batmanX + 50 && y >= batmanY && y <= batmanY + 50 ||
			x >= batmanX - 20 && x <= batmanX + 50 + 20 && y >= batmanY - 70 && y <= batmanY) {
			regularBatman = false;
			healBatman -= 48;
			flameTime = 5;
			FX = x;
			FY = y;
			return true;
		}
	}
	return false;
}

void drawProjectile() {





	if (!batmanTurn) {
		bezier(t, p3, p2, p1, p0);
		drawBombMissile(curX, curY);
	}
	else {
		bezier(t, p0, p1, p2, p3);
		drawBatmanMissile(curX, curY);
	}



}

void drawCurrentArrow(int x, int y) {

	int width = 10;
	int height = 30;
	glBegin(GL_POLYGON);
	glColor3f(1, 0.5, 0.1);
	glVertex3f(x, y + movingCurrentArrow, 0);
	glVertex3f(x + width, y + movingCurrentArrow, 0);
	glVertex3f(x + width, y + height + movingCurrentArrow, 0);
	glVertex3f(x, y + height + movingCurrentArrow, 0);
	glEnd();

	int edge = 10;
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0.5, 0.1);
	glVertex3f(x - edge, y + movingCurrentArrow, 0);
	glVertex3f(x + edge / 2, y - 15 + movingCurrentArrow, 0);
	glVertex3f(x + width + edge, y + movingCurrentArrow, 0);
	glEnd();


}


void drawCloud(double cx, double cy, double rx, double ry, int num_segments)
{
	drawEllipse(cx, cy, rx, ry, num_segments, 0.5, 0.5, 0.5);
}


void drawBushes() {

	drawEllipse(0, 0, 350, 100, 40, 0, 0.702, 0);
	drawEllipse(500, 20, 200, 50, 40, 0, 0.804, 0);
	drawEllipse(1100, 10, 500, 50, 40, 0, 0.506, 0);
}


void drawMoon() {
	double cx = 100;
	double cy = 100;
	double r = 50;
	drawCircle(cx, windowY - cy, r, 20, 1, 1, 1);


}
void drawWaterDrop(double x, double y) {
	double r = 10;
	drawCircle(x, y, r, 40, 0.5, 59.2, 1);
	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 59.2, 1);
	glVertex2f(x - r, y);
	glVertex2f(x + r, y);
	glVertex2f(x, y + 2.2 * r);
	glEnd();
}

void drawLightning(int x, int  y) {

	glBegin(GL_POLYGON);
	glColor3f(0.99, 0.86, 0.1);
	glVertex3f(x, y, 0);
	glVertex3f(x + 20, y, 0);
	glVertex3f(x + 40, y + 40, 0);
	glVertex3f(x + 20, y + 40, 0);

	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(x + 15, y + 10, 0);
	glVertex3f(x - 5, y - 40, 0);
	glVertex3f(x + 35, y + 10, 0);


	glEnd();

}

void lightningSetter(int val)
{
	lightTime = 4.5;
	glutTimerFunc(4000, lightningSetter, 0);
}

void debug() {
	char* p0s[20];
	sprintf((char*)p0s, "P0={%d,%d}", p0[0], p0[1]);
	print(785, 450, (char*)p0s);

	char* p1s[20];
	sprintf((char*)p0s, "P1={%d,%d}", p1[0], p1[1]);
	print(785, 400, (char*)p1s);

	char* p2s[20];
	sprintf((char*)p2s, "P2={%d,%d}", p2[0], p2[1]);
	print(785, 350, (char*)p2s);

	char* p3s[20];
	sprintf((char*)p3s, "P3={%d,%d}", p3[0], p3[1]);
	print(785, 300, (char*)p3s);


	char* p4s[20];
	sprintf((char*)p3s, "t=%d", t);
	print(785, 250, (char*)p4s);
	/*char* p0s[20];
	sprintf((char*)p0s, "P0={%d,%d}", p0[0], p0[1]);
	print(785, 450, (char*)p0s);*/

}


void drawBuilding(double x, double y, double w, double h) {


	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex3f(x, y, 0);
	glVertex3f(x + w, y, 0);
	glVertex3f(x + w, y + h, 0);
	glVertex3f(x, y + h, 0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 0);
	glVertex3f(x + 0.1 * w, y + h * 0.1, 0);
	glVertex3f(x + 0.3 * w, y + h * 0.1, 0);
	glVertex3f(x + 0.3 * w, y + 0.3 * h, 0);
	glVertex3f(x + 0.1 * w, y + 0.3 * h, 0);


	glVertex3f(x + 0.1 * w, y + h * 0.4, 0);
	glVertex3f(x + 0.3 * w, y + h * 0.4, 0);
	glVertex3f(x + 0.3 * w, y + 0.6 * h, 0);
	glVertex3f(x + 0.1 * w, y + 0.6 * h, 0);

	glVertex3f(x + 0.1 * w, y + h * 0.7, 0);
	glVertex3f(x + 0.3 * w, y + h * 0.7, 0);
	glVertex3f(x + 0.3 * w, y + 0.9 * h, 0);
	glVertex3f(x + 0.1 * w, y + 0.9 * h, 0);

	glVertex3f(x + 0.7 * w, y + h * 0.1, 0);
	glVertex3f(x + 0.9 * w, y + h * 0.1, 0);
	glVertex3f(x + 0.9 * w, y + 0.3 * h, 0);
	glVertex3f(x + 0.7 * w, y + 0.3 * h, 0);


	glVertex3f(x + 0.7 * w, y + h * 0.4, 0);
	glVertex3f(x + 0.9 * w, y + h * 0.4, 0);
	glVertex3f(x + 0.9 * w, y + 0.6 * h, 0);
	glVertex3f(x + 0.7 * w, y + 0.6 * h, 0);

	glVertex3f(x + 0.7 * w, y + h * 0.7, 0);
	glVertex3f(x + 0.9 * w, y + h * 0.7, 0);
	glVertex3f(x + 0.9 * w, y + 0.9 * h, 0);
	glVertex3f(x + 0.7 * w, y + 0.9 * h, 0);

	glEnd();
}

void drawStar(double x, double y) {
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex3f(x, y, 0);
	glVertex3f(x + 5, y, 0);
	glVertex3f(x + 2.5, y + 7.5, 0);

	glVertex3f(x, y, 0);
	glVertex3f(x + 2.5, y - 7.5, 0);
	glVertex3f(x + 5, y, 0);

	glVertex3f(x - 5, y, 0);
	glVertex3f(x + 2.5, y - 2.5, 0);
	glVertex3f(x + 2.5, y + 2.5, 0);

	glVertex3f(x + 10, y, 0);
	glVertex3f(x + 2.5, y + 2.5, 0);
	glVertex3f(x + 2.5, y - 2.5, 0);
	glEnd();
}
void drawBackground() {
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0.54);
	glVertex3f(0, 100, 0);
	glVertex3f(windowX, 100, 0);
	glVertex3f(windowX, windowY, 0);
	glVertex3f(0, windowY, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0.231, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(windowX, 0, 0);
	glVertex3f(windowX, 100, 0);
	glVertex3f(0, 100, 0);
	glEnd();
	drawMoon();

	if (lightTime > 0) {
		glBegin(GL_TRIANGLES);
		glColor3f(0, 0, 0);
		glVertex3f(0, 200, 0);
		glColor3f(1, 1, 1);
		glVertex3f(400, 400, 0);
		glVertex3f(200, 400, 0);
		glEnd();

		drawEllipse(300, 400, 100, 50, 50, 1, 1, 1);
		glPushMatrix();
		glTranslated(300, 400, 0);
		glScaled(10, 10, 0);
		drawBatmanLogo();
		glPopMatrix();

	}
	drawBuilding(0, 100, 50, 50);
	drawBuilding(50, 100, 50, 100);
	drawBuilding(100, 100, 100, 70);
	drawBuilding(200, 100, 50, 80);
	drawBuilding(250, 100, 50, 40);
	drawBuilding(300, 100, 60, 150);
	drawBuilding(360, 100, 50, 30);
	drawBuilding(410, 100, 70, 60);
	drawBuilding(480, 100, 50, 59);
	drawBuilding(530, 100, 30, 40);
	drawBuilding(560, 100, 80, 120);
	drawBuilding(640, 100, 50, 110);
	drawBuilding(690, 100, 50, 90);
	double shift = windowX / 2;
	drawBuilding(0 + shift, 100, 50, 50);
	drawBuilding(50 + shift, 100, 50, 100);
	drawBuilding(100 + shift, 100, 100, 70);
	drawBuilding(200 + shift, 100, 50, 80);
	drawBuilding(250 + shift, 100, 50, 40);
	drawBuilding(300 + shift, 100, 60, 150);
	drawBuilding(360 + shift, 100, 50, 30);
	drawBuilding(410 + shift, 100, 70, 60);
	drawBuilding(480 + shift, 100, 50, 59);
	drawBuilding(530 + shift, 100, 30, 40);
	drawBuilding(560 + shift, 100, 80, 120);
	drawBuilding(640 + shift, 100, 50, 110);
	drawBuilding(690 + shift, 100, 50, 90);
	drawBuilding(710 + shift, 100, 55, 120);
	drawStar(50, 200);



	drawStar(50, windowY * 0.89);
	drawStar(120, windowY * 0.56);
	drawStar(200, windowY * 0.51);
	drawStar(210, windowY * 0.82);
	drawStar(250, windowY * 0.73);
	drawStar(600, windowY * 0.645);
	drawStar(750, windowY * 0.94);
	drawStar(790, windowY * 0.6378);
	drawStar(800, windowY * 0.354);
	drawStar(950, windowY * 0.460);


	drawStar(980, windowY * 0.89);
	drawStar(1120, windowY * 0.56);
	drawStar(1000, windowY * 0.51);
	drawStar(1100, windowY * 0.82);
	drawStar(1350, windowY * 0.73);
	drawStar(1400, windowY * 0.645);

	drawDove();
	drawCanary();

}
void Display() {

	glClearColor(1, 1, 1, 0.0f);//the background color is changed in the timer function after 1 sec by changing these parameters.
	glClear(GL_COLOR_BUFFER_BIT);

	drawBackground();

	if (batmanWin || supermanWin) {
		if (batmanWin) {
			drawBatman(400, 100, 200, 200);
		}
		else if (supermanWin) {
			drawSuperman(-500, 100, 200, 200);
		}
	}
	else {

		if (cloudX - 100 <= windowX) {
			drawCloud(0 + cloudX, 550 + movingCurrentArrow / 4.0, 100, 70, 40);
			drawCloud(100 + cloudX, 550 + movingCurrentArrow / 4.0, 100, 70, 40);
			if (lightTime > 0) {

				drawLightning(cloudX + 100, 450);
			}
			if (waterDropY > 0) {
				for (int i = 0; i < 12; ++i) {
					drawWaterDrop(waterDropX + double(i) * 25.0, i % 4 * 3 + waterDropY);
				}
			}

			else {
				waterDropY = 510;
				waterDropX = cloudX - 100;
			}
		}
		else {
			cloudX = 100;
		}
		if (regularBatman) {
			glPushMatrix();
			drawBatman();
			glPopMatrix();

		}
		else {
			glPushMatrix();
			drawBatman(20);
			drawAngerSign(double(batmanX) - 50, double(batmanY) + 120 + 20);
			drawAngerSign(double(batmanX) - 50, double(batmanY) - 120 + 20);
			drawAngerSign(double(batmanX) + 200, double(batmanY) + 120 + 20);
			drawAngerSign(double(batmanX) + 50, double(batmanY) + 20);
			glPopMatrix();

			glPushMatrix();
			glScalef(angryTime, angryTime, 0);
			drawAngerSign(double(batmanX) + 120, double(batmanY) + 120 + 20);
			glPopMatrix();
		}
		if (regularSuperman) {
			glPushMatrix();
			drawSuperman();
			glPopMatrix();
		}
		else {
			glPushMatrix();
			drawSuperman(20);
			drawAngerSign(double(supermanX) - 50, double(supermanY) + 120 + 20);
			drawAngerSign(double(supermanX) - 50, double(supermanY) - 120 + 20);
			drawAngerSign(double(supermanX) + 200, double(supermanY) + 120 + 20);
			drawAngerSign(double(supermanX) + 50, double(supermanY) + 20);
			glPopMatrix();

			glPushMatrix();
			glScalef(angryTime, angryTime, 0);
			drawAngerSign(double(supermanX) - 20, double(supermanY) + 120 + 20);
			glPopMatrix();
		}


		drawWall();


		if (disappearTime <= 0)
			drawMovingRod();


		glPushMatrix();
		drawHealthBarBatman();
		glPopMatrix();


		glPushMatrix();
		drawHealthBarSuperman();
		glPopMatrix();


		if (batmanTurn) {
			drawPowerLine(300, 300);
			drawCurrentArrow(batmanX + 25, batmanY + 100);
		}
		else {
			drawPowerLine(900, 300);
			drawCurrentArrow(supermanX + 25, supermanY + 100);

		}



		if (!isDown && hasBeenClicked) {
			glPushMatrix();
			drawProjectile();
			glPopMatrix();
		}

		if (flameTime > 0) {
			drawFlames(FX, FY);
		}

		//debug();

	}
	glFlush();
}

void setBatmanPoints() {
	p0[0] = batmanX + 100;
	p0[1] = batmanY - 100;

	p1[0] = batmanX + 100;
	p1[1] = batmanY - 100;

	p2[0] = batmanX + 100;
	p2[1] = batmanY - 100;

	p3[0] = batmanX + 100;
	p3[1] = batmanY - 100;
}

void setSupermanPoints() {
	p0[0] = supermanX - 50;
	p0[1] = supermanY - 100;

	p1[0] = supermanX - 50;
	p1[1] = supermanY - 100;

	p2[0] = supermanX - 50;
	p2[1] = supermanY - 100;

	p3[0] = supermanX - 50;
	p3[1] = supermanY - 100;
}


void Anim() {
	glutPostRedisplay();

	rot += 1.5;
	cloudX += 1;
	waterDropY -= 1;
	lightTime -= 0.01;
	//mciSendString("play sounds\\back.wav ", NULL, 0, NULL);

	/*if (lightTime > 0) {
		mciSendString("play sounds\\thunder.wav", NULL, 0, NULL);
	}*/
	DoveX += deltaDoveX;
	DoveY += deltaDoveY;
	if (DoveX < 0) {
		deltaDoveX = 0.1;
	}
	else if (DoveX > windowX) {
		deltaDoveX = -0.1;
	}
	if (DoveY < 0) {
		deltaDoveY = 0.1;
	}
	else if (DoveY > windowY) {
		deltaDoveY = -0.1;
	}

	canaryX += deltacanaryX;
	canaryY += deltacanaryY;
	if (canaryX < 0) {
		deltacanaryX = 0.1;
	}
	else if (canaryX > windowX) {
		deltacanaryX = -0.1;
	}
	if (canaryY < 0) {
		deltacanaryY = 0.1;
	}
	else if (canaryY > windowY) {
		deltacanaryY = -0.1;
	}

	if (disappearTime > 0) {
		disappearTime -= 0.005;
	}

	if (flameTime > 0) {
		flameTime -= 0.01;
	}
	else {
		FX = -1;
		FY = -1;
	}

	if (upward) {
		movingCurrentArrow += 0.1;
	}
	else {
		movingCurrentArrow -= 0.1;
	}

	if (movingCurrentArrow > 9) {
		upward = false;
	}
	else if (movingCurrentArrow < 0) {
		upward = true;
	}

	if (goRight) {
		movingRod += 1;
	}
	else {
		movingRod -= 1;
	}
	if (movingRod < 0) {
		goRight = true;
	}
	if (movingRod + 200 > windowX) {
		goRight = false;
	}

	if (collideWithObstacle(curX, curY)  || t >= 1) {
		finishTheShot = true;
		mciSendString("play sounds\\BAZOOKA+1.wav", NULL, 0, NULL);
	}
	if (collideWithOpponent(curX, curY)) {
		finishTheShot = true;
		mciSendString("play sounds\\BAZOOKA+1.wav", NULL, 0, NULL);
		mciSendString("play sounds\\Drone.wav", NULL, 0, NULL);

	}


	if (!regularBatman || !regularSuperman) {
		angryTime += 0.005;
		if (angryTime >= 4) {
			regularBatman = true;
			regularSuperman = true;
			angryTime = 1;
		}
	}


	if (!finishTheShot && !isDown && hasBeenClicked) {
		t += 0.002;
	}
	else {
		t = 0;
	}


	if (batmanTurn) {
		p1[1] += power / 70;
		p3[0] += power / 50;
		p2[0] += power / 50;
		p2[1] += power / 70;
	}
	else {
		p2[1] += power / 70;
		p0[0] -= power / 50;
		p1[0] -= power / 50;
		p1[1] += power / 70;
	}
	if (isDown) {
		power += 1;
		mciSendString("play sounds\\Missile+2.wav", NULL, 0, NULL);
	}
	else {
		power = 0;
		if (hasBeenClicked && finishTheShot) {
			if (batmanTurn && healthSuperman <= 0) {
				batmanWin = true;
			}
			else if (!batmanTurn && healBatman <= 0) {
				supermanWin = true;
			}
			batmanTurn = !batmanTurn;
			if (batmanTurn) {
				setBatmanPoints();
			}
			else {
				setSupermanPoints();
			}
			hasBeenClicked = false;
			finishTheShot = false;
			curX = 0; curY = 0;
		}
	}


}

void mouseAction(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			isDown = true;
			hasBeenClicked = true;
		}
		else {
			isDown = false;
		}
	}

}

void main(int argc, char** argr) {
	glutInit(&argc, argr);

	setBatmanPoints();

	glutInitWindowSize(windowX, windowY);
	glutInitWindowPosition(10, 100);

	glutCreateWindow("BatmanVsSuperman");
	glutDisplayFunc(Display);
	//glutpassivemotionfunc(passm);	//call the passive motion function
	glutMouseFunc(mouseAction);			//call the mouse function
	//glutkeyboardfunc(key);			//call the keyboard function
	//glutkeyboardupfunc(keyup);		//call the keyboard up function
	//glutspecialfunc(spe);			//call the keyboard special keys function
	//glutspecialupfunc(speup);		//call the keyboard special keys up function
	glutIdleFunc(Anim);
	//change the point size to be 25
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, windowX, 0.0, windowY);
	glutTimerFunc(0, lightningSetter, 0);
	glutMainLoop();//don't call any method after this line as it will not be reached.
}
