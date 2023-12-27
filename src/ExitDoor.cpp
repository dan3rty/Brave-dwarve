#include <iostream>
#include "ExitDoor.h"

const sf::Vector2f INITIAL_POSITION = { 1400, 440 };
const float DOOR_SIZE = 128;
const float OPEN_TIME = 2.4;
ExitDoor::ExitDoor()
{
	bounds.setPosition(INITIAL_POSITION);
	image.loadFromFile("../res/doors.png");
	image.createMaskFromColor(sf::Color(224, 32, 64));
	texture.loadFromImage(image);
	bounds.setSize(sf::Vector2f(DOOR_SIZE, DOOR_SIZE));
	bounds.setTexture(&texture);
	bounds.setTextureRect(sf::IntRect(0, 0, DOOR_SIZE, DOOR_SIZE));
}

void ExitDoor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(bounds, states);
}

bool ExitDoor::update(const sf::FloatRect& playerPosition, bool isThreeKeys, float elapsedTime)
{
	if (playerPosition.intersects(bounds.getGlobalBounds()) && isThreeKeys && !isOpening)
	{
		isOpening = true;
		open(elapsedTime);
	}
	else if (isOpening)
	{
		open(elapsedTime);
	}
	if (isOpened)
	{
		bounds.setTextureRect(sf::IntRect((int)DOOR_SIZE, (int)DOOR_SIZE, (int)DOOR_SIZE, (int)DOOR_SIZE));
		return true;
	}
	return false;
}

void ExitDoor::open(float elapsedTime)
{
	animationTimer += elapsedTime;
	const int maxImages = 8;
	const float frameDuration = 0.3f;
	int curTexturePixelX = (int(animationTimer / frameDuration) % maxImages) * (int)DOOR_SIZE;
	int curTexturePixelY = 0;
	bounds.setTextureRect(sf::IntRect(curTexturePixelX, curTexturePixelY, (int)DOOR_SIZE, (int)DOOR_SIZE));
	if (animationTimer >= OPEN_TIME)
	{
		isOpened = true;
	}
}