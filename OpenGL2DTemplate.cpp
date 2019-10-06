#include <glut.h>
#include <math.h>

int windowY = 700;
int windowX = 1500; 
double movingRod = 0; 
bool goRight = true; 
bool takeTurns = true; // true means -> cat  ; 

int catX = 150; 
int catY = 150; 
int dogX = 1150; 
int dogY = 150; 

int p0[2]; // catPos
int p1[2]; // catControl 
int p2[2]; // dogControl ; 
int p3[2];//dogPos  ;


int power = 0; 

//int passX = 0;
//int passY = 0;
//
//int actX = 0;
//int actY = 0;
//
//int keyX = 0;
//int keyY = 0;
//int keyC = 0;
//
//int speX = 0;
//int speY = 0;
//int speC = 0;





void drawCircle(double cx, double cy, double r, int acc, double red , double green , double blue) {

	glBegin(GL_LINE_LOOP);
	glColor3f(red, green, blue);
	for (int i = 0; i < acc; i++) {
		double theta = 2.0f * 3.14159265359 * double(i) / double(acc); 
		double x = cx + r * cosf(theta); 
		double y = cy + r * sinf(theta); 
		
		glVertex3f(x , y , 0 ); 
	}


	glEnd(); 
}
void drawCat() {
	int x = catX; 
	int y = catY; 
	int width = 100; 
	int height = 100; 
	glBegin(GL_POLYGON); 
	glColor3f(0.5, 0.6, 0.44); 
	glVertex3f(x, y, 0); 
	glVertex3f(x+width, y, 0);
	glVertex3f(x+width, y+height, 0);
	glVertex3f(x, y+height, 0);
	glEnd(); 


	glBegin(GL_POINTS); 
	glColor3f(0, 0, 0); 
	glVertex3f(x, y+height, 0); 
	glVertex3f(x+width, y + height, 0);
	glEnd(); 


	// to draw a nose; 
	double noseX = x + double(width / 2); 
	double noseY = y + double(height / 4); 
	glBegin(GL_TRIANGLES); 
	glColor3f(0.7, 0.6, 0.4); 
	glVertex3f(noseX - 10  , noseY, 0 );
	glVertex3f(noseX + 10, noseY, 0);
	glVertex3f(noseX, noseY +10, 0);
	glEnd(); 


	// to draw mustaches ; 
	glBegin(GL_LINES); 
	glColor3f(0, 0, 0); 
	glVertex3f(noseX + 10, noseY, 0);
	glVertex3f(noseX + 20, noseY, 0);
	glVertex3f(noseX-10 , noseY, 0);
	glVertex3f(noseX -20, noseY, 0);
	glVertex3f(noseX - 5, noseY+5, 0);
	glVertex3f(noseX - 15, noseY+5, 0);
	glVertex3f(noseX + 5, noseY + 5, 0);
	glVertex3f(noseX + 15, noseY + 5, 0);
	glEnd(); 

	// draw leftEye
	drawCircle(noseX - 20, noseY + 30, 10, 20,1,1,1); 

	//drawRightEye ; 
	drawCircle(noseX + 20, noseY + 30, 10, 20,1,1,1);
}


void drawDog() {
	int x = dogX;
	int y = dogY;
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
	glVertex3f(x-20/1.4+1, y + height - 20/1.4-1, 0);
	glVertex3f(x+1 , y + height -1, 0);
	glVertex3f(x-20+1, y + height + 20-1 , 0);
	glVertex3f(x - 20 / 1.4 - 20 + 1, y + height - 20 / 1.4 + 20 -1, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	glVertex3f(x +width - 1 , y + height - 1, 0);
	glVertex3f(x + width+20 / 1.4 -1  , y + height - 20 / 1.4 - 1 , 0);
	glVertex3f(x + width+20 / 1.4 + 20 - 1  , y + height - 20 / 1.4 + 20 - 1 , 0);
	glVertex3f(x +width+ 20 - 1  , y + height + 20 - 1  , 0);


	glEnd();
	// to draw a nose; 
	double noseX = x + double(width / 2.0);
	double noseY = y +double( height / 4.0);
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.2, 0.7);
	glVertex3f(noseX - 10, noseY, 0);
	glVertex3f(noseX + 10, noseY, 0);
	glVertex3f(noseX + 10, noseY+20, 0);
	glVertex3f(noseX-10, noseY + 20, 0);
	glEnd();


	// to draw mustaches ; 
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);

	glVertex3f(noseX + 10, noseY, 0);
	glVertex3f(noseX + 20, noseY, 0);

	glVertex3f(noseX + 10, noseY+10, 0);
	glVertex3f(noseX + 20, noseY+10, 0);

	glVertex3f(noseX - 10, noseY, 0);
	glVertex3f(noseX - 20, noseY , 0);

	glVertex3f(noseX - 10, noseY + 10, 0);
	glVertex3f(noseX - 20, noseY + 10, 0);
	glEnd();

	// draw leftEye
	drawCircle(noseX - 20, noseY + 30, 10, 20, 1, 1, 1);

	//drawRightEye ; 
	drawCircle(noseX + 20, noseY + 30, 10, 20, 1, 1, 1);
}
void drawRod() {
	int x = windowX / 2; 
	

	glBegin(GL_POLYGON); 
	glColor3f(0.2,0.8,0.47); 
	glVertex3f(x-15 , 0 , 0 ); 
	glVertex3f(x + 15, 0, 0);
	glVertex3f(x + 15, 400, 0);
	glVertex3f(x - 15, 400, 0);
	glEnd(); 

}
void drawMovingRod() {
	
	glBegin(GL_POLYGON); 
	glColor3f(0.25, 0.77, 0.9);
	glVertex3f(movingRod , windowY/2+60 , 0 );
	glVertex3f(movingRod+200, windowY / 2+60, 0);
	glVertex3f(movingRod +200, windowY / 2+100, 0);
	glVertex3f(movingRod , windowY / 2+100, 0);
	glEnd(); 
	

}

