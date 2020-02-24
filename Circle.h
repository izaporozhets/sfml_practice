#pragma once
#include <SFML/Graphics.hpp>

class Circle : public sf::Shape
{
public:
	Circle(const std::size_t pts = 30)
	{
		points = pts;
		setToDefault();
		update();
	}

	Circle(const float rds, const std::size_t pts = 30)
	{
		radius = rds;
		points = pts;
		update();
	}

	void setToDefault() override
	{
		setRadius(100.0f);
		setFillColor(sf::Color::Red);
		setPosition(500, 500);
		setOrigin(100, 100);
		update();
	}

	void setRadius(const float& rds)
	{
		radius = rds;
		update();
	}

	const float& getRadius() const
	{
		return radius;
	}

	virtual std::size_t getPointCount() const
	{
		return points;
	}

	virtual sf::Vector2f getPoint(std::size_t index) const
	{
		static const float pi = 3.141592654f;

		float angle = index * 2 * pi / getPointCount() - pi / 2;
		float x = std::cos(angle) * radius;
		float y = std::sin(angle) * radius;

		return { radius + x, radius + y };
	}

	Shape* clone() override {
		return new Circle(*this);
	}

private:
	float radius;
	std::size_t points;
};