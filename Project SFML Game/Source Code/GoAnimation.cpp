#include "GoAnimation.h"

GoAnimation::GoAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;

	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}

GoAnimation::~GoAnimation()
{

}

bool GoAnimation::Update(int row, float deltaTime, bool faceRight, bool newHurt)
{
	currentImage.y = row;
	totalTime += deltaTime;
	if (row == 0 || row == 3 || row == 2)
		imageCount.x = 4;
	else if (row == 1)
		imageCount.x = 6;
	if (newHurt == true)
		currentImage.x = 0;
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		if (row == 0)
		{
			if (currentImage.x >= imageCount.x - 1)
			{
				check = 1;
			}
			else if (currentImage.x <= 0)
			{
				check = 0;
			}
			if (check == 0)
				currentImage.x++;
			else if (check == 1)
				currentImage.x--;

		}
		else if (row == 1)
		{
			currentImage.x++;
			if (currentImage.x >= imageCount.x)
			{
				currentImage.x = 0;
			}
		}
		else if (row == 2)
		{
			if (currentImage.x < imageCount.x - 1)
				currentImage.x++;
			else
			{
				currentImage.x = 0;
				return true;
			}
		}
		else if (row == 3)
		{
			if (currentImage.x < imageCount.x - 1)
				currentImage.x++;
			else
			{
				currentImage.x = 0;
				return true;
			}
		}
	}

	uvRect.top = currentImage.y * uvRect.height;

	if (faceRight)
	{
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
	return false;
}