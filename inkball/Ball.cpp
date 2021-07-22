#include <Siv3D.hpp>

#include "Ball.h"
#include "Block.h"
#include "Ink.h"

Ball::Ball()
{
	Body = Circle();
	Pos = Cursor::Pos();
	Vel = Vec2(Random(-1.0, 1.0), Random(-1.0, 1.0));
	Rad = 10;
	Spd = 1.0;
	switch (Random(0,4))	// 0 = white, 1 = Orange, 2 = Blue, 3 = Green, 4 = Yellow
	{
	case 0:
		Clr = ColorF(0.8, 0.8, 0.8);
		break;
	case 1:
		Clr = ColorF(0.8, 0.4, 0.0);
		break;
	case 2:
		Clr = ColorF(0.4, 0.4, 0.6);
		break;
	case 3:
		Clr = ColorF(0.2, 0.6, 0.2);
		break;
	case 4:
		Clr = ColorF(0.6, 0.6, 0.2);
		break;

	default:
		Clr = ColorF(0.0, 0.0, 0.0);
		break;
	}
}

Ball::Ball(Vec2 _p, Vec2 _v, double _s, int _c)
{
	Body = Circle();
	Pos = _p;
	Vel = _v;
	Rad = 10;
	Spd = _s;

	switch (_c)	// 0 = white, 1 = Orange, 2 = Blue, 3 = Green, 4 = Yellow
	{
	case 0:
		Clr = ColorF(0.8, 0.8, 0.8);
		break;
	case 1:
		Clr = ColorF(0.8, 0.4, 0.0);
		break;
	case 2:
		Clr = ColorF(0.4, 0.4, 0.6);
		break;
	case 3:
		Clr = ColorF(0.2, 0.6, 0.2);
		break;
	case 4:
		Clr = ColorF(0.6, 0.6, 0.2);
		break;

	default:
		Clr = ColorF(0.0, 0.0, 0.0);
		break;
	}
}

void Ball::drawBall()
{
	Body.set(Pos, Rad);
	Body.draw(Clr).drawFrame(2, 0, ColorF(0.5, 0.5, 0.5));
}

void Ball::moveBall()
{
	Vel = Vel.normalized();
	Pos += Vel * Spd;
}

void Ball::collisionBall(Ball _b)
{
	if ( Vec2(Pos - _b.getPos()).length() < 20 )
	{
		Vel = ( Vel + ( Pos - _b.getPos() ) ).normalized();
	}
}

void Ball::collisionBlock(Block blk)
{
	Body.set(Pos, Rad);
	blk.makeBody(blk.getPos());

	if (blk.getType() == 1) {

		/*
		if (Pos.intersects(blk.getBody()))
		{
			(Pos.intersects(blk.getBody().top()) || Pos.intersects(blk.getBody().bottom()) ? Vel.y : Vel.x) *= -1.0;
		}
		*/

		if (const auto intersectsPoints = Body.intersectsAt(blk.getBody()))
		{
			Vec2 reflect(0.0, 0.0);
			for (const auto & iPoint : intersectsPoints.value())
			{
				reflect += (Pos - iPoint).normalized();
			}

			Vel += reflect;
		}

	}
}

bool Ball::collisionHall(int y, int x) {
	// Print << (Pos - Vec2(20 + 40 * x, 20 + 40 * y)).length();
	if (((Pos - Vec2(20 + 40 * x, 20 + 40 * y)).length()) < 40.0) {
		return true;
	}
	return false;
}

bool Ball::collisionLine(Ink i) {
	Body.set(Pos, Rad);
	if (const auto intersectsPoints = Body.intersectsAt(i.getBody()))
	{
		Vec2 reflect(0.0, 0.0);
		for (const auto& iPoint : intersectsPoints.value())
		{
			reflect += (Pos - iPoint).normalized();
		}
		Vel += reflect;
		return true;
	}
	return false;
}

Vec2 Ball::getPos()
{
	return Pos;
}

Vec2 Ball::getVel()
{
	return Vel;
}

double Ball::getSpd()
{
	return Spd;
}

ColorF Ball::getClr()
{
	return Clr;
}

void Ball::setPos(Vec2 _p)
{
	this->Pos = _p;
}

void Ball::setVel(Vec2 _v)
{
	this->Vel = _v;
}

void Ball::setSpd(double _s)
{
	this->Spd = _s;
}

void Ball::setClr(ColorF _c)
{
	this->Clr = _c;
}