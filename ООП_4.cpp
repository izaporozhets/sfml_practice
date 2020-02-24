// ООП_4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>

#include "Functions.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Composite.h"
#include <SFML/Window/Event.hpp>
#include "Line.h"
#include "CreateWindow.h"
#include "MementoServ.h"

void select_shape(std::vector<sf::Shape*>& v_shapes, sf::RenderWindow& window, sf::Shape*& current_composite, sf::Shape*& current_shape);
int main()
{
	//Single scene
	CreateWindow* window = CreateWindow::getInstance(sf::VideoMode(1920, 1080), "Kursa4!", sf::Style::Close | sf::Style::Titlebar);

	//Shapes 
	Circle circle;
	Ellipse ellipse;
	Rectangle rectangle;
	Line line;
	
	//Memento pattern
	MementoServ memento;

	//Shapes vector
	std::vector<sf::Shape* > v_shapes; 
	//Vector of containers needed to be deleted
	std::vector<sf::Shape* > to_delete;

	//Composite pattern
	Composite container;

	sf::Shape* current_shape = nullptr;
	sf::Shape* current_composite = nullptr;

	v_shapes.clear();

	bool is_tail = false;

	while (window->getWindow()->isOpen())
	{
		sf::Event event;
		while (window->getWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->getWindow()->close();

			//Selecting shape
			else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				select_shape(v_shapes,*window->getWindow(),current_composite,current_shape);
			}
			//Adding current shape to container
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G)
			{
				if (current_composite != nullptr) {
					for (auto& shape : *dynamic_cast<Composite*>(current_composite)->get_shapes()) {
						container.add_shape(shape);
					}
					to_delete.push_back(current_composite);
					current_composite = nullptr;
				}
				else if(current_shape) {
					container.add_shape(current_shape);
					current_shape = nullptr;
				}
			}

			// Add container to the shapes vector
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F)
			{
				if (!container.get_shapes()->empty()) {
					//Adding container to v_shapes
					v_shapes.push_back(container.clone());

					// Remove shapes(that in container) from v_shapes
					for (auto& shape : *container.get_shapes())
					{
						v_shapes.erase(std::remove(v_shapes.begin(), v_shapes.end(), shape), v_shapes.end());
					}
					//Remove containers(that in container) from v_shapes
					for (auto& container : to_delete) {
						v_shapes.erase(std::remove(v_shapes.begin(), v_shapes.end(), container), v_shapes.end());
					}
					to_delete.clear();

					// Clear container.
					container.get_shapes()->clear();
				}
			}
		
			//Set current shape to default settings

			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				if (current_shape) {
					current_shape->setToDefault();
				}
				/*if (current_composite) {
					for (auto& shp : *dynamic_cast<Composite*>(current_composite)->get_shapes()) {
						shp->setToDefault();
					}
				}*/
			}

			//Adding shapes to the vector
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)
			{
				v_shapes.push_back(circle.clone());
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
			{
				v_shapes.push_back(ellipse.clone());
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3)
			{
				v_shapes.push_back(rectangle.clone());
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4)
			{
				v_shapes.push_back(line.clone());
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num5)
			{
				if (current_composite) {
					v_shapes.push_back(current_composite->clone());
				}
				else if(current_shape)
				{
					v_shapes.push_back(current_shape->clone());
				}
			}
			//Deletes current shape/composite
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Delete) {
				if (!v_shapes.empty()) {
					if (current_composite) {
						v_shapes.erase(std::remove(v_shapes.begin(), v_shapes.end(), current_composite), v_shapes.end());
						current_composite = nullptr;
					}
					else {
						v_shapes.erase(std::remove(v_shapes.begin(), v_shapes.end(), current_shape), v_shapes.end());
						current_shape = nullptr;
					}
				}
			}

			//Changes color
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
			{
				sf::Color color(rand() % 256, rand() % 256, rand() % 256);
				if (current_composite) {
					for (auto& shape : *dynamic_cast<Composite*>(current_composite)->get_shapes()) {
						shape->setFillColor(color);
					}
				}
				if(current_shape) 
				{
					current_shape->setFillColor(color);
				}
			}
			//Activates tail
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
				if (!is_tail) {
					is_tail = true;
				}
				else {
					is_tail = false;
				}
			}
			//Saving current scene
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
				Composite to_save;
				to_save.get_shapes()->insert(to_save.get_shapes()->begin(), v_shapes.begin(), v_shapes.end());
				memento.save(to_save);
				memento.save_to_file(to_save);
				
			}
			//Loading previous saving
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L) {
				Composite to_load;
				memento.load(to_load);
				v_shapes.clear();
				for (auto& cont_shape : *to_load.get_shapes()) {
					v_shapes.push_back(cont_shape);
				}
				to_load.get_shapes()->clear();
			}
			//Make current shape go to cursor
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
				if (current_shape)
				{
					sf::Vector2f distandce(sf::Mouse::getPosition((*window->getWindow())).x - current_shape->getPosition().x,
						sf::Mouse::getPosition((*window->getWindow())).y - current_shape->getPosition().y);

					current_shape->move(distandce *0.06f);
				}
			}
		}




		if (current_shape) {
			moving(current_shape);
		}
		if (current_composite) {
			dynamic_cast<Composite*>(current_composite)->moving_together();
		}
		container.moving_together();

		if (!is_tail) {
			window->getWindow()->clear();
		}

		//Deformation
		if (current_shape) {
			bool is_container = false;
			for (auto& elem : v_shapes) {
				if (dynamic_cast<Composite*>(elem)) {
					is_container = true;
					for (auto& shape : *dynamic_cast<Composite*>(elem)->get_shapes()) {
						if (current_shape->getGlobalBounds().intersects(shape->getGlobalBounds())) {
							current_shape->setScale(sf::Vector2f(1.3, 1.3));
							break;
						}
						else {
							current_shape->setScale(sf::Vector2f(1, 1));
						}
					}
					continue;
				}
				else if (current_shape->getGlobalBounds().intersects(elem->getGlobalBounds()) && current_shape != elem) {
					current_shape->setScale(sf::Vector2f(1.3, 1.3));
					break;
				}
				else if(is_container == false) {
					current_shape->setScale(sf::Vector2f(1, 1));
				}
			}
		}
		if (current_composite) {
			for (auto& container : v_shapes) {

				if (dynamic_cast<Composite*>(container) && dynamic_cast<Composite*>(current_composite) != dynamic_cast<Composite*>(container)) {
					for (auto& shape2 : *dynamic_cast<Composite*>(current_composite)->get_shapes()) {
						shape2->setScale(sf::Vector2f(1, 1));
					}
					for (auto& shape : *dynamic_cast<Composite*>(container)->get_shapes()) {

						for (auto& shape1 : *dynamic_cast<Composite*>(current_composite)->get_shapes()) {

							if (shape->getGlobalBounds().intersects(shape1->getGlobalBounds())) {
								for (auto& shape2 : *dynamic_cast<Composite*>(current_composite)->get_shapes()) {
									shape2->setScale(sf::Vector2f(1.3, 1.3));
								}
							}
						}
					}
				}
				else if (dynamic_cast<Composite*>(current_composite) != dynamic_cast<Composite*>(container)){
					for (auto& shape2 : *dynamic_cast<Composite*>(current_composite)->get_shapes()) {
						shape2->setScale(sf::Vector2f(1, 1));
					}
					for (auto& shape1 : *dynamic_cast<Composite*>(current_composite)->get_shapes()) {
						if (shape1->getGlobalBounds().intersects(container->getGlobalBounds())) {
							for (auto& shape2 : *dynamic_cast<Composite*>(current_composite)->get_shapes()) {
								shape2->setScale(sf::Vector2f(1.3, 1.3));
							}
						}
					}
				}
			}
		}
		
		//Window bounds
		for (auto& shape : v_shapes)
		{
			if (dynamic_cast<Composite*>(shape)) {
				dynamic_cast<Composite*>(shape)->bounds(*window->getWindow());
			}
			if (shape != nullptr && current_composite == nullptr) {

				if (shape->getPosition().x <= shape->getOrigin().x)
				{
					shape->setPosition(shape->getOrigin().x, shape->getPosition().y);
				}
				if (shape->getPosition().x >= window->getWindow()->getSize().x - shape->getOrigin().x)
				{
					shape->setPosition(window->getWindow()->getSize().x - shape->getOrigin().x, shape->getPosition().y);
				}
				if (shape->getPosition().y >= window->getWindow()->getSize().y - shape->getOrigin().y)
				{
					shape->setPosition(shape->getPosition().x, window->getWindow()->getSize().y - shape->getOrigin().y);
				}
				if (shape->getPosition().y <= shape->getOrigin().y)
				{
					shape->setPosition(shape->getPosition().x, shape->getOrigin().y);
				}
			}
		}
		
		//Drawing all the elements from v_shapes
		for (auto& shape : v_shapes) {
			if (dynamic_cast<Composite*>(shape)) {
				for (auto& composite_shape : *dynamic_cast<Composite*>(shape)->get_shapes()) {
					window->getWindow()->draw(*composite_shape);
				}
			}
			else if (shape != nullptr) {
				window->getWindow()->draw(*shape);
			}
			else {}
		}

		window->getWindow()->display();
	}

	return 0;
}


void select_shape(std::vector<sf::Shape*>& v_shapes, sf::RenderWindow& window, sf::Shape*& current_composite, sf::Shape*& current_shape) {
	sf::Vector2f mouse_position;
	mouse_position.x = sf::Mouse::getPosition(window).x;
	mouse_position.y = sf::Mouse::getPosition(window).y;

	for (auto& shape : v_shapes)
	{
		//Checking if v_shapes`s element has Composite type
		if (dynamic_cast<Composite*>(shape)) {
			//Checking if user choose shape from composite
			for (auto& shape_ : *dynamic_cast<Composite*>(shape)->get_shapes()) {
				if (shape_->getGlobalBounds().contains(mouse_position)) {
					current_composite = shape;
					current_shape = nullptr;
					std::cout << "composite selected" << std::endl;
					return;
				}
				else {
					current_composite = nullptr;
				}

			}
		}
		else if (shape->getGlobalBounds().contains(mouse_position))
		{
			std::cout << "shape selected" << std::endl;
			current_shape = shape;
			current_composite = nullptr;
			return;
		}
		else
		{
			current_shape = nullptr;
		}
	}
}
