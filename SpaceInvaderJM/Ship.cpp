#include "Ship.h"
#define START_X 50
#define START_Y 300

Ship::Ship(int x, int y) : position(START_X, START_Y), speed(0.0, 0.0), texture(), sprite()
{

	
	
}

Ship::Ship() {

}

sf::Sprite Ship :: getSprite() {
	return sprite;
}

void Ship::restart() {

	sprite.setPosition(START_X, START_Y);

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

void Ship::setImageFromTexture(sf::Texture texture, const std::int16_t& angle)
{
	
	//Appliquer l'image à la zone
	sprite.setTexture(texture);
	sprite.rotate(angle);//Rotation horizontale
	
}


void Ship::setSpriteFromSprite(sf::Sprite mysprite)
{

	//Appliquer l'image à la zone
	sprite = mysprite;

}


int Ship::getX() {
	return sprite.getPosition().x;
}

int Ship::getY(){

	return sprite.getPosition().y;

}

void Ship::setPosition(sf::Vector2f position) {

	sprite.setPosition(position);

}


void Ship::setPositionXY(int x, int y) {
	position.x = x;
	position.y = y;
	sprite.setPosition(position);

}
