
#include <SFML/Graphics.hpp>
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Ship {

public:
	Ship(int x, int y);

	
	void update();//Mettre � jour position
	void draw(sf::RenderWindow& window);//Afficher ) l'�cran
	void setSpeed(sf::Vector2f vector);//Mettre � jour la position


private:

	//Attribut
	sf::Vector2f position;
	sf::Vector2f speed;

	sf::Texture texture;//Zone d'image
	sf::Sprite sprite;//Image personnalis�e

		
};