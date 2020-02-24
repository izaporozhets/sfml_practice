#pragma once
#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
const int SPEED = 1;


void moving(sf::Shape* current_shape) {
	if (current_shape) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			current_shape->move(-SPEED, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			current_shape->move(SPEED, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			current_shape->move(0, -SPEED);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			current_shape->move(0, SPEED);
		}
	}
}
