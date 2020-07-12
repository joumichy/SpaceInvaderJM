#include "pch.h"
#include "Game.h"
#include "Ship.h"
#include "Alien.h"
#include "Wall.h"
#include "Bullet.h"


Game::Game(int width, int height) : w(WIDTH), h(HEIGHT), window(sf::VideoMode(WIDTH, HEIGHT), "Game"), ship(START_X, HEIGHT / 2), alien(600, HEIGHT / 2), listAlien()
{


}





int Game::mainloop()
{
	sf::Event events;
	sf::Clock clock;
	sf::Clock clockMove;
	sf::Clock clockAlienGenerator;
	sf::Clock clockAlienShot;
	sf::Clock clockExplosion;
	sf::Time time;
	time = clockExplosion.getElapsedTime();
	

	sf::Font font;
	if (!font.loadFromFile("./Media/Font/arial.ttf")) {
		std::cout << "Echec fichie ttf" << std::endl;
		system("pause");
	}
	scoreText.setFillColor(sf::Color::Green);
	scoreText.setFont(font);
	scoreText.setPosition(10.f, 100.f);
	scoreText.setCharacterSize(20);
	scoreText.setString(std::to_string(score));


	livesText.setFillColor(sf::Color::Green);
	livesText.setFont(font);
	livesText.setPosition(10.f, 120.f);
	livesText.setCharacterSize(20);
	livesText.setString(std::to_string(lives));



	gameOverText.setFillColor(sf::Color::Green);
	gameOverText.setFont(font);
	gameOverText.setPosition(WIDTH/3, HEIGHT/3);
	gameOverText.setCharacterSize(50);
	gameOverText.setString(std::to_string(lives));
	
	//Define Object
	//std::vector<Alien> listAlien;
	//std::vector<Wall> listWall;
	
	

	std::vector<Bullet> bulletVector;
	std::vector<Bullet> alienBulletVector;

	Wall wall(MAX_WIDTH, 200);
	std::vector<std::vector<Wall>> allListWalls;
	std::vector<std::vector<Alien>> allListAlien;


	std::vector<Wall> newListWall;
	std::vector<Alien> newListAlien;
	
	newListAlien.resize(4);
	newListWall.resize(4);
	allListAlien.resize(TAB_Y);
	

	
	//initListWalls(listWall);

	
	//Set Object
	

	const std::string alienImagePath = "./Media/Texture/alienship.png";
	const std::string wallImagePath = "./Media/Texture/wall.png";
	const std::string shipImagePath  = "./Media/Texture/spaceship.png";
	const std::string exploisionImagePath = "./Media/Texture/explosion.png";
	const std::string backgroundImagePath = "./Media/Texture/background.png";

	
	//Image explosion
	if (!imageExplosion.loadFromFile(exploisionImagePath)) {

		std::cout << "Erreur chargement Explosion Image!" << std::endl;
	}
	imageExplosion.createMaskFromColor(sf::Color::White);
	textureExplosion.loadFromImage(imageExplosion);


	//image background
	if (!textureBackGround.loadFromFile(backgroundImagePath)) {

		std::cout << "Erreur chargement Background Image!" << std::endl;
	}
	
	textureBackGround.loadFromFile(backgroundImagePath);
	

	

	
	
	

	if (!window.isOpen()) 
	{
		std::cout << "ERREUR Window !" << std::endl;
		return EXIT_FAILURE;

	}
	initShip(textureShip, shipImagePath);
	sf::Sprite spriteBackground;
	textureBackGround.setRepeated(true);
	spriteBackground.setTextureRect(sf::IntRect(0, 0, WIDTH, HEIGHT));
	spriteBackground.setTexture(textureBackGround);

	

	window.setFramerateLimit(60);
	

	while (window.isOpen())
		//Tant que l'ecran est actif
	{
		//Si le joueur n'a pas perdu
		if (!gameOver) {
		

			while (window.pollEvent(events))
			{
				//On traite ici tous les events
				if (events.type == sf::Event::EventType::Closed)
				{
					//Arret écran
					window.close();
				}
			}



			//Gestion des evenements

			window.clear(sf::Color::Black);
			
			if (clock.getElapsedTime().asSeconds() > 1.0 / 30.0)
			{
				//Tous les 1/30 secondes on met à jour la position du vaisseau
				ship.update();
				clock.restart();

			}
			if (clockAlienShot.getElapsedTime().asSeconds() > 1)
			{
				//rand shot
				int prob = rand() % 100 + 1;
				alienShoot(aliens, alienBulletVector);
				clockAlienShot.restart();

			}

			if (clockMove.getElapsedTime().asSeconds() > 0.2)
			{
				
				//moveAliens(aliens);
				//moveWalls(walls);

				
				clockMove.restart();


			}


			if (clockAlienGenerator.getElapsedTime().asSeconds() > 5)
			{

				int WallOrAlien = rand() % 100 + 1;

				if (WallOrAlien > 50) {
					initListAliens(newListAlien, textureAlien, alienImagePath);

				}
				else
				{
					initListWalls(newListWall, textureWall, wallImagePath);
				}

				clockAlienGenerator.restart();





			}
			//Clear Window's screen


			window.draw(spriteBackground);
			eventHandler(events,
				bulletVector,
				alienBulletVector,
				aliens,
				walls,
				ship);

			//Show First Alien Colonne
			
			for (unsigned int i = 0; i < aliens.size(); i++) {
				aliens[i].draw(window);

			}

			if (clockExplosion.getElapsedTime().asSeconds() > 2) {

				for (unsigned int i = 0; i < aliens.size(); i++) {

					if (aliens[i].isDead()) {

						aliens.erase(aliens.begin() + i);
					}

				}
				clockExplosion.restart();

			}


			for (unsigned int i = 0; i < aliens.size(); i++) {
				if (aliens[i].isDead()) {

					//aliens[i].setNewTexture(textureExplosion);
					sf::Sprite sprite;
					sprite = aliens[i].getSprite();
					sprite.setTexture(textureExplosion);

					aliens[i].setSpriteFromSprite(sprite);



					//aliens.erase(aliens.begin() + i);
					clockExplosion.restart();


				}

			}

			//Show Wall
			for (unsigned int i = 0; i < walls.size(); i++) {
				walls[i].draw(window);
			}
			updateText();

			
			ship.draw(window);
			
			window.draw(scoreText);
			window.draw(livesText);
			//

			window.display();



			//Affcher l'ecran
		}
		else {

		std::string stringLives = "GAME OVER \n Score: " + std::to_string(score);
		gameOverText.setString(stringLives);
		window.clear();
		window.draw(gameOverText);
		window.display();

		}
		
		
		
	}

	

	
	
}




