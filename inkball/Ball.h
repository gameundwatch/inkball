#pragma once

#include <Siv3D.hpp>

class Ball
{

private:
	Circle Body;
	Vec2 Pos;
	Vec2 Vel;
	double Spd;
	ColorF Clr;
	// 0 = white, 1 = Orange, 2 = Blue, 3 = Green, 4 = Yellow

public:
	Ball();
	Ball(Vec2 _p, Vec2 _v, double _s, int _c);
	void DrawBall();
	void MoveBall();

	Vec2 getPos();
	Vec2 getVel();
	double getSpd();
	ColorF getClr();

	void setPos(Vec2 _p);
	void setVel(Vec2 _v);
	void setSpd(double _s);
	void setClr(ColorF _c);

};


