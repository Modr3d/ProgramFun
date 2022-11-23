#include "Scores.h"

Scores::Scores(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

Scores::~Scores()
{
}

void Scores::SetPos(sf::Vector2f pos)
{
	body.setPosition(pos);
}

void Scores::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}