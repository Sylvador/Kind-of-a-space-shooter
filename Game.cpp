#include "Game.h"
#include "Player.h"
Game::Game()
	: window(sf::VideoMode(800, 600), "SFML boy")
{
	window.setFramerateLimit(120);
	timeSinceLastUpdate = sf::Time::Zero;
	TimePerFrame = sf::seconds(1.f / 60.f);
	
	if(!font.loadFromFile("Fonts/HanaleiFill-Regular.ttf"))
		throw "pizdec";
	
	enemyTex.loadFromFile("Textures/cat.png");
	bulletTex.loadFromFile("Textures/bullet.png");
	playerTex.loadFromFile("Textures/doge.png");

	player = new Player(&playerTex);
	hpText.setFont(font);
	hpText.setCharacterSize(24);
	hpText.setFillColor(sf::Color::White);
	pIsMovingDown = false;
	pIsMovingUp = false;
	pIsMovingRight = false;
	pIsMovingLeft = false;
	pIsShooting = false;
	shootTimer = 20;

	spawnTimer = 0;
	EhpText.setFont(font);
	EhpText.setCharacterSize(24);
	EhpText.setFillColor(sf::Color::White);

	score = 0;
	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(10.f, 10.f);

	gameOver = false;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(40);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setPosition(100.f, window.getSize().y/2);
	gameOverText.setString("YOU PROEBAL");
}

void Game::update()
{
	if (player->GetHp() > 0)
	{
	float speed = 23.f;
	sf::Vector2f movement;
	//Acceleration
	direction = sf::Vector2f(0.f, 0.f);
	if (pIsMovingUp)
	{
		/*direction.y = -1.f;

		if (currentVelocity.y > -maxVelocity)
			currentVelocity.y += acceleration * direction.y;*/
		movement.y -= speed;
	}
	if (pIsMovingDown)
	{
		/*direction.y = 1.f;

		if (currentVelocity.y < maxVelocity)
			currentVelocity.y += acceleration * direction.y;*/
		movement.y += speed;
	}
	if (pIsMovingLeft)
	{
		/*direction.x = -1.f;

		if (currentVelocity.x > -maxVelocity)
			currentVelocity.x += acceleration * direction.x;*/
		movement.x -= speed;
	}
	if (pIsMovingRight)
	{
		/*direction.x = 1.f;

		if (currentVelocity.x < maxVelocity)
			currentVelocity.x += acceleration * direction.x;*/
		movement.x += speed;
	}
	//Drag
	//if (currentVelocity.x > 0.f)
	//{
	//	currentVelocity.x -= drag;

	//	if (currentVelocity.x < 0.f)
	//		currentVelocity.x = 0.f;
	//}
	//else if (currentVelocity.x < 0.f)
	//{
	//	currentVelocity.x += drag;

	//	if (currentVelocity.x > 0.f)
	//		currentVelocity.x = 0.f;
	//}
	//else if (currentVelocity.y > 0.f)
	//{
	//	currentVelocity.y -= drag;

	//	if (currentVelocity.y < 0.f)
	//		currentVelocity.y = 0.f;
	//}
	//else if (currentVelocity.y < 0.f)
	//{
	//	currentVelocity.y += drag;

	//	if (currentVelocity.y > 0.f)
	//		currentVelocity.y = 0.f;
	//}

	//Final move
	player->shape.move(movement * (1.f / 60.f) * speed);
	
	//WINDOW COLLISION
	if (player->GetPlayerModel().getPosition().x >= window.getSize().x - player->GetPlayerModel().getGlobalBounds().width)
		player->shape.setPosition(window.getSize().x - player->shape.getGlobalBounds().width, player->shape.getPosition().y);
	if (player->GetPlayerModel().getPosition().x <= 0)
		player->shape.setPosition(0.f, player->shape.getPosition().y);
	if (player->GetPlayerModel().getPosition().y >= window.getSize().y - player->GetPlayerModel().getGlobalBounds().height)
		player->shape.setPosition(player->shape.getPosition().x, window.getSize().y - player->shape.getGlobalBounds().height);
	if (player->GetPlayerModel().getPosition().y <= 0)
		player->shape.setPosition(player->shape.getPosition().x, 0.f);

	hpText.setPosition(player->GetPlayerModel().getPosition().x, player->GetPlayerModel().getPosition().y - hpText.getGlobalBounds().height);
	hpText.setString(std::to_string(player->GetHp()) + "/" + std::to_string(player->GetMaxHp()));
	if (shootTimer < 10)
		shootTimer++;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootTimer >= 10)
	{
		shootTimer = 0;
		player->bullets.push_back(Bullet(&bulletTex, player->GetPlayerModel().getPosition() + sf::Vector2f(player->shape.getGlobalBounds().width/2, player->shape.getGlobalBounds().height / 2)));
	}
	for (size_t i = 0; i < player->bullets.size(); i++)
	{
		//Move
		player->bullets[i].shape.move(sf::Vector2f(1000.f, 0) * (1.f / 60.f));

		//Out of window bouds
		if (player->bullets[i].shape.getPosition().x > window.getSize().x)
		{
			player->bullets.erase(player->bullets.begin() + i);
			break;
		}

		//Enemy collision
		for (size_t k = 0; k < enemies.size(); k++)
		{
			if (player->bullets[i].shape.getGlobalBounds().intersects(enemies[k].shape.getGlobalBounds()))
			{
				enemies[k].Hp--;
				if (enemies[k].Hp <= 0)
				{
					score += enemies[k].HpMax;
					enemies.erase(enemies.begin() + k);
				}
				player->bullets.erase(player->bullets.begin() + i);
				break;
			}
		}
	}
	//Enemy
	if (spawnTimer < 30)
		spawnTimer++;

	if (spawnTimer >= 30)
	{
		enemies.push_back(Enemy(&enemyTex, sf::Vector2u(window.getSize())));
		spawnTimer = 0;
	}
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i].shape.move(sf::Vector2f(-250.f, 0) * (1.f / 60.f));

		if (enemies[i].shape.getPosition().x <= 0 - enemies[i].shape.getGlobalBounds().width)
		{
			enemies.erase(enemies.begin() + i);
			break;
		}
		if (enemies[i].shape.getGlobalBounds().intersects(player->GetPlayerModel().getGlobalBounds()))
		{
			enemies.erase(enemies.begin() + i);
			player->DecreaseHp();
			break;
		}
	}

	//UI UPDATE

	scoreText.setString("Score " + std::to_string(score));
}
}

