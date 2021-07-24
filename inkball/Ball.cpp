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
	Body.drawShadow(Vec2(4, 4), 8, 1).draw(Clr).drawFrame(1, 0, ColorF(0.5, 0.5, 0.5));
}

//ボールの動作
void Ball::moveBall()
{
	Vel = Vel.normalized();
	Pos += Vel * Spd;
}

// ボール同士の衝突
void Ball::collisionBall(Ball _b)
{
	if ( Vec2(Pos - _b.getPos()).length() < 20 )
	{
		Vel = ( Vel + ( Pos - _b.getPos() ) ).normalized();
	}
}

// ボールとブロックとの衝突
void Ball::collisionBlock(Block blk)
{
	Body.set(Pos, Rad);
	blk.makeBody(blk.getPos());

	if (blk.getType() == 1) {

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

// ボールが穴に入る
bool Ball::collisionHall(int y, int x) {
	// Print << (Pos - Vec2(20 + 40 * x, 20 + 40 * y)).length();
	if (((Pos - Vec2(20 + 40 * x, 20 + 40 * y)).length()) < 10.0) {
		return true;
	}
	return false;
}

// ボールが穴に引き寄せられる
void Ball::attractHall(int y, int x) {
	if (((Pos - Vec2(20 + 40 * x, 20 + 40 * y)).length()) < 40.0) {
		Vel += (Vec2(20 + 40 * x, 20 + 40 * y) - Pos).normalized() * 0.02;
	}
}

// ボールと線の衝突

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

// スコア加点
int Ball::addScore(Block blk) {
	if (Clr == ColorF(0.8, 0.4, 0.0) && blk.getType() == 12) {
		// Red
		return 100;
	} 
	else if (Clr == ColorF(0.4, 0.4, 0.6) && blk.getType() == 13)	{
		// Blue
		return 200;
	} 
	else if (Clr == ColorF(0.2, 0.6, 0.2) && blk.getType() == 14) {
		// Green
		return 400;
	} 
	else if (Clr == ColorF(0.6, 0.6, 0.2) && blk.getType() == 15) {
		// Yellow
		return 1000;
	} 
	else if (Clr == ColorF(0.8, 0.8, 0.8) || blk.getType() == 11) {
		// White
		return 0;
	}
	else {
		return -1;
	}
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