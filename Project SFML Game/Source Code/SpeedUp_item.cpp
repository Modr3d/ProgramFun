#include "SpeedUp_item.h"

SpeedUp_item::SpeedUp_item(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

SpeedUp_item::~SpeedUp_item()
{
}

void SpeedUp_item::Update(float deltaTime)
{
	velocity.x = 0.0f;
	velocity.y = velocity.y + (981.0f * deltaTime);
	body.move(velocity * deltaTime);
}

void SpeedUp_item::SetPos(sf::Vector2f pos)
{
	body.setPosition(pos);
}

void SpeedUp_item::OnCollision(sf::Vector2f direction)
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

void SpeedUp_item::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}