void Game::eventHandler(sf::Event events,
	std::vector<Bullet>& bulletVector,
	std::vector<Bullet>& alienBulletVector,
	std::vector<Alien>& aliens,
	std::vector<Wall>& walls,
	Ship& ship)
{
	

	
	
	bool isShooting = false;
	
	float const speed = 4.0;
	if (events.type == sf::Event::EventType::KeyPressed)
	{
		//Si on appuie sur une touche on modifie la vitesse du vaisseau
		switch (events.key.code)
		{
		case sf::Keyboard::Left:
			{

			ship.setSpeed({ -SPEED, 0 });
			//std::cout << "Left !" << std::endl;

				break;
			}

		case sf::Keyboard::Right:
		{
			ship.setSpeed({ SPEED, 0});
			//std::cout << "Right !" << std::endl;

				break;
			}

		case sf::Keyboard::Up:
			{
			ship.setSpeed({ 0, -SPEED });
			//std::cout << "UP !" << std::endl;

				break;
			}

		case sf::Keyboard::Down:
			{
			ship.setSpeed({ 0, SPEED });

				break;
			}
	
		}
	}

	//Reseting Move
	else if (events.type == sf::Event::EventType::KeyReleased)
	{
		//Dès qu'on relache on remet la vitesse à 0;
		ship.setSpeed({0.0, 0.0});
	}


	//Shooting
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{

			//Play Shoot
			isShooting = true;
						
	}
	
	


	if (isShooting == true) {
		
		//Création d'une nouvelle balle
		Bullet newBullet(sf::Vector2f(10, 5));

		//Position de la balle à la position du vaisseau
		newBullet.setPos(sf::Vector2f(ship.getX(), ship.getY()+20));

		//Ajout de la balle dans une liste 
		bulletVector.push_back(newBullet);
		isShooting = false;//Reset Shooting
			

	}
	

	//Ship Shot
	for (unsigned int i = 0; i < bulletVector.size(); i++) {

		
		//Affichage écran
		bulletVector[i].draw(window);
	
		//Mouvement balle
		bulletVector[i].fire(5);

	}

	//Alien Shot
	for (unsigned int i = 0; i < alienBulletVector.size(); i++) {

		
		alienBulletVector[i].draw(window);
	
		alienBulletVector[i].fire(-5);
	 

	}

	//BUllet Alien on Ship
	for (unsigned int i = 0; i < alienBulletVector.size(); i++) {

		if (ship.getSprite().getGlobalBounds().intersects(alienBulletVector[i].getShape().getGlobalBounds())
		&& !alienBulletVector[i].isShipBullet()) {

				
				alienBulletVector.erase(alienBulletVector.begin() + i);
				lives -= 1;
				ship.setPositionXY(START_X, START_Y);

		};


	}


	//IMPACT Alien
	for (unsigned int i = 0; i < bulletVector.size(); i++) {
		
		for (unsigned int elem = 0; elem < aliens.size(); elem++) {

			//HIT										//Bullet is from Player
			if (aliens[elem].checkCol(bulletVector[i]) && bulletVector[i].isShipBullet()) {

				if (aliens[elem].isDead()) {


					//Kill Alien
					aliens.erase(aliens.begin() + elem);

					//Destroy bullet
					bulletVector.erase(bulletVector.begin() + i);

					score += 100;
				}


			};

		}
		//IMPACT MUR
		for (Wall wall : walls) {
			
			//Si la balle entre en collision avec un mur
			if (wall.getSprite().getGlobalBounds().intersects(bulletVector[i].getShape().getGlobalBounds())) {

				bulletVector.erase(bulletVector.begin() + i);
			}
		}
		
	

		
	

		
	}

	//Alien Hit  Ship
	for(Alien alien : aliens){

		
		if (alien.getSprite().getGlobalBounds().intersects(ship.getSprite().getGlobalBounds())) {
			lives -= 1;
			ship.setPositionXY(START_X, START_Y);
			if (lives == 0) {

				setGameOver(true);
			}

		}
	}
	
	
	
	
	for (Wall wall : walls) {

		if (wall.getSprite().getGlobalBounds().intersects(ship.getSprite().getGlobalBounds())) {
			lives -= 1;
			ship.setPositionXY(START_X, START_Y);
			if (lives == 0) {

				setGameOver(true);
			}

		}
	}
	
	
	
	
}
void Game::aleaAliensMove(std::vector<Alien>& listAlien) {
	//for(alien)
	for (int i = 0; i < listAlien.size(); i++) {

		int movement = rand() % 100 + 1;
		double height = (double)MAX_HEIGHT;
		double test = (double)70 / 100;

		if (movement <= 33) {
			if ((double)listAlien[i].getY() < height *(double)(70 / 100)) {
				listAlien[i].setSpeed(sf::Vector2f(0, SPEED));
				listAlien[i].update();
			}
			else if ((double)listAlien[i].getY() < height *(double)( 70/ 100))  {
				listAlien[i].setSpeed(sf::Vector2f(0, -SPEED));
				listAlien[i].update();
			}
			
		}
		else if (movement > 33 && movement <= 66) {

			if ((double)listAlien[i].getY() < height *(double)(70 / 100)) {
				listAlien[i].setSpeed(sf::Vector2f(SPEED, SPEED));
				listAlien[i].update();
			}
			else {
				listAlien[i].setSpeed(sf::Vector2f(SPEED, -SPEED));
				listAlien[i].update();
			}
			
		}
		else {
			listAlien[i].setSpeed(sf::Vector2f(-SPEED*2, 0));
			listAlien[i].update();
		}

	
	}

}