void Game::render()
{
	window.clear();

	window.draw(player->GetPlayerModel());

	window.draw(scoreText);

	for (size_t i = 0; i < player->bullets.size(); i++)
	{
		window.draw(player->bullets[i].shape);
	}

	for (size_t i = 0; i < enemies.size(); i++)
	{
		EhpText.setString(std::to_string(enemies[i].Hp) + "/" + std::to_string(enemies[i].HpMax));
		EhpText.setPosition(enemies[i].shape.getPosition().x, enemies[i].shape.getPosition().y - EhpText.getGlobalBounds().height);
		window.draw(EhpText);
		window.draw(enemies[i].shape);
	}

	//UI
	window.draw(hpText);

	if (player->GetHp() <= 0)
		window.draw(gameOverText);

	window.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		pIsMovingUp = isPressed;
	if (key == sf::Keyboard::S)
		pIsMovingDown = isPressed;
	if (key == sf::Keyboard::A)
		pIsMovingLeft = isPressed;
	if (key == sf::Keyboard::D)
		pIsMovingRight = isPressed;
}

void Game::run()
{
	while (window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update();
		}
		render();
 	}
}

void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
		}
		if(event.type == sf::Event::KeyPressed)
			handlePlayerInput(event.key.code, true);
		if(event.type == sf::Event::KeyReleased)
			handlePlayerInput(event.key.code, false);
		
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			window.close();
	}
}
