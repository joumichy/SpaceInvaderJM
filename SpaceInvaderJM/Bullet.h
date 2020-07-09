#pragma once
#include <SFML/Graphics.hpp>


class Bullet {

public : 
	Bullet(sf::Vector2f size);

	Bullet(sf::Vector2f size, sf::Color);


	void fire(int speed);
	void draw(sf::RenderWindow &window);
	void setPos(sf::Vector2f newPos);
	
	int getLeft();
	int getRight();
	int getTop();
	int getDown();
	void setToAlienBullet(bool bullet);
	bool isShipBullet();

	sf::RectangleShape getShape();
	

private:

	sf::RectangleShape bullet;
	bool shipBullet = true;

};
