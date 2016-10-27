#pragma once


void myTimerKen(int t); void staying(float x); int value = 0; float gravity = 10; int valueRPunch = 0;
class Point2
{
public:
	Point2() { x = y = 0.0f; } // constructor 1
	Point2(float xx, float yy) { x = xx; y = yy; } // constructor 2
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
GLuint texture;
RGBApixmap kenStay[10];
RGBApixmap kenWalk[12];
RGBApixmap kenJump[21]; int jumpVal = 0; int Jmp2Counter = 0; int valuPow = 0; int poweringCounter = 0;
RGBApixmap kenPunced[1];
RGBApixmap powerKen; RGBApixmap powerKenShow[14]; RGBApixmap kenSmallPunch;
class Mario
{
public:

	RGBApixmap pix[5];// make six empty pixmaps, one for each side of cube

	enum State	{ STANDING, RUNNING0, RUNNING1,
					RUNNING2, RUNNING3, RUNNING4,
					RUNNING5, RUNNING6,
					RUNNING7, RUNNING8, RUNNING9,
					RUNNING10, JUMPING, DIE
	}state;
public:	enum ModeType{ STAY, RUN, R, JUMP, DEAD, PUNCHED, POWER, PUNCH } mode;
	float pos_X, pos_Y;
	float ralphPosX = 0, ralphPosY = 0; float timeJump = 0; bool firstJump = false; float HealthValue = 0;
	Mario(Point2 pos)

	{
		
		for (int i = 0; i < 12; i++)
		{
			std::string result2 = "kenWalk" + std::to_string(i);
			result2 = result2 + ".bmp";
			kenWalk[i].readBMPFile(result2);
			kenWalk[i].setChromaKey(0, 0, 0);
		}

		pix[0].readBMPFile("MarioStanding.bmp");
		pix[1].readBMPFile("MarioRun1.bmp");
		pix[2].readBMPFile("MarioRun2.bmp");
		pix[3].readBMPFile("MarioRun3.bmp");
		pix[4].readBMPFile("MarioJump.bmp");

		for (int i = 0; i<5; i++)
		{
			pix[i].setChromaKey(192, 192, 192);
		}
		
		for (int i = 0; i < 10; i++)
		{
			std::string result = "ken" + std::to_string(i);
			result = result + ".bmp";
			kenStay[i].readBMPFile(result);
			kenStay[i].setChromaKey(255, 0, 255);
		}

		for (int i = 0; i < 21; i++)
		{
			std::string result = "kenJump" + std::to_string(i);
			result = result + ".bmp";
			kenJump[i].readBMPFile(result);
			kenJump[i].setChromaKey(0, 0, 0);
		}
		
		for (int i = 0; i < 2; i++)
		{
			std::string result = "kenPunched" + std::to_string(i);
			result = result + ".bmp";
			kenPunced[i].readBMPFile(result);
			kenPunced[i].setChromaKey(0, 0, 0);
		}
		powerKen.readBMPFile("powerKen.bmp");
		powerKen.setChromaKey(245, 245, 245);
		for (int i = 0; i < 14; i++)
		{
			std::string result = "hadu" + std::to_string(i);
			result = result + ".bmp";
			powerKenShow[i].readBMPFile(result);
			powerKenShow[i].setChromaKey(245, 245, 245);
		}

		

		this->pos_X = pos.getX();
		this->pos_Y = pos.getY();
		

	};


	void setRalphPosition(float x, float y){
		this->ralphPosX = x;
		this->ralphPosY = y;
	}

	void setPositionForward(float x, float y)
	{
		this->pos_X += x;
		this->pos_Y += y;

	}
	void setPositionBackward(float x, float y)
	{
		this->pos_X -= x;
		this->pos_Y -= y;

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

	float getPositionY(){
		return this->pos_Y;
	}
	float getPositionX(){
		return this->pos_X;
	}
	//void render();
	//void changeMode(ModeType m);
	//void run();
	//void stay();
	//void jump();
	//void die();
	void changeCouter()
	{
		
		jumpVal = 0; valuPow = 0; poweringCounter = 0;
	}


	void resetJmpTimer(){
		timeJump = 1; 
	
	}

	void increseTime(){
		timeJump += 1;
		
	}
	float getJmpTime(){
		return timeJump;	
	}
	bool firstJmpChk(){
		return firstJump;
	}



	bool jumpKen = false;
	int JumpY = 0; 
	void KenJumpDisplay1(float x, float y, float jmpT, bool firstJmpChk)
	{
		jumpVal++;
		if (jumpVal > 20)
		{

			//	jumpVal = 0;
		
			glutTimerFunc(0, myTimerKen, 1);
			glRasterPos2i(x, 0);
			staying(x);
			this->pos_Y = 0;
			//		glutSwapBuffers();
			if (Jmp2Counter > JumpY)
				JumpY = 0;

			timeJump = 0;
			return void();
		}

		else if (jumpVal > 10)
		{
			this->pos_Y = 0;
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_EQUAL, 1.0);
			//	glClear(GL_COLOR_BUFFER_BIT);
			glPixelZoom(2, 2);
			y -= gravity*timeJump;
			JumpY = y;
			glRasterPos2i(x, y);
			kenJump[jumpVal].mDraw();
			glFlush();
			glPixelZoom(1, 1);
			this->pos_Y = 0;

		}
		else
		{

			
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_EQUAL, 1.0);
			//	glClear(GL_COLOR_BUFFER_BIT);
			glPixelZoom(2, 2);
			y += gravity*timeJump;
			Jmp2Counter += y;
			JumpY = y;
			glRasterPos2i(x, y);
			kenJump[jumpVal].mDraw();
			glFlush();
			glPixelZoom(1, 1);
			this->pos_Y = 0;
		}
		//glutSwapBuffers();
	}

