#include <Siv3D.hpp>

#include "Block.h"

Block::Block()
{
	Size = Vec2(40, 40);
	Type = 0;
}

Block::Block(int x, int y, int i)
{
	Size = Vec2(40, 40);
	Pos	 = Vec2(x, y);
	Type = i;
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
		Body.draw(Arg::top = ColorF(1, 1, 1),Arg::bottom = ColorF(0.8, 0.8, 0.8)).drawFrame(1, 0, ColorF(0.2, 0.2, 0,2));
		break;
	default:
		break;
	}

}