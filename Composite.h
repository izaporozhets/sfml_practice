#pragma once


#include "Memento.h"
#include <cmath>
#include <fstream>
#include <algorithm>
class Composite : public sf::Shape 
{
public :

	Composite() {
		update();
	}

	Composite(sf::Shape* shape) {
		add_shape(shape);
		update();
	}

	Composite(Composite& container) {
		for (auto& shape : *container.get_shapes()) {
			shapes.push_back(shape->clone());
		}
	}

	void add_shape(sf::Shape* shape) {
		shapes.push_back(shape);
	}

	void setFillColor(const sf::Color& color)
	{
		for (auto& shape : shapes)
			if(shape != nullptr)
				shape->setFillColor(color);
	}

	void move(float offsetX, float offsetY)
	{
		for (auto& shape : shapes)
			shape->move(offsetX, offsetY);
	}

	void move(const sf::Vector2f& offset)
	{
		for (auto& shape : shapes)
			shape->move(offset);
	}

	void moving_together() {
		for (auto& shape : shapes) {
			
			moving(shape);
		}
	}

	void bounds(sf::RenderWindow& window)
	{
		for (auto& shape : shapes)
		{

			if(shape != nullptr){

				if (shape->getPosition().x <= shape->getOrigin().x)
				{
					shape->setPosition(shape->getOrigin().x, shape->getPosition().y);

					for (int i = 0; i < shapes.size();i++) {
						if (distancesx.size() != shapes.size()) {
							distancesx.push_back(abs(shapes[i]->getPosition().x - shape->getPosition().x));
						}
						shapes[i]->setPosition(distancesx[i] + shape->getOrigin().x, shapes[i]->getPosition().y);
					}
				}
				if (shape->getPosition().x >= window.getSize().x - shape->getOrigin().x)
				{
					shape->setPosition(window.getSize().x - shape->getOrigin().x, shape->getPosition().y);

					for (int i = 0; i < shapes.size(); i++) {
						if (distancesx1.size() != shapes.size()) {
							distancesx1.push_back(abs(shapes[i]->getPosition().x - shape->getPosition().x));
						}
						shapes[i]->setPosition(window.getSize().x - distancesx1[i] - shape->getOrigin().x, shapes[i]->getPosition().y);
					}
				}
				if (shape->getPosition().y >= window.getSize().y - shape->getOrigin().y)
				{
					shape->setPosition(shape->getPosition().x, window.getSize().y - shape->getOrigin().y);
					for (int i = 0; i < shapes.size(); i++) {
						if (distancesy.size() != shapes.size()) {
							distancesy.push_back(abs(shapes[i]->getPosition().y - shape->getPosition().y));
						}
						shapes[i]->setPosition(shapes[i]->getPosition().x, window.getSize().y - distancesy[i] - shape->getOrigin().y);
					}
				}
				if (shape->getPosition().y <= shape->getOrigin().y)
				{
					shape->setPosition(shape->getPosition().x, shape->getOrigin().y);
					for (int i = 0; i < shapes.size(); i++) {
						if (distancesy1.size() != shapes.size()) {
							distancesy1.push_back(abs(shapes[i]->getPosition().y - shape->getPosition().y));
						}
						shapes[i]->setPosition(shapes[i]->getPosition().x, distancesy1[i] + shape->getOrigin().y);
					}
				}
				
			}
		}
	}

	virtual std::size_t getPointCount() const
	{
		for (auto& shape : shapes)
			return shape->getPointCount();
	}
	virtual sf::Vector2f getPoint(std::size_t index) const
	{
		for (auto& shape : shapes)
			return shape->getPoint(index);
	}

	void set_memento(Memento& memento) const
	{
		memento.shots.clear();
		for (auto& elem : shapes) {
			memento.shots.push_back(elem->clone());
		}
	}

	void get_memento(Memento memento)
	{
		for (auto& elem : memento.shots) {
			shapes.push_back(elem->clone());
		}
	}

	void save_to_file(Memento memento) {
		for (auto& elem : memento.shots) {
			std::fstream fout;
			fout.open("saving.txt", std::ios::out | std::ios::app);
			fout << elem->getScale().x << ',' << elem->getScale().y << ','
				<< elem->getPosition().x << ',' << elem->getPosition().y;

			fout << '\n';
			fout.close();
		}
	}

	std::vector<sf::Shape*>* get_shapes()
	{
		return &shapes;
	}

	Shape* clone() override { return new Composite(*this); }
	
	void setToDefault() override {}

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		for (auto& shape : shapes) {
			target.draw(*shape);
		}
	}
	std::vector<sf::Shape*> shapes;

	std::vector<float> distancesx;
	std::vector<float> distancesy;
	std::vector<float> distancesx1;
	std::vector<float> distancesy1;

};