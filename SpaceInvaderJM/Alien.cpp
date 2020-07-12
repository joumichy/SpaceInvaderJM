#include "Alien.h"


//Alien init 
Alien::Alien() {

	//Not dead
	dead = false;

};

Alien::Alien(int x, int y) :Entity() {
	//Not dead
	dead = false;
};


bool Alien::checkCol(Bullet& bullet) 
{

	sf::RectangleShape bulletShape;
	bulletShape = bullet.getShape();
	//Si la balle entre en collision avec le vaisseau du joueur
	if (bulletShape.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
		setDead(true);
		return true;
	}
	return false;
}

void Alien::movementAlea(sf::Vector2f vector) {
	
}

bool Alien::isDead() {

	return dead;

}

void Alien::setDead(bool death) {

	dead = death;

}






