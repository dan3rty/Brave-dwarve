#include "Fireball.h"

Fireball::Fireball()
{
	image.loadFromFile("../res/fireball.png");
	image.createMaskFromColor(sf::Color(237, 28, 36));
	texture.loadFromImage(image);
	bounds.setSize(sf::Vector2f(FIREBALL_WIDTH, FIREBALL_HEIGHT));
	bounds.setTexture(&texture);
	bounds.setTextureRect(sf::IntRect(0, 0, (int)FIREBALL_WIDTH, (int)FIREBALL_HEIGHT));
}

void Fireball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (isActive)
	{
		target.draw(bounds, states);
	}
}

void Fireball::updateFireball(float elapsedTime, Field& field, Enemy& enemy)
{
	if (!isActive)
	{
		return;
	}
	const float step = FIREBALL_SPEED * elapsedTime;
	sf::Vector2f movement(0.f, 0.f);
	movement.x += isRightDirection ? step : -step;
	if (field.checkFieldFloorCollision(bounds.getGlobalBounds(), movement, false) != movement)
	{
		isActive = false;
	}
	if (enemy.checkEnemyCollision(bounds.getGlobalBounds(), movement) != movement)
	{
		isActive = false;
		enemy.die();
	}
	moveTimer += elapsedTime;
	const int maxImages = 3;
	const float frameDuration = 0.2f;
	//TODO: сделать анимацию типа 0 1 2 1 2 1 2 1 2
	int curPixelX = (int(moveTimer / frameDuration) % maxImages) * (int)FIREBALL_WIDTH;
	int curPixelY = 0;
	bounds.setTextureRect(sf::IntRect(curPixelX, curPixelY, (int)FIREBALL_WIDTH, (int)FIREBALL_HEIGHT));
	bounds.move(movement);
}

void Fireball::activateFireball(bool isRight, sf::Vector2f playerPosition)
{
	isActive = true;
	isRightDirection = isRight;
	bounds.setPosition(playerPosition);
}


