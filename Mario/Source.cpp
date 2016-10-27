#include <iostream>
#include <sstream>
#include <glut.h>
#include"RGBA.h"
#include"Ralph.h"
#include"Mario.h"

float iMy = 100;
void progressBar(void);
void drawBox(void);
static Mario m(Point2(0, 0));
Ralph r(Point2R(655, 0));
RGBApixmap backGr[24];
RGBApixmap box;
void keyReleased(char key, int x, int y);
int cut = 0;
 int KenForce = 50;
 int KenMass = 25;
 int KenInitalVelocity = 0;
 int KenFinalVelocity = 0;
 int KenRunTime = 1;
 int KenInitialPostion = 0;
 int KenFinalPosition = 0;
 int KenAcceleration = KenForce / KenMass;
 int RalphForce = 50;
 int RalphMass = 25;
 int RalphInitalVelocity = 0;
 int RalphFinalVelocity = 0;
 int RalphRunTime = 1;
 int RalphInitialPostion = 0;
 int RalphFinalPosition = 0;

 int RalphAcceleration = RalphForce / RalphMass;
void myInit(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 750, 0, 480);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL, 1.0);

	for (int i = 0; i < 24; i++)
	{
		std::string result = "b" + std::to_string(i);
		result = result + ".bmp";
		backGr[i].readBMPFile(result);
		backGr[i].setChromaKey(192, 192, 192);
	}
	box.readBMPFile("box.bmp");
	box.setChromaKey(192, 192, 192);


	m.changeMode(Mario::STAY);
	r.changeMode(Ralph::STAY);

	
}

void progressBarRalph()
{
	int value = 0;
	r.getHealth();
	 value = r.getHealth();  // on hit we need to increment the value
	int progress = iMy - value;
	// value must not be greater than 100 if it is greater than game will be over
	// and must not less than  if it is less then it will be drawn outside the  bar


	if (progress <= 100 & progress >= 40) // Green 
		glColor3f(0.3, 0.9, 0.2);

	else if (progress <= 30 & progress >-20) // Red when life is low
		glColor3f(0.9, 0.0, 0.0);

	//  Life Bar
	glBegin(GL_QUADS);
	glVertex2f(-91 + iMy, 84);
	glVertex2f(-89, 84);
	glVertex2f(-89, 71);
	glVertex2f(-91 + iMy, 71);
	glEnd();

	// Bar that decrease life bar
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_QUADS);
	if (progress>-20)
	{
		glVertex2f(-91 + iMy - progress, 84);
		glVertex2f(-89, 84);
		glVertex2f(-89, 71);
		glVertex2f(-91 + iMy - progress, 71);
	}
	//else print game over
	glEnd();

}
void progressBarKen()
{

	int value = m.HealthValue;  // on hit we need to increment the value
	int progress = iMy - value;
	// value must not be greater than 100 if it is greater than game will be over
	// and must not less than  if it is less then it will be drawn outside the  bar


	if (progress <= 100 & progress >= 40) // Green 
		glColor3f(0.3, 0.9, 0.2);

	else if (progress <= 30 & progress >-20) // Red when life is low
		glColor3f(0.9, 0.0, 0.0);

	//  Life Bar
	glBegin(GL_QUADS);
	glVertex2f(-91 + iMy, 109);
	glVertex2f(-89, 109);
	glVertex2f(-89, 96);
	glVertex2f(-91 + iMy, 96);
	glEnd();

	// Bar that decrease life bar
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_QUADS);
	if (progress>-20)
	{
		glVertex2f(-91 + iMy, 109);
		glVertex2f(-89 + progress, 109);
		glVertex2f(-89 + progress, 96);
		glVertex2f(-91 + iMy, 96);
	}
	//else print game over
	glEnd();

}
void bkChange(int ct)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPixelZoom(1.35, 2);

	glRasterPos2i(0, 0);
	//drawBox();
	
	backGr[ct].mDraw();
	
	glPushMatrix();
	glTranslatef(110,300,0);
	progressBarKen();
	glPopMatrix();
	glFlush();
	//glPixelZoom(5, 5);


	glPushMatrix();
	glTranslatef(700, 325, 0);
	progressBarRalph();
	glPopMatrix();
	glFlush();

	m.render();

	///glFlush();
	r.render();
	//	glPixelZoom(5, 5);
	//progressBar();

	glFlush();

	glutSwapBuffers();
}

