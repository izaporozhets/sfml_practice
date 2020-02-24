#pragma once
#include "Composite.h"
class Memento
{
	friend class Composite;
	std::vector<sf::Shape*> shots;
};

