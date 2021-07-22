#include <Siv3D.hpp>

#include "Block.h"

Block::Block()
{
	Type = 0;
	Pos = Vec2(0, 0);
	Size = Vec2(40, 40);
}

Block::Block(int x, int y, int i)
{
	Type = i;
	Pos = Vec2(x, y);
	Size = Vec2(40, 40);
}

void Block::drawBlock(int x,int y) {

	if (Type >= 10) {
		Body.setSize(Size.x, Size.y);
		Body.setPos(40 * y, 40 * x);
		switch (Type)
		{
		case 12:
			// hall
			Body.draw(ColorF(0.8, 0.4, 0.0)).drawFrame(1, 0, ColorF(0.8, 0.4, 0.0));
			Hall.set(Vec2(20 + 40 * y, 20 + 40 * x), 12.5);
			Hall.draw(ColorF(0.1, 0.1, 0.1));
			break;
		default:
			break;
		}
	} else {
		Body.setSize(Size.x, Size.y);
		Body.setPos(40 * y, 40 * x);
		
		switch (Type)
		{
		case 0:
			Body.draw(ColorF(0.8, 0.8, 0.8)).drawFrame(1, 0, ColorF(0.5, 0.5, 0.5));
			break;
		case 1:
			// normal wall
			Body.draw(Arg::top = ColorF(1, 1, 1), Arg::bottom = ColorF(0.8, 0.8, 0.8)).drawFrame(1, 0, ColorF(0.9, 0.9, 0.9));
			break;
		case 2:
			// color wall
			break;
		default:
			break;
		}
	}
	
}

void Block::setHall(int y,int x) {
	Hall.set(Vec2(20 + 40 * y, 20 + 40 * x), 12.5);
}

Rect Block::getBody()
{
	return Body;
}

int Block::getType()
{
	return Type;
}

Vec2 Block::getPos()
{
	return Pos;
}

Vec2 Block::getSize()
{
	return Size;
}

void Block::makeBody(Vec2 _p)
{
	Body.setSize(Size.x, Size.y);
	Body.setPos(40 * _p.y,40 * _p.x);
}