#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ship.h"

class Alien : public Ship{

public :

	Alien(int x, int y) :Ship(x, y){

		
	}

	void movement(sf::Vector2f vector);

private:

	//Attribut
	sf::Vector2f position;
	sf::Vector2f speed;

	sf::Texture texture;//Zone d'image
	sf::Sprite sprite;//Image personnalisée


};