	GLuint LoadTexture(const char * filename)
	{

		

		int width, height;

		unsigned char * data;

		FILE * file;

		file = fopen(filename, "rb");

		if (file == NULL) return 0;
		width = 1024;
		height = 512;
		data = (unsigned char *)malloc(width * height * 3);
		//int size = fseek(file,);
		fread(data, width * height * 3, 1, file);
		fclose(file);

		for (int i = 0; i < width * height; ++i)
		{
			int index = i * 3;
			unsigned char B, R;
			B = data[index];
			R = data[index + 2];

			data[index] = R;
			data[index + 2] = B;

		}


		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);


		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
		free(data);

		return texture;
	}
	GLuint texture = LoadTexture("powerKen.bmp");;
	
	int getHealth(){
		return HealthValue;
	}

	void decHealth(){
		HealthValue += 10;
	}

};




void staying(float x)
{
	value++;
	if (value > 9)
		value = 0;


	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL, 1.0);
//	glClear(GL_COLOR_BUFFER_BIT);
	
	glRasterPos2i(x, 0);
	glPixelZoom(2, 2);
	kenStay[value].mDraw();
	glFlush();
	glPixelZoom(1, 1);
//glutSwapBuffers();
	//
}

void myTimerKen(int t){

	
	glutTimerFunc(0, myTimerKen, 1);
	
}
Mario m1(Point2(0, 0)); 

void kenPuncedCont(float x,float y){
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

void powerCounter(){
	poweringCounter = 0;
}
void powering(float x, float ralphX){
	
	
	for (; poweringCounter<ralphX-180; poweringCounter++)
	{
		glutSwapBuffers();
		glPushMatrix();
		glTranslatef(ralphX, -100, 0);
		/*glBegin(GL_TRIANGLES);

		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(245.0, 200.0);
		glVertex2f(245.0, 210.0);
		glVertex2f(215.0, 200.0);

		glColor3f(0.2, 0.2, 0.2);
		glVertex2f(244.0, 198.0);
		glVertex2f(244.0, 205.0);
		glVertex2f(228.0, 205.0);

		glEnd();*/
		glPushMatrix();
		int y = 0;
		//glTranslatef(x, y, 0.0);
		glTranslatef(100+x, 0, 0);
		glLineWidth(5);
		glBegin(GL_LINES);

		glColor3f(0.4, 0.5, 1.0);
		int k = 0;
		int l = 0;
		int m = 0;
		int n = 0;
		int o = 0;
		for (int i = 0; i<2; i++)
		{
			glVertex2f(35.0, 240.0 - k);
			glVertex2f(55.0, 230.0 - k);


			glVertex2f(55.0, 230.0 - k);
			glVertex2f(50.0, 237.0 - k);

			glVertex2f(50.0, 237.0 - k);
			glVertex2f(68.0 - k, 220.0);

			glVertex2f(68.0 - k, 220.0);
			glVertex2f(50.0, 203.0 + k);

			glVertex2f(50.0, 203.0 + k);
			glVertex2f(55.0, 210.0 + k);

			glVertex2f(55.0, 210.0 + k);
			glVertex2f(35.0, 200.0 + k);
			k += 6;
		}
		glEnd();
		glLineWidth(4);
		glBegin(GL_LINES);

		glColor3f(0.4, 0.5, 1.0);
		for (int i = 0; i<2; i++)
		{
			glVertex2f(35.0, 235.0 - k);
			glVertex2f(55.0, 235 - k);
			k += 6;
		}

		glColor3f(0.4, 0.5, 1.0);
		for (int i = 0; i<2; i++)
		{
			glVertex2f(35.0, 235.0 - k);
			glVertex2f(55.0, 235 - k);
			k += 6;
		}
		glEnd();
	//	glPopMatrix();
	}
	glPopMatrix();
	glutSwapBuffers();

}

void powerKenShowing(float x,float ralphX){
	valuPow++;
	if (valuPow > 12)
	{
		glutTimerFunc(0, myTimerKen, 1);
		glRasterPos2i(x, 0);

		powering(x, ralphX);
		staying(x);
		
		
		//		glutSwapBuffers();
		
		return void();
	}

	if (valuPow > 3)
	{
		glPushMatrix();
		glRasterPos2i(x + 165, 75);
		
		powerKen.mDraw();
		glFlush();
		glPopMatrix();
	}
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL, 1.0);
	//	glClear(GL_COLOR_BUFFER_BIT);
	
	glPixelZoom(1, 1);
	glRasterPos2i(x, 0);
	glPixelZoom(2, 2);
	powerKenShow[valuPow].mDraw();
	glFlush();
	glPixelZoom(1, 1);
}


