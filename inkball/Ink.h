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
	void drawPoint(Vec2 v);
	void drawLine();
	bool isEmpty();
	void Clear();
	double getLength();
	Vec2 get1st();
	void setDot(Vec2 v);
	LineString getBody();
};