//Move all Aliens
void Game::moveAliens(std::vector<Alien>& listAlien) {

	for (int i = 0; i < listAlien.size(); i ++) {
		listAlien[i].setSpeed(sf::Vector2f(-SPEED,0));
		listAlien[i].update();
	}
	

}

void Game::moveWalls(std::vector<Wall>& listWall) {
	for (unsigned int i = 0; i < listWall.size(); i++) {
		listWall[i].setSpeed(sf::Vector2f(-SPEED, 0));
		listWall[i].update();

	}

}



//Init Player Ship
void Game::initShip(sf::Texture& textureShip, std::string shipImagePath) {

	
	if (!textureShip.loadFromFile(shipImagePath)) {
		std::cout << "Erreur image ship " << std::endl;
	}
	
	sf::Sprite spriteShip;
	spriteShip.setTexture(textureShip);
	spriteShip.rotate(90);

	ship.setSpriteFromSprite(spriteShip);
	ship.setPositionXY(START_X, HEIGHT / 2);
}
void Game::initListAliens(std::vector<Alien> &listAlien,sf::Texture& texture, std::string alienImagePath) {

	if (!texture.loadFromFile(alienImagePath)) {
		std::cout << "Erreur image " << std::endl;
		system("pause");
	}
	

	sf::Sprite sprite;

	sprite.setTexture(texture);

	
	
	int numberOfAliens = rand() % 4 + 1;
	int positionOfAliens = rand() % 10 + 1;
	for (unsigned int i = 0; i < numberOfAliens; i++) {
		//Alien alien(600,600);
		
		alien.setSpriteFromSprite(sprite);
		alien.setPositionXY(MAX_WIDTH, PADDING_Y+ positionOfAliens*10 + (i * 100));
	
		alien.setType(alienType);
		aliens.push_back(alien);
	}

};

