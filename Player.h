#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "Bullet.h"
class Player
{
public:
	Player(sf::Texture* texture);
	sf::Sprite GetPlayerModel();
	sf::Sprite shape;
	std::vector <Bullet> bullets;
	void DecreaseHp();
	int GetHp();
	int GetMaxHp();
private:
	int Hp;
	int MaxHp;
};

