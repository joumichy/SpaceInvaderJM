#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Alien {

public:
	Alien(int x, int y);

	void update();
	void draw(sf::RenderWindow& window);
	void setSpeed(sf::Vector2f vector);


private:
	sf::Vector2f position;
	sf::Vector2f speed;

	sf::Texture texture;
	sf::Sprite sprite;


};