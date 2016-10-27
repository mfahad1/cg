#include "Point.h"
#include <glut.h>

class TurtleState  // or class Pen
{
public:
	TurtleState()
	{
		this->CP.set(0, 0);
		this->CD = 0;
		this->stepWidth = 0;

	}

	TurtleState(Point2 CP, float CD, float w)
	{
		this->CP.set(CP.getX(), CP.getY());
		this->CD = CD;
		this->stepWidth = w;
	}


	//private:
	float CD;
	Point2 CP;
	float stepWidth;
};

/**********************Class Turtle ********************************/

class Turtle
{
public:
	Turtle()
	{
		this->currentState = TurtleState();
		this->stepLength = 1;
		this->turnAngle = 0;

	}
	Turtle(Point2 a, float angle)
	{
		this->currentState.CP.set(a.getX(), a.getY());
		this->turnAngle = angle;

	}


	Turtle(TurtleState state, float stepLength, float cd)
	{
		Point2 a(state.CP.getX(), state.CP.getY());
		this->currentState.CD = cd;
		this->currentState = TurtleState(a, state.CD, state.stepWidth);
		this->stepLength = stepLength;

	}

	void moveTo(float x, float y);
	void moveTo(Point2 p);
	void lineTo(float x, float y);
	void lineTo(Point2 p);

	void forward(bool isVisible);
	void forward(float length, bool isVisible);
	void turnLeft(float turnAngle);
	void turnRight(float turnAngle);

	void setCurrentState(Point2 CP, float CD, float stepwidth);
	TurtleState getCurrentState(void);

	void setStepLength(float dist){ stepLength = dist; }
	float getStepLength(){ return stepLength; }

	//void setStepWidth(float width){stepWidth = width;} 
	//float getStepWidth(){return stepWidth;}

	void setTurnAngle(float angle){ this->turnAngle = angle; }




private:
	TurtleState currentState;
	float stepLength;
	float turnAngle;
};

//----------------------  turtle graphics  moveTo()-----------------------
//----------------------------------------------------------------

void Turtle::moveTo(float x, float y)
{
	this->currentState.CP.set(x, y);
}// end moveTo

void Turtle::moveTo(Point2 p)
{
	this->currentState.CP.set(p.getX(), p.getY());
}// end moveTo


//----------------------  turtle graphics  lineTo()-----------------------

void Turtle::lineTo(float x, float y)
{
	glLineWidth(this->currentState.stepWidth);
	glBegin(GL_LINES);
	glVertex2f(this->currentState.CP.getX(), this->currentState.CP.getY());
	glVertex2f(x, y);
	glEnd();

	this->currentState.CP.set(x, y);
}// end lineTo

void Turtle::lineTo(Point2 p)

{
	glLineWidth(this->currentState.stepWidth);
	glBegin(GL_LINES);
	glVertex2f(this->currentState.CP.getX(), this->currentState.CP.getY());
	glVertex2f(p.getX(), p.getY());
	glEnd();

	this->currentState.CP.set(p.getX(), p.getY());
}// end lineTo


//----------------------  turtle graphics  turn functions-----------------------


void Turtle::turnRight(float Angle)	// turn clockwise through angle
{
	this->currentState.CD -= Angle;
}

void Turtle::turnLeft(float Angle)	// turn Anticlockwise through angle
{
	this->currentState.CD += Angle;
}


//----------------------  turtle graphics  forward function-----------------------

void Turtle::forward(bool isVisible)  //forward motion
{
	float pi = 3.14159;
	float radiansPerDegree = (2.0 * pi) / 360.0;
	float x;
	float y;
	x = this->currentState.CP.getX() + stepLength * cos(radiansPerDegree * this->currentState.CD);
	y = this->currentState.CP.getY() + stepLength * sin(radiansPerDegree *this->currentState.CD);
	if (isVisible)
	{
		lineTo(x, y);
	}
	else
		moveTo(x, y);
}

void Turtle::forward(float lenght, bool isVisible)  //forward motion
{
	float pi = 3.14159;
	float radiansPerDegree = (2.0 * pi) / 360.0;
	float x;
	float y;
	x = this->currentState.CP.getX() + lenght * cos(radiansPerDegree * this->currentState.CD);
	y = this->currentState.CP.getY() + lenght * sin(radiansPerDegree *this->currentState.CD);
	if (isVisible)
	{
		lineTo(x, y);
	}
	else
		moveTo(x, y);
}

void Turtle::setCurrentState(Point2 p, float angle, float w)
{
	moveTo(p);
	this->currentState.CD = angle;
	this->currentState.stepWidth = w;
}

TurtleState Turtle::getCurrentState()
{
	TurtleState *state =
		new TurtleState(this->currentState.CP, this->currentState.CD,
		this->currentState.stepWidth);

	return *state;

}

//----------------------  End turtle graphics-----------------------