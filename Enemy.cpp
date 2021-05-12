#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2u pos)
{
	this->HpMax = rand() % 3 + 1;
	this->Hp = this->HpMax;

	this->shape.setTexture(*texture);
	this->shape.setScale(0.2f, 0.2f);
	this->shape.setPosition(pos.x - this->shape.getGlobalBounds().width, rand() % (int)(pos.y - this->shape.getGlobalBounds().height));
}
