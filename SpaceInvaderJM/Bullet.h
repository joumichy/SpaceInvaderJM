#pragma once
#include <SFML/Graphics.hpp>

class Bullet {

public : 
	Bullet(sf::Vector2f size);

	void fire(int speed);
	void draw(sf::RenderWindow &window);
	void setPos(sf::Vector2f newPos);
	
	int getLeft();
	int getRight();
	int getTop();
	int getDown();

	

private:

	sf::RectangleShape bullet;


};