void drawHealthBarCat() {
	int x = 10; 
	int y = windowY - 40; 
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex3f(x, y , 0);
	glVertex3f(x+240, y, 0);
	glVertex3f(x+240, y+30, 0);
	glVertex3f(x, y+30, 0);
	glEnd();
}

void drawHealthBarDog() {
	int x = windowX - 10 -240;
	int y = windowY - 40;
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex3f(x, y, 0);
	glVertex3f(x + 240, y, 0);
	glVertex3f(x + 240, y + 30, 0);
	glVertex3f(x, y + 30, 0);
	glEnd();
}

int* bezier(float t, int* p0, int* p1, int* p2, int* p3)
{
	int res[2];
	res[0] = pow((1 - t), 3) * p0[0] + 3 * t * pow((1 - t), 2) * p1[0] + 3 * pow(t, 2) * (1 - t) * p2[0] + pow(t, 3) * p3[0];
	res[1] = pow((1 - t), 3) * p0[1] + 3 * t * pow((1 - t), 2) * p1[1] + 3 * pow(t, 2) * (1 - t) * p2[1] + pow(t, 3) * p3[1];
	return res;
}

void drawProjectile() {

	glColor3f(1, 0, 0);

	glColor3f(0, 1, 0);

	glColor3f(0, 0, 1);

	glColor3f(1, 1, 1);

	glPointSize(1);
	glColor3f(1, 1, 0);
	glBegin(GL_POINTS);
	for (float t = 0; t < 1; t += 0.001)
	{
		int* p = bezier(t, p0, p1, p2, p3);
		glVertex3f(p[0], p[1], 0);
	}
	glEnd();
	glPointSize(9);
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	glVertex3f(p0[0], p0[1], 0);
	glColor3f(0, 1, 0);
	glVertex3f(p1[0], p1[1], 0);
	glColor3f(0, 0, 1);
	glVertex3f(p2[0], p2[1], 0);
	glColor3f(1, 1, 1);
	glVertex3f(p3[0], p3[1], 0);
	glEnd();
}


void drawPowerLine() {
	int x = 300;
	int y = 300;
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex3f(x, y, 0);
	glVertex3f(x + power, y, 0);
	glVertex3f(x + power, y + 30, 0);
	glVertex3f(x, y + 30, 0);
	glEnd();
}

void Display() {

	glClearColor(1 , 1 , 1 , 0.0f);//the background color is changed in the timer function after 1 sec by changing these parameters.
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix(); 
	drawCat(); 
	glPopMatrix(); 

	glPushMatrix();
	drawDog();
	glPopMatrix();

	glPushMatrix();
	drawRod();
	glPopMatrix();

	glPushMatrix();
	drawMovingRod();
	glPopMatrix();

	glPushMatrix();
	drawHealthBarCat();
	glPopMatrix();


	glPushMatrix();
	drawHealthBarDog();
	glPopMatrix();

	glPushMatrix();
	drawPowerLine(); 
	glPopMatrix();


	

	glFlush();
}


void Anim() {
	glutPostRedisplay(); 
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
}

void mouseAction(int button, int state, int x, int y) {

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		power += 5; 
	}

}
void main(int argc, char** argr) {
	glutInit(&argc, argr);
	p0[0] = catX;
	p0[1] = catY;

	p1[0] = catX;
	p1[1] = catY;

	p2[0] = catX;
	p2[1] = catY;

	p3[0] = catX;
	p3[1] = catY;
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
	glPointSize(25);				//change the point size to be 25
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, windowX, 0.0, windowY);

	glutMainLoop();//don't call any method after this line as it will not be reached.
}
