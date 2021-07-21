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
	Body.setSize(Size.x,Size.y);
	Body.setPos(40 * x, 40 * y);
	switch (Type)
	{
	case 0:
		Body.draw(ColorF(0.8, 0.8, 0.8)).drawFrame(1, 0, ColorF(0.5, 0.5, 0.5));
		break;
	case 1:
		Body.draw(Arg::top = ColorF(1, 1, 1),Arg::bottom = ColorF(0.8, 0.8, 0.8)).drawFrame(1, 0, ColorF(0.9, 0.9, 0.9));
		break;
	default:
		break;
	}
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
	Body.setPos(40 * _p.x,40 * _p.y);
}