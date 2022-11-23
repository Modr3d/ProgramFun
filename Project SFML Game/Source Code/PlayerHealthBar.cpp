#include "PlayerHealthBar.h"

PlayerHealthBar::PlayerHealthBar(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

PlayerHealthBar::~PlayerHealthBar()
{
}

void PlayerHealthBar::SetPos(sf::Vector2f pos)
{
	body.setPosition(pos);
}

void PlayerHealthBar::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}