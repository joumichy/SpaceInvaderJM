#include "Ship.h"

Ship::Ship(int x, int y) : position(x, y), speed(0.0, 0.0), texture(), sprite()
{

	
	
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

void Ship::setImage(const std::string& path,const std::int16_t& angle)
{
	//On Chaarge l'image
	//Path : "./Media/Texture/spaceship.png"
	if (!texture.loadFromFile(path)) {
		std::cout << "Load Failed !" << std::endl;
		system("pause");

	}

	//Appliquer l'image à la zone
	sprite.setTexture(texture);
	sprite.rotate(angle);//Rotation horizontale
}