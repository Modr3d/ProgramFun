#include "Fireball.h"

Fireball::Fireball(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

Fireball::~Fireball()
{
}

void Fireball::Update(float deltaTime)
{
	velocity.x = 0.0f;
	velocity.y = velocity.y + (981.0f * deltaTime);
	body.move(velocity * deltaTime);
}

void Fireball::SetPos(sf::Vector2f pos)
{
	body.setPosition(pos);
}

void Fireball::OnCollision(sf::Vector2f direction)
{
	if (direction.y < 0.0f)
	{
		//Collision on the bottom
		velocity.y = 0.0f;
	}
	else if (direction.y > 0.0f)
	{
		//Collision on the top
		velocity.y = 0.0f;
	}
}

void Fireball::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}