#pragma once
#include"Mario.h"

void myTimerRalph(int t); void stayingRalph();
class Point2R
{
public:
	Point2R() { x = y = 0.0f; } // constructor 1
	Point2R(float xx, float yy) { x = xx; y = yy; } // constructor 2
	void set(float xx, float yy) { x = xx; y = yy; }
	float getX() { return x; }
	float getY() { return y; }
	
	void draw(void)
	{
		
		glPointSize(2.0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_POINT_SMOOTH);

		glBegin(GL_POINTS); // draw this point
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();

		glDisable(GL_POINT_SMOOTH);

	}// end draw
private:
	float x, y;
}; // end class Point2

RGBApixmap ralphStay[35];
RGBApixmap ralphWalk[7];
RGBApixmap ralphJump[19]; int jumpValR = 0; RGBApixmap Girnatmp[24]; int ralpPoweredCounter = 0;
RGBApixmap ralphSmallPunch[9];
Mario mChk(Point2(0, 0));
class Ralph
{
public:

	RGBApixmap pix[5];// make six empty pixmaps, one for each side of cube

	enum State	{
		STANDING, RUNNING0, RUNNING1,
		RUNNING2, RUNNING3, RUNNING4,
		RUNNING5, RUNNING6,
		RUNNING7, RUNNING8, RUNNING9,
		RUNNING10, JUMPING, DIE, PUNCHING
	}state;

	
public:	enum ModeType{ STAY, RUN, R, JUMP, DEAD, PUNCH, POWERED, PUNCHED } mode;
		float pos_X, pos_Y;
		float kenPosX = 0, kenPosY = 0; 
		int HealthValue = 0;
		Ralph(Point2R pos)
		{
		

			for (int i = 0; i < 35; i++)
			{
				std::string result2 = "ralphStanding" + std::to_string(i);
				result2 = result2 + ".bmp";
				ralphStay[i].readBMPFile(result2);
				ralphStay[i].setChromaKey(245, 245, 245);
			}

			
			for (int i = 0; i < 7; i++)
			{
				std::string result2 = "ralphWalk" + std::to_string(i);
				result2 = result2 + ".bmp";
				ralphWalk[i].readBMPFile(result2);
				ralphWalk[i].setChromaKey(245, 245, 245);
			}
			for (int i = 0; i < 19; i++)
			{
				std::string result2 = "ralphJumpStanding" + std::to_string(i);
				result2 = result2 + ".bmp";
				ralphJump[i].readBMPFile(result2);
				ralphJump[i].setChromaKey(245, 245, 245);
			}

			for (int i = 0; i < 9; i++)
			{
				std::string result2 = "ralphPunch" + std::to_string(i);
				result2 = result2 + ".bmp";
				ralphSmallPunch[i].readBMPFile(result2);
				ralphSmallPunch[i].setChromaKey(245, 245, 245);
			}

			for (int i = 0; i < 23; i++)
			{
				std::string result = "ralfGirnatmp-" + std::to_string(i);
				result = result + ".bmp";
				Girnatmp[i].readBMPFile(result);
				Girnatmp[i].setChromaKey(10, 0, 0);
			}



			this->pos_X = pos.getX();
			this->pos_Y = pos.getY();
		
		};

		void setPositionForward(float x, float y)
		{
			this->pos_X -= x;
			this->pos_Y -= y;
		
		}
		void setPositionBackward(float x, float y)
		{
			this->pos_X += x;
			this->pos_Y += y;

		}

		float getPositionY(){
			return this->pos_Y;
		}
		float getPositionX(){
			return this->pos_X;
		}

		void render();
		void changeMode(ModeType m);
		void run();
		void die();
		void display(int value);

		void changePosition(float dx, float dy)
		{
			this->pos_X = dx;
			this->pos_Y = dy;
		
		}
		//void render();
		//void changeMode(ModeType m);
		//void run();
		//void stay();
		//void jump();
		//void die();

		void changeCouter()
		{
			jumpValR = 0; valueRPunch = 0; ralpPoweredCounter = 0;
		}


		void setKenPosition(float x , float y){
			this-> kenPosX = x;
			this->kenPosY = y;
		}
		int getHealth(){
			return HealthValue;
		}

		void decHealth(){
			HealthValue += 10;
		}


		void ralphPowered(){
			ralpPoweredCounter++;
			if (ralpPoweredCounter > 23)
			{

				//ralpPoweredCounter = 0;

				glutTimerFunc(0, myTimerRalph, 1);
				stayingRalph();
				
				return void();


			}
			if (ralpPoweredCounter ==  23)decHealth();
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_EQUAL, 1.0);
			glPixelZoom(2, 2);
			Girnatmp[ralpPoweredCounter].mDraw();
			glFlush();
			glPixelZoom(1, 1);
		}


		
};


int valueR = 0;

