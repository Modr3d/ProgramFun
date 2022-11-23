#include "Pause.h"

Pause::Pause(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

Pause::~Pause()
{
}

void Pause::SetPos(sf::Vector2f pos)
{
	body.setPosition(pos);
}

void Pause::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}