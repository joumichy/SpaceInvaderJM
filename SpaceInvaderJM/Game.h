#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "Alien.h"
#include "Wall.h"
#include <list>



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

	//Wall Gestion
	void initListWalls(std::vector<Wall>& listWall, sf::Texture& texture, std::string wallImagePath);
	void moveWalls(std::vector<Wall>& listWall);
	void gameInit(sf::Text& livesText);
	bool isGameOver();
	void setGameOver(bool gameover);
	void alienShoot(std::vector<Alien>& aliens, std::vector<Bullet>& alienBullet );
	//TextGestion

	void updateText();

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
	

	sf::Texture textureAlien;
	sf::Sprite spriteAlien;

	sf::Texture textureWall;
	sf::Sprite spriteWall;


	sf::Text scoreText;
	sf::Text livesText;



	

};