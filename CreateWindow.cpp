#include "pch.h"
#include "CreateWindow.h"

CreateWindow* CreateWindow::instance = nullptr;

CreateWindow::CreateWindow(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings)
{
	window = new sf::RenderWindow(mode,title,style,settings);
}

CreateWindow* CreateWindow::getInstance(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings)
{
	if (instance == nullptr) {
		instance = new CreateWindow( mode, title, style,settings);
	}
	return instance;
}

sf::RenderWindow * CreateWindow::getWindow()
{
	return window;
}
