#include <SFML/Graphics.hpp>
#include "Entity.h"
class Wall :public Entity {

public:
	Wall(int x, int y);

	void setSize(sf::Vector2f size);


private:
	std::string path = "./Media/Texture/wall.png";
	sf::Vector2f size;
};