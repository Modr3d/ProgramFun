#include "M01.h"

M01::M01(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	m01Animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(70.0f, 70.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(400.0f, 1000.0f);
	body.setTexture(texture);
}

M01::~M01()
{

}

bool M01::Update(float deltaTime, sf::Vector2f playerPos, sf::Vector2f redorgePos, bool beenAtk)
{
	velocity.x = 0.0f;
	if(abs(playerPos.y - redorgePos.y) > 20 && playerPos.y < 645)
		jumpTime += (deltaTime);
	if (abs(playerPos.x - redorgePos.x) > 100 || beenAtk == 1 || hurt == 1)
		unstableMode = 0;
	if (playerPos.x - 20 < redorgePos.x && playerPos.x + 20 > redorgePos.x && unstableMode != 1 && hurt != 1)
		unstableMode = 1;
	else if (playerPos.x < redorgePos.x && unstableMode != 1)
		velocity.x -= speed;
	else if (playerPos.x > redorgePos.x && unstableMode != 1)
		velocity.x += speed;

	if (jumpTime > 2.0f)
	{
		velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
		jumpTime = 0.0f;
	}
	if (unstableMode == 1)
	{
		unstableTime = unstableTime + deltaTime;
		if (unstableTime < 2)
		{
			if (faceRight == 1)
				velocity.x -= speed;
			else
				velocity.x += speed;
		}
		else
		{
			unstableTime = 0;
			unstableMode = 0;
		}
	}
	velocity.y = velocity.y + (981.0f * deltaTime);

	if (beenAtk == 1)
	{
		hurt = true;
		newHurt = true;
	}
	if (hurt == true)
	{
		row = 3;
		velocity.x = 0.0f;
	}
	else if (velocity.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;
		if (unstableMode != 1)
			if (velocity.x > 0.0f)
				faceRight = false;
			else
				faceRight = true;
	}

	hurtEnd = m01Animation.Update(row, deltaTime, faceRight, newHurt);
	if (hurtEnd == true)
	{
		hurt = false;
	}
	newHurt = false;
	body.setTextureRect(m01Animation.uvRect);
	body.move(velocity * deltaTime);
	if (hurtEnd == true)
	{
		return true;
	}
	return false;
}

void M01::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void M01::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		//Collision on the left.
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//Collision on the right
		velocity.x = 0.0f;
	}
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

void M01::SetPos(sf::Vector2f position)
{
	body.setPosition(position);
}