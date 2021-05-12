#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"

class Bullet
{
public:
	Bullet(sf::Texture* texture, sf::Vector2f pos);
	sf::Sprite shape;
};