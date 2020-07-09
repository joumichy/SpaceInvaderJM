#pragma once
#include "pch.h"
#include "Ship.h"
#include "Alien.h"
#include "Wall.h"




class Game
{

public:

	Game(int width, int height);
	int mainloop();
	void eventHandler(sf::Event events,
		std::vector<Bullet>& bulletVector,
		Alien& alien,
		std::vector<Alien>& listAlien,
		std::vector<Wall>& listWall,
		Ship& ship,
		std::vector<std::vector<Alien>>& allListAlien,
		std::vector<Alien>& newlistAlien,
		std::vector<Bullet>& alienBulletVector);
	
	//Alien Gestion
	void initListAliens(std::vector<Alien>& listAlien, sf::Texture& texture, std::string alienImagePath);
	void moveAliens(std::vector<Alien>& listAlien);
	void aleaAliensMove(std::vector<Alien>& listAlien);

	

	//Wall Gestion
	void initListWalls(std::vector<Wall>& listWall, sf::Texture& texture, std::string wallImagePath);
	void moveWalls(std::vector<Wall>& listWall);
	void gameInit(sf::Text& livesText);
	bool isGameOver();
	void setGameOver(bool gameover);
	void alienShoot(std::vector<Alien>& aliens, std::vector<Bullet>& alienBullet );
	//TextGestion

	void updateText();
	void initShip(sf::Texture& texture, std::string wallImagePath);


private:

	Ship ship;
	Alien alien;
	Wall wall;

	sf::RenderWindow window;
	int w, h;
	int score = 0;
	int lives = 3;
	bool gameOver = false;

	//Event Object
	std::vector<Alien> listAlien;
	std::vector<Alien> aliens;
	std::vector<Wall> walls;
	std::vector<Entity> entitiesEnemy;

	sf::Texture textureShip;
	sf::Texture textureAlien;
	sf::Texture textureWall;
	sf::Texture textureExplosion;
	sf::Texture textureBackGround;

	sf::Image imageExplosion;
	sf::Image imageWall;
	


	sf::Text scoreText;
	sf::Text livesText;
	sf::Text gameOverText;




	

};