void stayingRalph()
{
	valueR++;
	if (valueR > 34)
		valueR = 0;
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL, 1.0);
	glPixelZoom(2, 2);
	ralphStay[valueR].mDraw();
	glFlush();
	glPixelZoom(1, 1);
}

void myTimerRalph(int t){


	glutTimerFunc(100, myTimerRalph, 1);
}



Ralph r1(Point2R(0, 0));
Mario KenPunched(Point2(0, 0));
void RalphJumpDisplay1()
{
	jumpValR++;
	if (jumpValR > 18)
	{
		r1.changeMode(Ralph::STAY);
		glutTimerFunc(0, myTimerRalph, 1);
		r1.render();
		return void();
	}
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL, 1.0);
	glPixelZoom(2, 2);
	ralphJump[jumpValR].mDraw();
	glFlush();
	glPixelZoom(1, 1);
}



void RalphPunching(){
	valueRPunch++;
	if (valueRPunch > 8)
	{
		r1.changeMode(Ralph::STAY);
		glutTimerFunc(0, myTimerRalph, 1);
		stayingRalph();
		return void();
	}
	glPixelZoom(2, 2);
	ralphSmallPunch[valueRPunch].mDraw();
	glFlush();
	glPixelZoom(1, 1);
}

void ralphPuncedCont(float x, float y){
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL, 1.0);
	//	glClear(GL_COLOR_BUFFER_BIT);
	glPixelZoom(2, 2);
	glRasterPos2i(x, y);

	kenPunced[0].mDraw();
	glFlush();
	glPixelZoom(1, 1);
	//m1.changeMode(Mario::STAY);
}



void Ralph::render()
{
	switch (mode)
	{
	case(STAY) :
		glRasterPos2i(this->pos_X, this->pos_Y);
		glutTimerFunc(0, myTimerRalph, 1);
		stayingRalph();
		break;
	case(RUN) :
		glRasterPos2i(this->pos_X, this->pos_Y);
		glPixelZoom(2, 2);
		run();
		glPixelZoom(1, 1);
		break;
	case(JUMP) :
		r1.pos_X = this->pos_X;
		glRasterPos2i(r1.pos_X, this->pos_Y);
		RalphJumpDisplay1();
	//	mode = STAY;
		break;
	case(PUNCH) :
		
		glRasterPos2i(this->pos_X, this->pos_Y);
		RalphPunching();
		break;

	case(POWERED) :
		glRasterPos2i(this->pos_X, this->pos_Y);
		
		ralphPowered();
		
		//mode = STAY;
		break;


	case(PUNCHED) :

		if (this->kenPosX >= this->pos_X + 110)
		{
			if (this->pos_X <40){
				//glRasterPos2i(this->pos_X, this->pos_Y);
				ralphPuncedCont(this->pos_X, this->pos_Y); mode = STAY;
				decHealth();
			}
			else
			{
				this->pos_X -= 20;
				//	glRasterPos2i(this->pos_X, this->pos_Y);
				ralphPuncedCont(this->pos_X, this->pos_Y);
				decHealth();
			}			//mode = STAY;
		}
		else
		{
			glRasterPos2i(this->pos_X, this->pos_Y);
			stayingRalph();
			mode = STAY;
		}
		break;
	}
}

void Ralph::run()
{
	switch (state)
	{

	case RUNNING0:
		glRasterPos2i(this->pos_X, this->pos_Y);
			ralphWalk[0].mDraw();

		state = RUNNING1;
		break;
	case RUNNING1:
		glRasterPos2i(this->pos_X, this->pos_Y);
		ralphWalk[1].mDraw();

		state = RUNNING2;
		break;

	case RUNNING2:
		glRasterPos2i(this->pos_X, this->pos_Y);
		ralphWalk[2].mDraw();

		state = RUNNING3;
		break;
	case RUNNING3:
		glRasterPos2i(this->pos_X, this->pos_Y);
		ralphWalk[3].mDraw();

		state = RUNNING4;
		break;
	case RUNNING4:
		glRasterPos2i(this->pos_X, this->pos_Y);
		ralphWalk[4].mDraw();

		state = RUNNING5;
		break;
	case RUNNING5:
		glRasterPos2i(this->pos_X, this->pos_Y);
		ralphWalk[5].mDraw();
		state = RUNNING6;
		break;
	case RUNNING6:
		glRasterPos2i(this->pos_X, this->pos_Y);
		ralphWalk[6].mDraw();
		state = RUNNING0;
		break;
	
	}


}




void Ralph::changeMode(ModeType m)
{
	if (mode == m)
		return;
	switch (m)
	{
	case STAY:
		state = STANDING;
		break;
	case RUN:
		state = RUNNING1;
		break;
	case JUMP:
		state = JUMPING;
		break;
	case PUNCH:
		state = PUNCHING;
		break;
	}
	mode = m;
}