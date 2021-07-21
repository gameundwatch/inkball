#pragma once

#include<Siv3D.hpp>

class Ink
{
private:
	Array<Vec2> Dots;
	LineString Body;

public:
	Ink();
	void makeLine();
	void drawLine();
	void Clear();
	void setDot(Vec2 v);
};

