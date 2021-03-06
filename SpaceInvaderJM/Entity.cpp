#include "Entity.h"

Entity::Entity(int x, int y) : position(x, y), speed(0.0, 0.0), texture(), sprite()
{



}

bool Entity:: checkCollisionBullet(Bullet& bullet) {
	
	sf::RectangleShape bulletShape;
	bulletShape = bullet.getShape();
	//Si la balle entre en collision avec le vaisseau du joueur
	if (bulletShape.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
		return true;
	}
	return false;

}

Entity::Entity() {

}

EnemyType Entity:: getType() {
	return type;
}

void Entity:: setType(EnemyType mytype) {
	this->type = mytype;
}

void Entity::update()
{
	//On met � jour la position de l'objet
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

	//Appliquer l'image � la zone
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

void Entity::setSpriteFromSprite(sf::Sprite mysprite)
{

	//Appliquer l'image � la zone
	this->sprite = mysprite;

}


sf::Sprite Entity:: getSprite() {

	return sprite;
}


void Entity::setNewTexture(sf::Texture texture) {

	sprite.setTexture(texture);
}

