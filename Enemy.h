#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"

class Enemy
{
public:
	int Hp;
	int HpMax;
	sf::Sprite shape;

	Enemy(sf::Texture* texture, sf::Vector2u pos);
};