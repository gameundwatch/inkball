#include "Ink.h"

Ink::Ink() {
	Dots = {};
}
void Ink::makeLine() {
	for (auto& dot : Dots) {
	Body.push_back(dot);
	}
}

bool Ink::isEmpty() {
	return Dots.isEmpty();
}

void Ink::drawPoint(Vec2 v) {
	Circle(v, 4).draw(ColorF(0.2, 0.2, 0.2, 0.5 + Periodic::Sine0_1(1s) * 0.5));
}

void Ink::drawLine() {
	Body.draw(LineStyle::RoundCap, 4, ColorF(0.2, 0.2, 0.2));
}

void Ink::Clear() {
	Dots.clear();
	Body.clear();
}

double Ink::getLength() {
	if (Dots.size() != 2) {
		return 0;
	}
	else {
		return (Dots.at(0) - Dots.at(1)).length();
	}
}

Vec2 Ink::get1st() {
	return Dots.at(0);
}

void Ink::setDot(Vec2 v) {
	Dots.push_back(v);
}

LineString Ink::getBody() {
	return Body;
}
