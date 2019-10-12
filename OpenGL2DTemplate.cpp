#include <stdlib.h> 
#include <glut.h>
#include <math.h>
#include <string.h>
#include <stdio.h>


//2) put moving things 
int windowY = 700;
int windowX = 1500;

// variables for handling the moving rod ; 
double movingRod = 0;
bool goRight = true;

// to know which turn is it ; 
bool catTurn = true; // true means -> cat  ; 

int catX = 150;
int catY = 150;
int dogX = 1150;
int dogY = 150;

int p0[2]; // catPos
int p1[2]; // catControl 
int p2[2]; // dogControl ; 
int p3[2];//dogPos  ;

// to check if iam pressing the mouse to shoot 
bool isDown = false;
// the amount of power given 
int power = 0;

double t = 0;

bool hasBeenClicked = false;
bool finishTheShot = false;
// to check  if the cat of the dog has been attacked  
bool regularCat = true;
bool regularDog = true;

// to set the time which the cat or the dog will be angry 
double angryTime = 1;


// health of competetors 
int healthDog = 240;
int healCat = 240;

// current position of the projectile ; 
int curX = 0;
int curY = 0;

// to track the winners ;
bool catWin = false;
bool dogWin = false;

double waterDropY = 510;
double waterDropX = 0;
double cloudX = 100;
double lightTime = 4.5;

double movingCurrentArrow = 0; 
bool upward = true; 
void drawCircle(double cx, double cy, double r, int acc, double red, double green, double blue) {

	// for cute eyes ; 
	//glBegin(GL_POINTS);
	//glColor3f(red, green, blue);
	//for (int i = 0; i < acc / 4; i++) {
	//	double theta = 2.0f * 3.14159265359 * double(i) / double(acc);
	//	double x = cx + r * cosf(theta);
	//	double y = cy + r * sinf(theta);

	//	glVertex3f(x, y, 0);
	//}

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




void drawBird(double x, double y, double r, double g, double b) {
	double width = 50;
	double height = 50;
	glBegin(GL_POLYGON);
	glColor3f(r,g,b);
	glVertex3f(x, y, 0);
	glVertex3f(x + width, y, 0);
	glVertex3f(x + width, y + height, 0);
	glVertex3f(x, y + height, 0);
	glEnd();

	drawEllipse(x, y+height/2 + movingCurrentArrow / 4.0, 20, 10, 20, r,g,b);
	drawEllipse(x+width, y + height / 2 + movingCurrentArrow/4.0, 20, 10, 20, r,g,b);

	drawCircle(x +width/3.0, y+3*height/4.0, 5, 10, 1, 1, 1);
	drawCircle(x + 2*width / 3.0, y + 3 * height / 4.0, 5, 10, 1, 1, 1);

	// draw iris 
	glPointSize(2); 
	glColor3f(0, 0, 0); 
	glBegin(GL_POINTS); 
	glVertex2f(x + width / 3.0, y + 3 * height / 4.0);
	glVertex2f(x + 2*width / 3.0, y + 3 * height / 4.0);

	glEnd(); 

	glColor3f(0.647, 0.286, 0.165); // brown  ; 

	glBegin(GL_TRIANGLES); 
	glVertex2f(x + width / 2.0 -7 , y +   height / 4.0+3);
	glVertex2f(x + width / 2.0 + 7 , y +  height / 4.0+3);
	glVertex2f(x + width / 2.0, y +  height / 4.0 + 10);


	glVertex2f(x + width / 2.0 - 7, y + height / 4.0 + 3);
	glVertex2f(x + width / 2.0 + 7, y + height / 4.0 + 3);
	glVertex2f(x + width / 2.0, y + height / 4.0 -4);
	
	glEnd(); 

	glBegin(GL_LINES); 
	glVertex2f(x + width/3 , y); 
	glVertex2f(x + width / 3, y-10);


	glVertex2f(x + width / 3, y-5);
	glVertex2f(x + width / 3-6, y - 7);


	glVertex2f(x + width / 3, y - 5);
	glVertex2f(x + width / 3 + 6, y - 7);


	glVertex2f(x + 2*width / 3, y);
	glVertex2f(x + 2*width / 3, y - 10);


	glVertex2f(x + 2*width / 3, y - 5);
	glVertex2f(x + 2*width / 3 - 6, y - 7);


	glVertex2f(x + 2*width / 3, y - 5);
	glVertex2f(x + 2*width / 3 + 6, y - 7);

	glEnd(); 

}

double DoveX = 500;
double DoveY = 700;
double deltaDoveX = -0.1;
double deltaDoveY = 0.1;


double canaryX = 100;
double canaryY = 500;
double deltacanaryX = 0.1;
double deltacanaryY = -0.1;
void drawDove()
{
	drawBird(DoveX,DoveY, 0, 0.512, 1);
}
void drawCanary() {
	drawBird(canaryX, canaryY, 1, 0.749, 0);
}
void drawCat(int shift = 0) {
	int x = catX;
	int y = catY + shift;
	int width = 100;
	int height = 100;
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.6, 0.44);
	glVertex3f(x, y, 0);
	glVertex3f(x + width, y, 0);
	glVertex3f(x + width, y + height, 0);
	glVertex3f(x, y + height, 0);
	glEnd();

	glPointSize(25);
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	glVertex3f(x, y + height, 0);
	glVertex3f(x + width, y + height, 0);
	glEnd();


	// to draw a nose; 
	double noseX = x + double(width / 2);
	double noseY = y + double(height / 4);
	glBegin(GL_TRIANGLES);
	glColor3f(0.7, 0.6, 0.4);
	glVertex3f(noseX - 10, noseY, 0);
	glVertex3f(noseX + 10, noseY, 0);
	glVertex3f(noseX, noseY + 10, 0);
	glEnd();


	// to draw mustaches ; 
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(noseX + 10, noseY, 0);
	glVertex3f(noseX + 20, noseY, 0);
	glVertex3f(noseX - 10, noseY, 0);
	glVertex3f(noseX - 20, noseY, 0);
	glVertex3f(noseX - 5, noseY + 5, 0);
	glVertex3f(noseX - 15, noseY + 5, 0);
	glVertex3f(noseX + 5, noseY + 5, 0);
	glVertex3f(noseX + 15, noseY + 5, 0);
	glEnd();

	// draw leftEye
	drawCircle(noseX - 20, noseY + 30, 10, 20, 1, 1, 1);
	// draw iris 
	drawCircle(noseX - 20, noseY + 30, 4, 20, 0, 0, 0);

	//drawRightEye ; 
	drawCircle(noseX + 20, noseY + 30, 10, 20, 1, 1, 1);
	drawCircle(noseX + 20, noseY + 30, 4, 20, 0, 0, 0);

}



