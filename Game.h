#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include <vector>
#include <string>
class Game
{
public:
	Game();
	void run();

private:
	void processEvents();
	void update();
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	sf::RenderWindow window;

	sf::Clock clock;
	sf::Time timeSinceLastUpdate;
	sf::Time TimePerFrame;

	sf::Vector2f currentVelocity;
	sf::Vector2f direction;
	float maxVelocity = 25.f;
	float acceleration = 1.f;
	float drag = 0.5f;
	
	sf::Font font;

	sf::Texture playerTex;
	sf::Texture enemyTex;
	sf::Texture bulletTex;
	
	Player* player;
	sf::Text hpText;
	bool pIsMovingUp;
	bool pIsMovingDown;
	bool pIsMovingRight;
	bool pIsMovingLeft;
	bool pIsShooting;
	int shootTimer;

	std::vector <Enemy> enemies;
	int spawnTimer;
	sf::Text EhpText;

	int score;
	sf::Text scoreText;

	sf::Text gameOverText;
	bool gameOver;
};

