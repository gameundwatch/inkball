#pragma once

#include<Siv3D.hpp>

#include"Block.h"

class Block
{
private:
	Rect Body;
	Circle Hall;
	int Type;
	Vec2 Pos;
	Vec2 Size;

public:
	Block();
	Block(int x,int y, int i);
	void drawBlock(int x,int y);

	void setHall(int y, int x);

	Rect getBody();
	int  getType();
	Vec2 getPos();
	Vec2 getSize();
	void makeBody(Vec2 _p);
};


