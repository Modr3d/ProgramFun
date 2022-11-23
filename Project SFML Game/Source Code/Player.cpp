#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,float jumpHeight) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	switchTimex = 0.5f;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(80.0f, 100.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(200.0f, 1000.0f);
	body.setTexture(texture);
}

Player::~Player()
{

}

bool Player::Update(float deltaTime, bool canRun, float playerPos)
{
	velocity.x *= 0.5f;
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) && canRun == 1) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && playerPos > 1010.0f))
		velocity.x -= speed;
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) && canRun == 1) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && playerPos < -715.0f))
		velocity.x += speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump && punch != true)
	{
		canJump = false;
		newJump = true;
		velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && punchTime >= 1.5f)
	{
		newJump = true;
		punch = true;
		punchTime = 0;
		punchCD = 1;
	}

	if (punchCD == 1)
	{
		punchTime += deltaTime;
	}
	if (punchTime >= 1.5f)
	{
		punchCD = 0;
	}

	velocity.y = velocity.y+(981.0f * deltaTime);
	if (punch == true)
	{
		row = 3;
		if (velocity.x > 0.0f || velocity.x < 0.0f)
		{
			if (velocity.x > 0.0f)
			{
				if(canRun == 1)
					velocity.x += speed;
				faceRight = true;
			}
			else
			{
				if (canRun == 1)
					velocity.x -= speed;
				faceRight = false;
			}
		}
	}
	else if (canJump == false)
	{
		row = 2;
		if (velocity.x > 0.0f || velocity.x < 0.0f)
		{
			if (velocity.x > 0.0f)
				faceRight = true;
			else
				faceRight = false;
		}
	}
	else if (velocity.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;
		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	punchEnd = animation.Update(row, deltaTime, faceRight,newJump);
	newJump = false;
	if (punchEnd == true)
	{
		punch = false;
	}
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
	if (punch == true)
		return true;
	return false;
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::OnCollision(sf::Vector2f direction)
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
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		//Collision on the top
		velocity.y = 0.0f;
	}
}

void Player::SetPosition(sf::Vector2f position)
{
	body.setPosition(position);
}
void Player::SetSpeed(float newspeed)
{
	speed = newspeed;
}