#include "Bullet.h"
#include<math.h>

Bullet::Bullet(sf::Texture* texture, sf::Vector2f size, sf::Vector2f Pposition, sf::Vector2f Bposition)
{
	player = Pposition;
	bull = Bposition;
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(Bposition);
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	aimDir = player - bull;
	aimDirNorm = aimDir / float(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));
	currVelocity = aimDirNorm * maxSpeed;
	body.move(currVelocity);
}
void Bullet::SetPos(sf::Vector2f pos)
{
	body.setPosition(pos);
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}