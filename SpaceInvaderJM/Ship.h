
#include <SFML/Graphics.hpp>
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

class Ship {

public:
	Ship(int x, int y);

	
	void update();//Mettre � jour position
	void draw(sf::RenderWindow& window);//Afficher ) l'�cran
	void setImage(const std::string& path,const std::int16_t& angle);
	void setSpeed(sf::Vector2f vector);//Mettre � jour la position


protected:

	//Attribut
	sf::Vector2f position;
	sf::Vector2f speed;

	sf::Texture texture;//Zone d'image
	sf::Sprite sprite;//Image personnalis�e

		
};