void drawBox(){
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL, 1.0);
	glPixelZoom(2, 2);
	box.mDraw();

}

void progressBar(){

	glRasterPos2i(0, 450);
	drawBox();
}

void keyPressed(unsigned char key, int x, int y) {
	static int i = 1; int a = 0;

	switch (key)
	{
	case 'a':

		i = m.pos_X;
		if (i <= 0)
			m.changePosition(0, 0);
		else
		{
			KenRunTime += 1;
			KenFinalVelocity = KenFinalVelocity + (KenAcceleration * KenRunTime);
			KenFinalPosition = KenFinalPosition + (KenFinalVelocity * KenRunTime);
			if (KenFinalPosition > 55) KenFinalPosition = 25;
			
			m.setPositionBackward(KenFinalPosition, 0);
		}
		m.changeMode(Mario::RUN);
		break;

	case 'z':
		i = m.pos_X;
		if (i <= 0)
			m.setPositionBackward(0, 0);
		else
		{
			m.setPositionBackward(10, 0);
		}
		m.changeMode(Mario::RUN);
		break;
	case 'd':

		i = m.pos_X;
		if (i >= r.pos_X - 125)
			m.changePosition(r.pos_X - 125, 0);
		else
		{
			KenRunTime += 1;
			KenFinalVelocity = KenFinalVelocity + (KenAcceleration * KenRunTime);
			KenFinalPosition = KenFinalPosition + (KenFinalVelocity * KenRunTime);
			if (KenFinalPosition > 55) KenFinalPosition = 25;
			m.setPositionForward(KenFinalPosition, 0);
		}
		m.changeMode(Mario::RUN);
		break;

	case 'c':
		i = m.pos_X;
		if (i >= r.pos_X - 125)
			m.changePosition(r.pos_X - 125, 0);
		else
		{
			m.setPositionForward(10, 0);
		}

		m.changeMode(Mario::RUN);
		break;
	case 'w':

		m.changeMode(Mario::JUMP);
		m.changeCouter();
		m.increseTime();
		break;
	case 'p':
		i = r.pos_X;
		if (i <= m.pos_X + 100)
			r.setPositionBackward(0, 0);
		else
			r.setPositionForward(20, 0);
		r.changeMode(Ralph::PUNCH);
		r.changeCouter();
		m.changeMode(Mario::PUNCHED);
		m.setRalphPosition(r.getPositionX(), r.getPositionY());
		break;

	case 'f':
		i = m.pos_X;
		if (i >= r.pos_X + 100)
			m.setPositionBackward(0, 0);
		else
			m.setPositionForward(20, 0);
		m.changeMode(Mario::PUNCH);
		m.changeCouter();
		r.changeMode(Ralph::PUNCHED);
		r.setKenPosition(m.getPositionX(), m.getPositionY());
		break;

	case 'b':
		m.changeCouter();
		m.changeMode(Mario::POWER);
		m.setRalphPosition(r.getPositionX(), r.getPositionY());
		r.changeMode(Ralph::POWERED);
		r.changeCouter();
		/*r.setKenPosition(m.getPositionX(),m.getPositionY());*/
		break;
	}
}

