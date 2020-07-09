
#include "pch.h"
#pragma once


enum EnemyType {

	alienType = 1,
	wallType = 2,
};
class Entity {

public:
	Entity(int x, int y);

	Entity();


	void update();//Mettre � jour position
	void draw(sf::RenderWindow& window);//Afficher ) l'�cran
	void setImage(const std::string& path, const std::int16_t& angle);
	void setSpeed(sf::Vector2f vector);//Mettre � jour la position

	void setPosition(sf::Vector2f position);
	void setPositionXY(int x, int y);
	void setSpriteFromSprite(sf::Sprite mysprite);
	sf::Sprite getSprite();

	EnemyType getType();
	void setNewTexture(sf::Texture texture);
	void setType(EnemyType type);


	int getX();
	int getY();


protected:

	//Attribut
	sf::Vector2f position;
	sf::Vector2f speed;
	sf::Texture texture;//Zone d'image
	sf::Sprite sprite;//Image personnalis�e
	EnemyType type;
	


};