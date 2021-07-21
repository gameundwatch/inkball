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
	Body.draw().drawFrame(1,0,ColorF(0.8,0.8,0.8));
}