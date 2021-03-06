#pragma once

#include <Siv3D.hpp>

#include "Block.h"
#include "Ink.h"

class Ball
{

private:
	Circle Body;	// ball body
	Vec2 Pos;		// position
	Vec2 Vel;		// velocity (2D unit vector)
	int Rad;		// radius
	double Spd;		// speed
	ColorF Clr;		// color

public:
	Ball();
	Ball(Vec2 _p, Vec2 _v, double _s, int _c);
	void drawBall();
	void moveBall();
	void collisionBall(Ball b);
	void collisionBlock(Block blk);
	void attractHall(int y, int x);
	bool collisionHall(int y, int x);
	bool collisionLine(Ink i);

	int addScore(Block blk);

	Vec2 getPos();
	Vec2 getVel();
	double getSpd();
	ColorF getClr();

	void setPos(Vec2 _p);
	void setVel(Vec2 _v);
	void setSpd(double _s);
	void setClr(ColorF _c);

};


