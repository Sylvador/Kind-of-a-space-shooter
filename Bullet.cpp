#include "Bullet.h"

Bullet::Bullet(sf::Texture* texture, sf::Vector2f pos)
{
	this->shape.setTexture(*texture);
	this->shape.setScale(0.1f, 0.1f);
	this->shape.setPosition(pos);
}