#pragma once

#include<Siv3D.hpp>

class Block
{
private:
	Rect Body;
	int Type;
	Vec2 Pos;
	Vec2 Size;

public:
	Block();
	Block(int x,int y, int i);
	void drawBlock(int x,int y);
};