void drawDog(int shift = 0) {
	int x = dogX;
	int y = dogY + shift;
	int width = 100;
	int height = 100;
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.6, 0.44);
	glVertex3f(x, y, 0);
	glVertex3f(x + width, y, 0);
	glVertex3f(x + width, y + height, 0);
	glVertex3f(x, y + height, 0);
	glEnd();

	//drawing ears 
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	glVertex3f(x - 20 / 1.4 + 1, y + height - 20 / 1.4 - 1, 0);
	glVertex3f(x + 1, y + height - 1, 0);
	glVertex3f(x - 20 + 1, y + height + 20 - 1, 0);
	glVertex3f(x - 20 / 1.4 - 20 + 1, y + height - 20 / 1.4 + 20 - 1, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	glVertex3f(x + width - 1, y + height - 1, 0);
	glVertex3f(x + width + 20 / 1.4 - 1, y + height - 20 / 1.4 - 1, 0);
	glVertex3f(x + width + 20 / 1.4 + 20 - 1, y + height - 20 / 1.4 + 20 - 1, 0);
	glVertex3f(x + width + 20 - 1, y + height + 20 - 1, 0);


	glEnd();
	// to draw a nose; 
	double noseX = x + double(width / 2.0);
	double noseY = y + double(height / 4.0);
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.2, 0.7);
	glVertex3f(noseX - 10, noseY, 0);
	glVertex3f(noseX + 10, noseY, 0);
	glVertex3f(noseX + 10, noseY + 20, 0);
	glVertex3f(noseX - 10, noseY + 20, 0);
	glEnd();


	// to draw mustaches ; 
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);

	glVertex3f(noseX + 10, noseY, 0);
	glVertex3f(noseX + 20, noseY, 0);

	glVertex3f(noseX + 10, noseY + 10, 0);
	glVertex3f(noseX + 20, noseY + 10, 0);

	glVertex3f(noseX - 10, noseY, 0);
	glVertex3f(noseX - 20, noseY, 0);

	glVertex3f(noseX - 10, noseY + 10, 0);
	glVertex3f(noseX - 20, noseY + 10, 0);
	glEnd();

	// draw leftEye
	drawCircle(noseX - 20, noseY + 30, 10, 20, 1, 1, 1);
	drawCircle(noseX - 20, noseY + 30, 4, 20, 0, 0, 0);

	//drawRightEye ; 
	drawCircle(noseX + 20, noseY + 30, 10, 20, 1, 1, 1);
	drawCircle(noseX + 20, noseY + 30, 4, 20, 0, 0, 0);

}
//void drawCurve(double cx, double cy, double r, int acc, double boundX, double boundY , int quad) {
//
//	glPointSize(1);
//	glBegin(GL_POINTS);
//	glColor3f(1, 0, 0);
//	for (int i = 0; i < acc; i++) {
//		double theta = 2.0f * 3.14159265359 * double(i) / double(acc);
//		double x = cx + r * cosf(theta);
//		double y = cy + r * sinf(theta);
//		bool cond0 = x >= cx && x <= boundX && y <= cy && cy >= boundY && quad ==1; // left top
//		
//		
//		bool cond1 = x >= cx && x <= boundX && y >= cy && cy <= boundY && quad == 2; //left down
//		
//		bool cond2 = x <= cx && x >= boundX && y <= cy && cy >= boundY && quad == 3; // right top 
//
//		bool cond3 = x <= cx && x >= boundX && y >= cy && cy <= boundY && quad == 4 ; // right down 
//	
//		if (cond0 || cond1 || cond2 || cond3 )
//			glVertex3f(x, y, 0);
//	}
//
//
//	glEnd();
//}

