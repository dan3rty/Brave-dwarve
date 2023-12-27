#include <iostream>
#include "Key.h"

Key::Key(const sf::Vector2f& initialPosition, KEY_TYPE keyType)
{
	bounds.setPosition(initialPosition);
	image.loadFromFile("../res/keys.png");
	image.createMaskFromColor(sf::Color(224, 32, 64));
	texture.loadFromImage(image);
	bounds.setSize(sf::Vector2f(KEY_SIZE, KEY_SIZE));
	bounds.setTexture(&texture);
	if (keyType == KEY_TYPE::BRONZE)
	{
		 xTexture = 0;
	}
	else if (keyType == KEY_TYPE::SILVER)
	{
		xTexture = int(KEY_SIZE);
	}
	else
	{
		xTexture = int(KEY_SIZE * 2);
	}
	bounds.setTextureRect(sf::IntRect(xTexture, 0, (int)KEY_SIZE, (int)KEY_SIZE));
	bounds.setOrigin(KEY_SIZE / 2, KEY_SIZE / 2);
}

void Key::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!isFounded)
	{
		target.draw(bounds, states);
	}
}

void Key::update(const sf::FloatRect &playerPosition, float elapsedTime)
{
	animationTimer += elapsedTime;
	const int maxImages = 3;
	const float frameDuration = 0.07f;
	int curPixelY = (int(animationTimer / frameDuration) % maxImages) * (int)KEY_SIZE;
	bounds.setTextureRect(sf::IntRect(xTexture, curPixelY, (int)KEY_SIZE, (int)KEY_SIZE));
	if (playerPosition.intersects(bounds.getGlobalBounds()))
	{
		isFounded = true;
	}
}