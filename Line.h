#pragma once
#include "Rectangle.h"

class Line : public Rectangle
{
public:
	Line()
	{
		setToDefault();
		update();
	}

	void setToDefault() override
	{
		setSize(sf::Vector2f(300.0f, 50.0f));
		setScale(1.0f, 1.0f);
		setFillColor(sf::Color::Green);
		setPosition(400, 300);
		setOrigin(300 / 2, 50 / 2);
		update();
	}

	Shape* clone() override {
		return new Line(*this);
	}
};