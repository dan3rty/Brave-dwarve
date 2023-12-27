#include <iostream>
#include "Enemy.h"

const float ENEMY_HEIGHT = 25.0f;
const float ENEMY_WIDTH = 64.0f;
const float DEATH_TIME = 2.0f; //TODO: change to 15
const float REVIVE_TIME = 3.0f;
constexpr float ENEMY_SPEED = 100.f;
const float DEATH_ANIMATION_TIME = 0.6f;

Enemy::Enemy(const sf::Vector2f& initialPosition)
{
	this->initialPosition = initialPosition;
	isRight = true;
	image.loadFromFile("../res/worm.png");
	image.createMaskFromColor(sf::Color(224, 32, 64));
	texture.loadFromImage(image);
	bounds.setPosition(this->initialPosition);
	bounds.setSize(sf::Vector2f(ENEMY_WIDTH, ENEMY_HEIGHT));
	bounds.setTexture(&texture);
	bounds.setTextureRect(sf::IntRect(0, 0, (int)ENEMY_WIDTH, (int)ENEMY_HEIGHT));
	bounds.setOrigin(ENEMY_WIDTH / 2, ENEMY_HEIGHT / 2);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (isAlive || reviveTimer != 0)
	{
		target.draw(bounds, states);
	}
}

sf::Vector2f Enemy::getMovement(float elapsedTime, Field& field)
{
	const float step = ENEMY_SPEED * elapsedTime;
	sf::Vector2f movement(0.f, 0.f);
	if (isRight)
	{
		movement.x += step;
		if (bounds.getScale() == sf::Vector2f(-1, 1))
		{
			bounds.setScale(1, 1);
		}
	}
	else
	{
		movement.x -= step;
		if (bounds.getScale() == sf::Vector2f(1, 1))
		{
			bounds.setScale(-1, 1);
		}

	}
	movement = field.checkFieldFloorCollision(bounds.getGlobalBounds(), movement, false);
	return movement;
}

void Enemy::updateEnemy(float elapsedTime, Field& field)
{
	if (isDying)
	{
		dying(elapsedTime);
		return;
	}
	if (!isAlive)
	{
		deathTimer += elapsedTime;
		if (deathTimer >= DEATH_TIME)
		{
			reviveEnemy(elapsedTime);
		}
		return;
	}
	auto movement = getMovement(elapsedTime, field);
	sf::Vector2f wallsCollision = field.checkFieldFloorCollision(bounds.getGlobalBounds(), movement, false);
	if (wallsCollision == sf::Vector2f(0, 0))
	{
		updateEnemyDirection();
	}
	moveTimer += elapsedTime;
	const int maxImages = 4;
	const float frameDuration = 0.07f;
	curTexturePixelX = (int(moveTimer / frameDuration) % maxImages) * (int)ENEMY_WIDTH;
	curTexturePixelY = 0;
	bounds.setTextureRect(sf::IntRect(curTexturePixelX, curTexturePixelY, (int)ENEMY_WIDTH, (int)ENEMY_HEIGHT));
	bounds.move(movement);
}

void Enemy::updateEnemyDirection()
{
	isRight = !isRight;
}

void Enemy::reviveEnemy(float elapsedTime)
{
	sf::Vector2f position = initialPosition;
	position.y -= 10;
	bounds.setPosition(position);
	reviveTimer += elapsedTime;
	moveTimer += elapsedTime;
	const int maxImages = 6;
	const float frameDuration = 0.6f;
	curTexturePixelX = (int(moveTimer / frameDuration) % maxImages) * (int)ENEMY_WIDTH;
	curTexturePixelY = (int)ENEMY_HEIGHT;
	bounds.setTextureRect(sf::IntRect(curTexturePixelX, curTexturePixelY, (int)ENEMY_WIDTH, (int)ENEMY_HEIGHT));
	if (reviveTimer >= REVIVE_TIME)
	{
		reviveTimer = 0;
		isAlive = true;
	}
}

static sf::FloatRect moveRect(const sf::FloatRect& rect, sf::Vector2f& offset)
{
	return { rect.left + offset.x, rect.top + offset.y, rect.width, rect.height };
}

sf::Vector2f Enemy::checkEnemyCollision(const sf::FloatRect& oldBounds, const sf::Vector2f& movement)
{
	if (!isAlive || isDying)
	{
		return movement;
	}
	sf::Vector2f newMovement = movement;
	sf::FloatRect newBounds = moveRect(oldBounds, newMovement);
	sf::FloatRect enemyBound = bounds.getGlobalBounds();
	if (newBounds.intersects(enemyBound))
	{
		const sf::Vector2f enemyPosition = { enemyBound.left, enemyBound.top };
		const sf::Vector2f targetPosition = { oldBounds.left, oldBounds.top };
		const auto delta = enemyPosition - targetPosition;

		const bool topCollision = delta.y < 0
								  && std::abs(delta.y) >= std::abs(delta.x);

		const bool bottomCollision = delta.y > 0
									 && std::abs(delta.y) >= std::abs(delta.x);

		const bool leftCollision = delta.x < 0
								   && std::abs(delta.y) <= std::abs(delta.x);

		const bool rightCollision = delta.x > 0
									&& std::abs(delta.y) <= std::abs(delta.x);

		if (topCollision)
		{
			newMovement.y = enemyBound.top + enemyBound.height - oldBounds.top;
		}
		else if (bottomCollision)
		{
			newMovement.y = enemyBound.top - oldBounds.height - oldBounds.top;
		}
		else if (leftCollision)
		{
			newMovement.x = enemyBound.left + enemyBound.width - oldBounds.left;
		}
		else if (rightCollision)
		{
			newMovement.x = enemyBound.left - oldBounds.width - oldBounds.left;
		}
	}
	return newMovement;
}

void Enemy::die()
{
	deathTimer = 0;
	moveTimer = 0;
	isDying = true;
	bounds.setSize(sf::Vector2f(64, 64));
	bounds.move(sf::Vector2f(0, -39));
}

void Enemy::dying(float elapsedTime)
{
	deathAnimationTimer += elapsedTime;
	const int maxImages = 6;
	const float frameDuration = 0.1f;
	curTexturePixelX = (int(deathAnimationTimer / frameDuration) % maxImages) * ENEMY_WIDTH;
	curTexturePixelY = (int)ENEMY_HEIGHT * 2;
	bounds.setTextureRect(sf::IntRect(curTexturePixelX, curTexturePixelY, ENEMY_WIDTH, ENEMY_WIDTH));
	if (deathAnimationTimer >= DEATH_ANIMATION_TIME)
	{
		isAlive = false;
		isDying = false;
		deathAnimationTimer = 0;
		bounds.setSize(sf::Vector2f(ENEMY_WIDTH, ENEMY_HEIGHT));
	}
}
