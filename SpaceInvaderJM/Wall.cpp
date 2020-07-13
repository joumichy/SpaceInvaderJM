#include "Wall.h";


Wall::Wall(int x, int y) :Entity() {

}

Wall::Wall():Entity() {

}
void Wall ::setSize(sf::Vector2f size) {
	
	size.x = sprite.getScale().x;
	sprite.setScale(size);
}



