#include "Ship.h"

Ship::Ship(int x, int y) : position(x, y), speed(0.0, 0.0),texture(),sprite()
{

	//On Chaarge l'image
	if (!texture.loadFromFile("./Media/Texture/spaceship.png")) {
		std::cout << "Load Failed !" << std::endl;
		system("pause");

	}

	//Appliquer l'image à la zone
	sprite.setTexture(texture);
	sprite.rotate(90);//Rotation horizontale
	
}

void Ship::update() 
{
	//On met à jour la position de l'objet
	position.x += speed.x;
	position.y += speed.y;

	sprite.setPosition(position);
		 
}

void Ship::draw(sf::RenderWindow& window)
{

	window.draw(sprite);

}

void Ship::setSpeed(sf::Vector2f vector)
{
	speed = vector;
}