void drawCurve(double cx, double cy, double r, int acc,  int quad) {

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
	glColor3f(1,0,0); 
	glVertex3f(x, y, 0);  // left top 
	glVertex3f(x, y - lineLen , 0);

	glVertex3f(x - width - lineLen, y - lineLen - width, 0);
	glVertex3f(x - width, y - lineLen - width, 0);

	glVertex3f(x, y-lineLen-2*width-5, 0);  // left down 
	glVertex3f(x, y - 2*lineLen -2*width-5 , 0);

	glVertex3f(x - width - lineLen, y - lineLen - width - 5, 0);
	glVertex3f(x - width, y - lineLen - width - 5, 0);

	glVertex3f(x+5, y, 0); // right top 
	glVertex3f(x+5, y - lineLen, 0);

	glVertex3f(x + width + 5 + lineLen, y - lineLen - width, 0);
	glVertex3f(x + width + 5 , y - lineLen - width, 0);


	glVertex3f(x + 5, y - lineLen - 2 * width - 5, 0);  // right down 
	glVertex3f(x + 5 , y - 2 * lineLen - 2 * width - 5, 0);

	glVertex3f(x + width + 5 + lineLen, y - lineLen - width - 5, 0);
	glVertex3f(x + width + 5, y - lineLen - width - 5 , 0);

	glEnd();
	// note the order of curves is not the order of the signs ; 
	drawCurve(x - width, y - lineLen, width, 40, 4); // left top 

	drawCurve(x - width, y - lineLen - 2 * width - 5, width, 40, 1); // left down  

	drawCurve(x + width+5, y - lineLen, width, 40,  3); // right top  

	drawCurve(x + width + 5, y - lineLen - 2*width - 5 , width, 40,2); // right down  


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

}

void drawMovingRod() {

	glBegin(GL_POLYGON);
	glColor3f(0.25, 0.77, 0.9);
	glVertex3f(movingRod, windowY / 2 + 60, 0);
	glVertex3f(movingRod + 200, windowY / 2 + 60, 0);
	glVertex3f(movingRod + 200, windowY / 2 + 100, 0);
	glVertex3f(movingRod, windowY / 2 + 100, 0);
	glEnd();


}

