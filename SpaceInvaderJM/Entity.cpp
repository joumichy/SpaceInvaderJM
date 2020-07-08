#include "Entity.h"

Entity::Entity(int x, int y) : position(x, y), speed(0.0, 0.0), texture(), sprite()
{



}

Entity::Entity() {

}

void Entity::update()
{
	//On met à jour la position de l'objet
	position.x += speed.x;
	position.y += speed.y;

	sprite.setPosition(position);

}

void Entity::draw(sf::RenderWindow& window)
{

	window.draw(sprite);

}

void Entity::setSpeed(sf::Vector2f vector)
{
	speed = vector;
}

void Entity::setImage(const std::string& path, const std::int16_t& angle)
{
	//On Chaarge l'image
	
	if (!texture.loadFromFile(path)) {
		std::cout << "Load Failed !" << std::endl;
		system("pause");

	}

	//Appliquer l'image à la zone
	sprite.setTexture(texture);
	sprite.rotate(angle);//Rotation horizontale
}


int Entity::getX() {
	return sprite.getPosition().x;
}

int Entity::getY() {

	return sprite.getPosition().y;

}

void Entity::setPosition(sf::Vector2f position) {

	sprite.setPosition(position);

}


void Entity::setPositionXY(int x, int y) {
	position.x = x;
	position.y = y;
	sprite.setPosition(position);

}
