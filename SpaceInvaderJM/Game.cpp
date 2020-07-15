#include "pch.h"
#include "Game.h"
#include "Ship.h"
#include "Alien.h"
#include "Wall.h"
#include "Bullet.h"


Game::Game(int width, int height) : w(WIDTH), h(HEIGHT), window(sf::VideoMode(WIDTH, HEIGHT), "Game"), ship(START_X, HEIGHT / 2)
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
	
	
	//FONT STYLE JEU
	sf::Font font;
	if (!font.loadFromFile("./Media/Font/arial.ttf")) {
		std::cout << "Echec fichier ttf" << std::endl;
		system("pause");
	}


	//SCORE SETTING
	scoreText.setFillColor(sf::Color::Green);
	scoreText.setFont(font);
	scoreText.setPosition(10.f, 100.f);
	scoreText.setCharacterSize(20);
	scoreText.setString(std::to_string(score));

	//LIVES SETTING
	livesText.setFillColor(sf::Color::Green);
	livesText.setFont(font);
	livesText.setPosition(10.f, 120.f);
	livesText.setCharacterSize(20);
	livesText.setString(std::to_string(lives));


	//GAME OVER SETTING
	gameOverText.setFillColor(sf::Color::Green);
	gameOverText.setFont(font);
	gameOverText.setPosition(WIDTH/3, HEIGHT/3);
	gameOverText.setCharacterSize(50);
	gameOverText.setString(std::to_string(lives));
	

	//INIT
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
	

	
	

	
	//Set Object
	const std::string alienImagePath = "./Media/Texture/alienship.png";
	const std::string alienImagePath2 = "./Media/Texture/alienship2.png";
	const std::string alienImagePath3 = "./Media/Texture/alienship3.png";
	const std::string alienImagePath4 = "./Media/Texture/alienship4.png";

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

	//Init ALiens Images
	if (!imageAlien.loadFromFile(alienImagePath)) {

		std::cout << "Erreur chargement Alien Image!" << std::endl;
	}
	imageAlien.createMaskFromColor(sf::Color::White);

	if (!imageAlien2.loadFromFile(alienImagePath2)) {

		std::cout << "Erreur chargement Alien Image!" << std::endl;
	}
	imageAlien2.createMaskFromColor(sf::Color::White);

	if (!imageAlien3.loadFromFile(alienImagePath3)) {

		std::cout << "Erreur chargement Alien Image!" << std::endl;
	}
	imageAlien3.createMaskFromColor(sf::Color::White);

	if (!imageAlien4.loadFromFile(alienImagePath4)) {

		std::cout << "Erreur chargement Alien Image!" << std::endl;
	}
	imageAlien4.createMaskFromColor(sf::Color::White);
	
	

	if (!window.isOpen()) 
	{
		std::cout << "ERREUR Window !" << std::endl;
		return EXIT_FAILURE;

	}
	initShip(textureShip, shipImagePath);

	//SET BACKGROUND
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
	
				alienShoot(aliens, alienBulletVector);
				
				clockAlienShot.restart();


			}

			if (clockMove.getElapsedTime().asSeconds() > 0.2)
			{
				
				moveEnemy(entitiesEnemy);
				aleaAliensMove(entitiesEnemy);
				eventHandlerPLayerShooting(events, bulletVector);

				
				clockMove.restart();


			}


			if (clockAlienGenerator.getElapsedTime().asSeconds() > 6)
			{

				int WallOrAlien = rand() % 100 + 1;

				if (WallOrAlien > 33){
					initListAliens(newListAlien, textureAlien, alienImagePath);
					//initListWalls(newListWall, textureWall, wallImagePath);

				}
				else
				{
					initListWalls(newListWall, textureWall, wallImagePath);
					//initListAliens(newListAlien, textureAlien, alienImagePath);
				}

				clockAlienGenerator.restart();





			}
			//Clear Window's screen


			window.draw(spriteBackground);
			//TODO !
			eventHandler(events,
				bulletVector,
				alienBulletVector,
				aliens,
				walls,
				ship);

			

			for (unsigned int i = 0; i < entitiesEnemy.size(); i++) {
				entitiesEnemy[i].draw(window);

			}

			updateText();

			
			ship.draw(window);
			
			window.draw(scoreText);
			window.draw(livesText);
		

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
void Game:: eventHandlerPLayerShooting(sf::Event events,
	std::vector<Bullet>& bulletVector
) {
	bool isShooting = false;

	//Shooting
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{

		//Play Shoot
		isShooting = true;

	}


	if (isShooting == true) {

		//Création d'une nouvelle balle
		Bullet newBullet(sf::Vector2f(10, 5));

		//Position de la balle à la position du vaisseau
		newBullet.setPos(sf::Vector2f(ship.getX(), ship.getY() + 20));

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

	//Bullet Alien on Ship
	for (unsigned int i = 0; i < alienBulletVector.size(); i++) {

		if (ship.getSprite().getGlobalBounds().intersects(alienBulletVector[i].getShape().getGlobalBounds())
		&& !alienBulletVector[i].isShipBullet()) {

				
				alienBulletVector.erase(alienBulletVector.begin() + i);
				lives -= 1;//Retire une vie
				if (lives == 0) {

					setGameOver(true);
				}
				ship.setPositionXY(START_X, START_Y);//Reset position

		};


	}

	//Impact Enemy

	//IMPACT Alien & WALL
	for (unsigned int i = 0; i < bulletVector.size(); i++) {
		
		
		for (unsigned int elem = 0; elem < entitiesEnemy.size(); elem++) {
		
				//HIT										//Bullet is from Player
				if (entitiesEnemy[elem].checkCollisionBullet(bulletVector[i]) && bulletVector[i].isShipBullet()) {

					//Kill Alien
					if (entitiesEnemy[elem].getType() == alienType) {
						
						entitiesEnemy.erase(entitiesEnemy.begin() + elem);
						score += 100;
					}

					//Destroy bullet
					bulletVector.erase(bulletVector.begin() + i);

					
					
				}
			
		}
	

		
	

		
	}
	
	
	//Wall and Aliens Physically HIT SHIP
	for (Entity enemy : entitiesEnemy) {

		if (enemy.getSprite().getGlobalBounds().intersects(ship.getSprite().getGlobalBounds())) {
			lives -= 1;
			ship.setPositionXY(START_X, START_Y);
			if (lives == 0) {

				setGameOver(true);
			}

		}
	}
	
	
}
void Game::aleaAliensMove(std::vector<Entity>& enemies) {
	//for(alien)
	for (int i = 0; i < enemies.size(); i++) {
		
		if (enemies[i].getType() == 1) {

			int movementAlea = rand() % 100 + 1;
			double height = (double)MAX_HEIGHT;
			double test = (double)70 / 100;

			if (movementAlea <= 33) {
				if ((double)enemies[i].getY() < height *(double)(70 / 100)) {
					enemies[i].setSpeed(sf::Vector2f(0, SPEED));
					enemies[i].update();
				}
				else if ((double)enemies[i].getY() > height *(double)(70 / 100)) {
					enemies[i].setSpeed(sf::Vector2f(0, -SPEED*2));
					enemies[i].update();
				}

			}
			else if (movementAlea > 33 && movementAlea <= 66) {

				if ((double)enemies[i].getY() < height *(double)(70 / 100)) {
					enemies[i].setSpeed(sf::Vector2f(SPEED, -SPEED));
					enemies[i].update();
				}
				else {
					enemies[i].setSpeed(sf::Vector2f(SPEED, SPEED*2));
					enemies[i].update();
				}

			}
			else {
				enemies[i].setSpeed(sf::Vector2f(-SPEED * 2, 0));
				enemies[i].update();
			}

		}
		

	
	}

}

//Move all Aliens

void Game:: moveEnemy(std::vector<Entity>& enemiesEntity) {
	for (unsigned int i = 0; i < enemiesEntity.size(); i++) {
		enemiesEntity[i].setSpeed(sf::Vector2f(-SPEED, 0));
		enemiesEntity[i].update();

	}

}



//Init Player Ship
void Game::initShip(sf::Texture& textureShip, std::string shipImagePath) {


	if (!imageShip.loadFromFile(shipImagePath)) {

		std::cout << "Erreur chargement Ship Image!" << std::endl;
	}
	imageShip.createMaskFromColor(sf::Color::White);
	textureShip.loadFromImage(imageShip);
	
	
	sf::Sprite spriteShip;
	spriteShip.setTexture(textureShip);
	spriteShip.rotate(90);

	ship.setSpriteFromSprite(spriteShip);
	ship.setPositionXY(START_X, HEIGHT / 2);
}
void Game::initListAliens(std::vector<Alien> &listAlien,sf::Texture& texture, std::string alienImagePath) {


	/*if (!imageAlien.loadFromFile(alienImagePath)) {

		std::cout << "Erreur chargement Wall Image!" << std::endl;
	}*/
	imageAlien.createMaskFromColor(sf::Color::White);
	texture.loadFromImage(imageAlien);
	
	sf::Sprite sprite;

	sprite.setTexture(texture);
	sprite.rotate(-90);
	
	int numberOfAliens = rand() % 4 + 1;
	int positionOfAliens = rand() % 10 + 1;
	for (unsigned int i = 0; i < numberOfAliens; i++) {
		//Alien alien(600,600);
		
		alien.setSpriteFromSprite(sprite);
		alien.setPositionXY(MAX_WIDTH, PADDING_Y+ positionOfAliens*10 + (i * 100));
	
		alien.setType(alienType);
		aliens.push_back(alien);
		entitiesEnemy.push_back(alien);
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
		entitiesEnemy.push_back(wall);
		
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