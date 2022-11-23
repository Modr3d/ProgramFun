#include "Menu.h"

Menu::Menu(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

Menu::~Menu()
{
}

void Menu::SetPos(sf::Vector2f pos)
{
	body.setPosition(pos);
}

void Menu::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}