void keyReleased(unsigned char key, int x, int y)
{
	switch (key)
	{

	case 'a':
		m.changeMode(Mario::STAY);
		KenInitalVelocity = 0;
		KenFinalVelocity = 0;
		KenRunTime = 1;
		KenInitialPostion = 0;
		KenFinalPosition = 0;
		break;

	case 'd':
		m.changeMode(Mario::STAY);
		 KenInitalVelocity = 0;
		 KenFinalVelocity = 0;
		 KenRunTime = 1;
		 KenInitialPostion = 0;
		 KenFinalPosition = 0;
		break;

	case 'w':
		m.changeMode(Mario::JUMP);
		m.changePosition(m.pos_X,0);
	//	m.resetJmpTimer();
		break;
	case 's':
		break;

	case 'p':
		
		break;
	}

	glutPostRedisplay();
}
void pressKeySpecial(int key, int x, int y)
{
	static int i = 655; int a = 655;
	switch (key)
	{
	case GLUT_KEY_LEFT:

		

		i = r.pos_X;
		if (i <= m.pos_X + 100)
			r.setPositionBackward(0, 0);
		else
		{
			RalphRunTime += 1;
			RalphFinalVelocity = RalphFinalVelocity + (RalphAcceleration * RalphRunTime);
			RalphFinalPosition = RalphFinalPosition + (RalphFinalVelocity * RalphRunTime);
			if (RalphFinalPosition > 55) RalphFinalPosition = 25;
			r.setPositionForward(RalphFinalPosition, 0);
			
		}
			
		r.changeMode(Ralph::RUN);
		break;
	case GLUT_KEY_RIGHT:
		

		i = r.pos_X;
		if (i >= 650)
			r.setPositionBackward(0, 0);
		else
		{
			RalphRunTime += 1;
			RalphFinalVelocity = RalphFinalVelocity + (RalphAcceleration * RalphRunTime);
			RalphFinalPosition = RalphFinalPosition + (RalphFinalVelocity * RalphRunTime);
			if (RalphFinalPosition > 55) RalphFinalPosition = 25;
			r.setPositionBackward(RalphFinalPosition, 0);

		}
			
		r.changeMode(Ralph::RUN);
		break;
	case GLUT_KEY_UP:
		
		r.changeMode(Ralph::JUMP);
		r.changeCouter();
		break;

	}
	glutPostRedisplay();
}






void releaseKeySpecial(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_LEFT:
		r.changeMode(Ralph::STAY);
		break;

	case GLUT_KEY_RIGHT:
		r.changeMode(Ralph::STAY);
		break;

	case GLUT_KEY_UP:
		//r.changeMode(Ralph::JUMP);
		break;
	case GLUT_KEY_DOWN:
		break;

	}

	glutPostRedisplay();
}




void myTimer(int t){

	cut++;
	if (cut > 23)
		cut = 0;

	glutTimerFunc(70, myTimer, 1);
	glutPostRedisplay();
}

RGBApixmap land;
void ralphWin()
{
	land.readBMPFile("ralphWin.bmp");
	glPushMatrix();
	glTranslatef(-150, 0, 0);
	land.mDraw();
	glPopMatrix();
	glutSwapBuffers();
}
void kenWin(){
	land.readBMPFile("ryoWin.bmp");
	glPushMatrix();
	glTranslatef(-20,0,0);
	land.mDraw();
	glPopMatrix();
	glutSwapBuffers();
}

void myDisplay()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	if (r.HealthValue == 100 )
		ralphWin(); 
	if (m.HealthValue == 100)
		ralphWin();
	else
	
	bkChange(cut);
	
	glFlush();
	//glutSwapBuffers();
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1080, 680);
	glutInitWindowPosition(100, 10);
	glutCreateWindow("Mario Game");

	glutSpecialFunc(pressKeySpecial);
	glutSpecialUpFunc(releaseKeySpecial);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyReleased);
	
	glutSwapBuffers();
	glutTimerFunc(5, myTimer, 1);
	glutDisplayFunc(myDisplay);

	/*glutKeyboardFunc(myKB_Handler);*/
	/*move();*/

	//glutIdleFunc(myDisplay);

	myInit();
	glutMainLoop();


}

