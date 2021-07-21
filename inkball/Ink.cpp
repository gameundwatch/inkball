#include "Ink.h"

Ink::Ink() {
	Dots = {};
}
void Ink::makeLine() {
	for (auto& dot : Dots) {
	Body.push_back(dot);
	}
}
void Ink::drawLine() {
	Body.draw(8, ColorF(0.1, 0.1, 0.1));
}
void Ink::Clear() {
	Dots.clear();
	Body.clear();
}

void Ink::setDot(Vec2 v) {
	Dots.push_back(v);
}