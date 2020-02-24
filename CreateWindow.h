#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

class CreateWindow
{

public:
	static CreateWindow* getInstance(sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());
	sf::RenderWindow* getWindow();
private:
	CreateWindow(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings);
	sf::RenderWindow* window;
	static CreateWindow* instance;
};