void Game::initListWalls(std::vector<Wall>& listWall, sf::Texture& texture,std::string wallImagePath) {

	//image Wall
	if (!imageWall.loadFromFile(wallImagePath)) {

		std::cout << "Erreur chargement Wall Image!" << std::endl;
	}
	imageWall.createMaskFromColor(sf::Color::White);
	textureWall.loadFromImage(imageWall);


	sf::Sprite sprite;
	

	sprite.setTexture(texture);
	int numberOfWall = rand() % 4 + 1;
	int positionOfWall = rand() % 10 + 1;
	for (unsigned int i = 0; i < numberOfWall; i++) {
		

		int wallLength = wall.getSprite().getGlobalBounds().width;
		wall.setSpriteFromSprite(sprite);
		wall.setPositionXY(MAX_WIDTH, PADDING_Y + positionOfWall + i*wallLength);
		wall.setType(wallType);
		walls.push_back(wall);
		
	}

}


void Game:: updateText() {

	std::string stringScore = "Score: " + std::to_string(score);
	scoreText.setString(stringScore);

	std::string stringLives = "Lives: " + std::to_string(lives);
	livesText.setString(stringLives);
}


bool Game::isGameOver() {

	return gameOver;
}

void Game::setGameOver(bool result) {

	gameOver = result;
}

//Alien shot
void Game::alienShoot(std::vector<Alien>& alien, std::vector<Bullet>& alienBulletVector) {
	bool toAlienMode = false;
	sf::Color color = sf::Color::Red;

	for (Alien alien : aliens) {
		int prob = rand() % +100 + 1;
		if (prob < PROB_SHOOT) {
	
			Bullet alienBullet(sf::Vector2f(10, 5), color);
			alienBullet.setPos(sf::Vector2f(alien.getX(), alien.getY()));
			
			alienBullet.setToAlienBullet(toAlienMode);
			alienBulletVector.push_back(alienBullet);
			
			

			//shot

		}
	}
}