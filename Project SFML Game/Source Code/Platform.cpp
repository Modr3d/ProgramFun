#include "Platform.h"

Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

Platform::~Platform()
{
}

void Platform::SetPos(sf::Vector2f pos)
{
	pos.y = 1000.0f;
	body.setPosition(pos);
}

void Platform::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}