void KenPunching(int xPos){
	valueRPunch++;
	if (valueRPunch > 8)
	{
		m1.changeMode(Mario::STAY);
		glutTimerFunc(0, myTimerKen, 1);
		staying(xPos);
		return void();
	}
	glPixelZoom(2, 2);
//	kenSmallPunch[valueRPunch].mDraw();
	glFlush();
	glPixelZoom(1, 1);
}



void Mario::render()
{
	switch (mode)
	{
	case(STAY) :
		glRasterPos2i(this->pos_X, 0);
		glutTimerFunc(0, myTimerKen, 1);
		staying(this->pos_X);

		this->pos_Y = 0;
		break;
		
	case(RUN) :
		glRasterPos2i(this->pos_X, this->pos_Y);
		glPixelZoom(2, 2);
		run();
//		glutSwapBuffers();
		glPixelZoom(1, 1);
		
		break;
	case(JUMP) :

		//glutTimerFunc(0, myTimerKen, 1);
		this->pos_Y = JumpY;
		KenJumpDisplay1(this->pos_X, this->pos_Y,getJmpTime(),this->firstJump);
		break;
	case(PUNCHED) :
	
		if (this->ralphPosX <= this->pos_X + 110 )
		{
			if (this->pos_X <40){
				//glRasterPos2i(this->pos_X, this->pos_Y);
				kenPuncedCont(this->pos_X, this->pos_Y); mode = STAY;
				decHealth();
			}
			else
			{
				this->pos_X -= 20;
			//	glRasterPos2i(this->pos_X, this->pos_Y);
				kenPuncedCont(this->pos_X, this->pos_Y);
				decHealth();
			}			//mode = STAY;
		}
		else
		{
			glRasterPos2i(this->pos_X, this->pos_Y);
			staying(this->pos_X);
			mode = STAY;
		}
		break;

	case(POWER) :
		
		powerKenShowing(this->pos_X,this->ralphPosX);
		//staying(this->pos_X);

		break;
	case(PUNCH) :

		glRasterPos2i(this->pos_X, this->pos_Y);
		KenPunching(this->pos_X);
		break;


	}
	
}

void Mario::run()
{
	switch (state)
	{

	case RUNNING0:
		glRasterPos2i(this->pos_X, this->pos_Y);
		kenWalk[0].mDraw();

		state = RUNNING1;
		break;
	case RUNNING1:
		glRasterPos2i(this->pos_X, this->pos_Y);
		kenWalk[1].mDraw();
		
		state = RUNNING2;
		break;

	case RUNNING2:
		glRasterPos2i(this->pos_X, this->pos_Y);
		kenWalk[2].mDraw();
		
		state = RUNNING3;
		break;
	case RUNNING3:
		glRasterPos2i(this->pos_X, this->pos_Y);
		kenWalk[3].mDraw();
	
		state = RUNNING4;
		break;
	case RUNNING4:
		glRasterPos2i(this->pos_X, this->pos_Y);
		kenWalk[4].mDraw();
		
		state = RUNNING5;
		break;
	case RUNNING5:
		glRasterPos2i(this->pos_X, this->pos_Y);
		kenWalk[5].mDraw();
		state = RUNNING6;
		break;
	case RUNNING6:
		glRasterPos2i(this->pos_X, this->pos_Y);
		kenWalk[6].mDraw();
		state = RUNNING7;
		break;
	case RUNNING7:
		glRasterPos2i(this->pos_X, this->pos_Y);
		kenWalk[7].mDraw();
		state = RUNNING8;
		break;
	case RUNNING8:
		glRasterPos2i(this->pos_X, this->pos_Y);
		kenWalk[8].mDraw();
		state = RUNNING9;
		break;
	case RUNNING9:
		glRasterPos2i(this->pos_X, this->pos_Y);
		kenWalk[9].mDraw();
		state = RUNNING10;
		break;
	case RUNNING10:
		glRasterPos2i(this->pos_X, this->pos_Y);
		kenWalk[10].mDraw();
		state = RUNNING1;
		break;
	}
}




void Mario::changeMode(ModeType m)
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
	}
	mode = m;
}