void drawHealthBarCat() {
	int x = 10;
	int y = windowY - 40;
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex3f(x, y, 0);
	glVertex3f(x + healCat, y, 0);
	glVertex3f(x + healCat, y + 30, 0);
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

void drawHealthBarDog() {
	int x = windowX - 10 - healthDog;
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
	glVertex3f(windowX-10-240, y, 0);
	glVertex3f(windowX - 10, y, 0);
	glVertex3f(windowX - 10, y + 30, 0);
	glVertex3f(windowX-10-240, y + 30, 0);

	glEnd();
}




void drawPowerLine(int x , int y ) {

	int len = fmin(power , 1200); 

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
		b = 0.5 -len/2400.0 ; 
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
		b = 0.2- len / 6000.0; 
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


void printt(int x, int y, char* string)
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
	if ((x >= xx - 15 && x <= xx + 15 && y >= 0 && y <= 400) || (x >= movingRod && x <= movingRod + 200 && y >= windowY / 2 + 60 && y <= windowY / 2 + 100) || x<0 || x>windowX || y<0 || y>windowY) {
		return true;
	}
	return false;
}


bool collideWithOpponent(int x, int y) {
	if (catTurn) {
		if (x >= dogX && x <= dogX + 100 && y >= dogY && y <= dogY + 100) {
			regularDog = false;
			healthDog -= 10;
			return true;
		}
	}
	else {
		if (x >= catX && x <= catX + 100 && y >= catY && y <= catY + 100) {
			regularCat = false;
			healCat -= 10;
			return true;
		}
	}
	return false;
}

void drawProjectile() {


	//glPushMatrix();
	glPointSize(15);
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	if (!catTurn) {
		bezier(t, p3, p2, p1, p0);
		glVertex3f(curX, curY, 0);
	}
	else {
		bezier(t, p0, p1, p2, p3);
		glVertex3f(curX, curY, 0);
	}
	glEnd();
	//glPopMatrix();
	/*glPointSize(9);
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	glVertex3f(p0[0], p0[1], 0);
	glColor3f(0, 1, 0);
	glVertex3f(p1[0], p1[1], 0);
	glColor3f(0, 0, 1);
	glVertex3f(p2[0], p2[1], 0);
	glColor3f(1, 1, 1);
	glVertex3f(p3[0], p3[1], 0);
	glEnd();*/


}

void drawCurrentArrow(int x, int y) {

	int width = 10; 
	int height = 30; 
	glBegin(GL_POLYGON); 
	glColor3f(1,0.5,0.1); 
	glVertex3f(x,y+movingCurrentArrow,0); 
	glVertex3f(x+width, y+movingCurrentArrow, 0);
	glVertex3f(x+width, y+height+ movingCurrentArrow, 0);
	glVertex3f(x, y+height+movingCurrentArrow, 0);
	glEnd(); 

	int edge = 10; 
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0.5, 0.1);
	glVertex3f(x-edge, y+movingCurrentArrow, 0);
	glVertex3f(x+edge/2, y-15+movingCurrentArrow, 0);
	glVertex3f(x+width+edge, y+movingCurrentArrow, 0);
	glEnd(); 


}


void drawCloud(double cx, double cy, double rx, double ry, int num_segments)
{ 
	drawEllipse(cx, cy, rx, ry, num_segments, 0.5, 0.5, 0.5); 
}


void drawBushes() {

	drawEllipse(0, 0, 350, 100, 40, 0, 0.702, 0);
	drawEllipse(500, 20, 200, 50, 40, 0, 0.804, 0);
	drawEllipse(1100, 10, 500, 50 , 40, 0, 0.506, 0);
}


void drawSun() {
	double cx = 100; 
	double cy = 200; 
	double r = 100; 
	drawCircle(  cx, windowY - cy, r, 20,1,1,0); 
	drawCircle(cx- r/2,windowY-cy+r/3.0,10,10,0,0,0 ); 
	drawCircle(cx + r / 2, windowY - cy + r / 3.0, 10, 10, 0, 0, 0);
	double rc = 60; 
	drawCurve(cx, windowY - cy, rc, 20, 3);
	drawCurve(cx, windowY - cy, rc, 20, 4);
}
void drawWaterDrop(double x  , double y ) {
	double r = 10; 
	drawCircle(x, y, r, 40, 0.5, 59.2, 1);
	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 59.2, 1);
	glVertex2f(x-r , y); 
	glVertex2f(x+r , y );
	glVertex2f(x , y+2.2*r);
	glEnd(); 
}

void drawLightning(int x , int  y ) {

	glBegin(GL_POLYGON); 
	glColor3f(0.99,0.86,0.1); 
	glVertex3f(x,y,0); 
	glVertex3f(x+20, y, 0);
	glVertex3f(x+40, y+40, 0);
	glVertex3f(x+20, y+40, 0);

	glEnd(); 

	glBegin(GL_TRIANGLES);
	glVertex3f(x+15, y+10, 0);
	glVertex3f(x -5, y-40, 0);
	glVertex3f(x + 35, y+10 , 0);


	glEnd();

}

