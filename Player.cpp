#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "Player.h"

Player::Player(sf::Texture* texture)
{
	this->shape.setTexture(*texture);
	this->shape.setScale(0.1f, 0.1f);
	this->MaxHp = 10;
	this->Hp = this->MaxHp;
	/*this->shape.setOrigin(shape.getPosition, shape.);
	this->shape.setRotation(100.f);
	this->shape.setPosition(400.f, 300.f);*/
}

sf::Sprite Player::GetPlayerModel()
{
	return shape;
}

void Player::DecreaseHp()
{
	Hp--;
}

int Player::GetHp()
{
	return Hp;
}

int Player::GetMaxHp()
{
	return MaxHp;
}
