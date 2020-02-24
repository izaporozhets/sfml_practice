#pragma once
#include <SFML/Graphics.hpp>

class Ellipse : public sf::Shape
{
public:
	Ellipse()
	{
		setToDefault();
		update();
	}

	Ellipse(const sf::Vector2f& rds)
	{
		radius = rds;
		update();
	}

	void setToDefault() override
	{
		setRadius(sf::Vector2f(250.0f, 50.0f));
		setFillColor(sf::Color::Yellow);
		setPosition(200, 1000);
		setOrigin(250, 50);
		update();
	}

	void setRadius(const sf::Vector2f& rds)
	{
		radius = rds;
		update();
	}

	const sf::Vector2f& getRadius() const
	{
		return radius;
	}

	virtual std::size_t getPointCount() const
	{
		return 30;
	}

	virtual sf::Vector2f getPoint(std::size_t index) const
	{
		static const float pi = 3.141592654f;

		float angle = index * 2 * pi / getPointCount() - pi / 2;
		float x = std::cos(angle) * radius.x;
		float y = std::sin(angle) * radius.y;

		return { radius.x + x, radius.y + y };
	}

	Shape* clone() override {
		return new Ellipse(*this);
	}

private:
	sf::Vector2f radius;
};