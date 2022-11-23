#include "GreenOrge.h"
#include<math.h>

GreenOrge::GreenOrge(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	goanimation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(80.0f, 110.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(400.0f, 1000.0f);
	body.setTexture(texture);
}

GreenOrge::~GreenOrge()
{

}

bool GreenOrge::Update(float deltaTime, sf::Vector2f playerPos, sf::Vector2f greenorgePos, bool beenAtk, bool Orgeattack)
{
	velocity.x = 0.0f;

	if (abs(playerPos.x - greenorgePos.x) < 500)
	{
		velocity.x = 0.0f;
		if (newWalk == 1)
		{
			newHurt = true;
			newWalk = 0;
		}
	}
	else if (playerPos.x < greenorgePos.x)
	{
		velocity.x -= speed;
		newWalk = 1;
	}
	else if (playerPos.x > greenorgePos.x)
	{
		velocity.x += speed;
		newWalk = 1;
	}
	if (velocity.x == 0.0f)
	{
		if (playerPos.x < greenorgePos.x)
			faceRight = true;
		else if (playerPos.x > greenorgePos.x)
			faceRight = false;
	}

	velocity.y = velocity.y + (981.0f * deltaTime);

	if (beenAtk == 1)
	{
		hurt = true;
		newHurt = true;
	}
	else if (Orgeattack == 1 && hurt != true)
	{
		Attack = true;
		newHurt = true;
	}

	if (hurt == true)
	{
		row = 3;
		velocity.x = 0.0f;
		Attack = false;
	}
	else if (Attack == true && hurt != true)
	{
		row = 2;
		velocity.x = 0.0f;
	}
	else if (velocity.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;
			if (velocity.x > 0.0f)
				faceRight = false;
			else if (velocity.x < 0.0f)
				faceRight = true;
	}

	hurtEnd = goanimation.Update(row, deltaTime, faceRight, newHurt);
	if (hurtEnd == true && Attack != 1)
	{
		hurt = false;
		Attack = false;
	}
	else if(hurtEnd == true && Attack == 1)
	{
		Attack = false;
		hurtEnd = false;
	}
	newHurt = false;
	body.setTextureRect(goanimation.uvRect);
	body.move(velocity * deltaTime);
	if (hurtEnd == true)
	{
		return true;
	}
	return false;
}

void GreenOrge::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void GreenOrge::OnCollision(sf::Vector2f direction)
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

void GreenOrge::SetPos(sf::Vector2f position)
{
	body.setPosition(position);
}