void lightningSetter(int val)
{
	lightTime = 4.5; 
	glutTimerFunc(4000, lightningSetter, 0);
}



void Display() {

	glClearColor(1, 1, 1, 0.0f);//the background color is changed in the timer function after 1 sec by changing these parameters.
	glClear(GL_COLOR_BUFFER_BIT);

	if (catWin || dogWin) {
		if (catWin) {

		}
		else if (dogWin) {

		}
	}
	else {
		
	
		if (cloudX <= windowX) {
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
			drawBushes();
			drawSun();
			drawDove();
			drawCanary(); 
		}
		if (regularCat) {
			glPushMatrix();
			drawCat();
			glPopMatrix();

		}
		else {
			glPushMatrix();
			drawCat(20);
			drawAngerSign(double(catX) - 50, double(catY) + 120 + 20);
			drawAngerSign(double(catX) - 50, double(catY) - 120 + 20);
			drawAngerSign(double(catX) + 200, double(catY) + 120 + 20);
			drawAngerSign(double(catX) + 50, double(catY)  + 20);
			glPopMatrix();

			glPushMatrix();
			glScalef(angryTime, angryTime, 0);
			drawAngerSign(double(catX) + 120, double(catY) + 120 + 20);
			glPopMatrix();
		}
		if (regularDog) {
			glPushMatrix();
			drawDog();
			glPopMatrix();
		}
		else {
			glPushMatrix();
			drawDog(20);
			drawAngerSign(double(dogX) - 50, double(dogY) + 120 + 20);
			drawAngerSign(double(dogX) - 50, double(dogY) - 120 + 20);
			drawAngerSign(double(dogX) + 200, double(dogY) + 120 + 20);
			drawAngerSign(double(dogX) + 50, double(dogY) + 20);
			glPopMatrix();

			glPushMatrix();
			glScalef(angryTime, angryTime, 0);
			drawAngerSign(double(dogX) -20, double(dogY) + 120 + 20);
			glPopMatrix();
		}


		drawWall();



		drawMovingRod();


		glPushMatrix();
		drawHealthBarCat();
		glPopMatrix();


		glPushMatrix();
		drawHealthBarDog();
		glPopMatrix();


		if (catTurn) {
			drawPowerLine(300,300);
			drawCurrentArrow(catX + 50, catY + 150); 
		}
		else  {
			drawPowerLine(900,300); 
			drawCurrentArrow(dogX + 50, dogY + 150);

		}



		if (!isDown && hasBeenClicked) {
			glPushMatrix();
			drawProjectile();
			glPopMatrix();
		}





		glFlush();
	}
}

void setTheCatPoints() {
	p0[0] = catX + 100;
	p0[1] = catY;

	p1[0] = catX + 100;
	p1[1] = catY;

	p2[0] = catX + 100;
	p2[1] = catY;

	p3[0] = catX + 100;
	p3[1] = catY;
}
void setTheDogPoints() {
	p0[0] = dogX;
	p0[1] = dogY;

	p1[0] = dogX;
	p1[1] = dogY;

	p2[0] = dogX;
	p2[1] = dogY;

	p3[0] = dogX;
	p3[1] = dogY;
}

void Anim() {
	glutPostRedisplay();
	cloudX += 0.1; 
	waterDropY -= 1; 
	lightTime -= 0.01; 


	DoveX += deltaDoveX; 
	DoveY += deltaDoveY; 
	if (DoveX < 0) {
		deltaDoveX = 0.1 ;
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

	if (collideWithObstacle(curX, curY) || collideWithOpponent(curX, curY) || t >= 1) {
		finishTheShot = true;
	}


	if (!regularCat || !regularDog) {
		angryTime += 0.005;
		if (angryTime >= 4) {
			regularCat = true;
			regularDog = true;
			angryTime = 1;
		}
	}

	if (!finishTheShot && !isDown) {
		t += 0.001;
	}
	else {
		t = 0;
	}

	if (catTurn) {
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
	}
	else {
		power = 0;
		if (hasBeenClicked && finishTheShot) {
			if (catTurn && healthDog <= 0) {
				catWin = true;
			}
			else if (!catTurn && healCat <= 0) {
				dogWin = true;
			}
			catTurn = !catTurn;
			if (catTurn) {
				setTheCatPoints();
			}
			else {
				setTheDogPoints();
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

	setTheCatPoints();

	glutInitWindowSize(windowX, windowY);
	glutInitWindowPosition(10, 100);

	glutCreateWindow("hey");
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
