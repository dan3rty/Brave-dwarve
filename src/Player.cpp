#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Field.h"

static const sf::Vector2f PLAYER_INITIAL_POSITION = { 500.0f, 340.0f };
const float GRAVITY = 140.0f;
constexpr float PLAYER_SPEED = 140.f;
const float JUMP_COEFFICIENT = 2.5;

Player::Player()
{
	direction = Direction::NONE;
	image.loadFromFile("../res/gnome_animation.png");
	image.createMaskFromColor(sf::Color(224, 32, 64));
	texture.loadFromImage(image);
	bounds.setPosition(PLAYER_INITIAL_POSITION);
	bounds.setSize(sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));
	bounds.setTexture(&texture);
	bounds.setTextureRect(sf::IntRect(0, 0, (int)PLAYER_WIDTH, (int)PLAYER_HEIGHT));
	bounds.setOrigin(PLAYER_WIDTH / 2, PLAYER_HEIGHT / 2);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(bounds, states);
}

sf::Vector2f Player::getMovement(float elapsedTime, Field& field, Enemy& enemy)
{
	const sf::Vector2f step(PLAYER_SPEED * elapsedTime, GRAVITY * elapsedTime);
	sf::Vector2f movement(0.f, 0.f);
	bool stairsUpCollision = field.checkUpStairsCollision(bounds.getGlobalBounds(), movement);
	bool stairsDownCollision = field.checkDownStairsCollision(bounds.getGlobalBounds(), movement);
	if (!stairsUpCollision)
	{
		movement.y += step.y;
	}
	switch (direction)
	{
	case Direction::LEFT:
		movement.x -= step.x;
		if (bounds.getScale() == sf::Vector2f(1, 1) && direction != Direction::UP && direction != Direction::DOWN)
		{
			bounds.setScale(-1, 1);
		}
		break;
	case Direction::RIGHT:
		movement.x += step.x;
		if (bounds.getScale() == sf::Vector2f(-1, 1) && direction != Direction::UP && direction != Direction::DOWN)
		{
			bounds.setScale(1, 1);
		}
		break;
	case Direction::JUMP:
		movement.y -= JUMP_COEFFICIENT * step.y; //TODO: скорость прыжка изменить
		break;
	case Direction::UP:
		if (stairsUpCollision)
		{
			movement.y -= step.x + step.y; //TODO: скорость подъёма и спуска с лестниц изменить
			movement = field.correctStairsMovement(bounds.getGlobalBounds(), movement);
		}
		break;
	case Direction::DOWN:
		if (stairsDownCollision)
		{
			movement.y += 2 * step.x;
			movement = field.correctStairsMovement(bounds.getGlobalBounds(), movement);
		}
		break;
	case Direction::LEFT_JUMP:
		movement.y -= JUMP_COEFFICIENT * step.y;
		movement.x -= step.x;
		if (bounds.getScale() == sf::Vector2f(1, 1) && direction != Direction::UP && direction != Direction::DOWN)
		{
			bounds.setScale(-1, 1);
		}
		break;
	case Direction::RIGHT_JUMP:
		movement.x += step.x;
		if (bounds.getScale() == sf::Vector2f(-1, 1) && direction != Direction::UP && direction != Direction::DOWN)
		{
			bounds.setScale(1, 1);
		}
		movement.y -= JUMP_COEFFICIENT * step.y;
		break;
	default:
		break;
	}

	bool isStairsMovement = (direction == Direction::DOWN || direction == Direction::UP) &&
							(stairsUpCollision || stairsDownCollision);
	movement = field.checkFieldFloorCollision(bounds.getGlobalBounds(), movement, isStairsMovement);
	movement = enemy.checkEnemyCollision(bounds.getGlobalBounds(), movement);
	isFalling = movement.y == step.y;
	return movement;
}

void Player::updatePlayer(float elapsedTime, Field& field, Enemy& enemy)
{
	checkAbilities();
	updatePlayerDirection();
	auto movement = getMovement(elapsedTime, field, enemy);
	int curPixelX = 0, curPixelY = 0;
	moveTimer += elapsedTime;
	bool stairsUpCollision = field.checkUpStairsCollision(bounds.getGlobalBounds(), movement);
	bool stairsDownCollision = field.checkDownStairsCollision(bounds.getGlobalBounds(), movement);
	bool isStairsMovement = stairsUpCollision || stairsDownCollision;
	sf::Vector2f wallsCollision = field.checkFieldFloorCollision(bounds.getGlobalBounds(), movement, isStairsMovement);
	if (isFalling)
	{
		const int maxImages = 2;
		const float frameDuration = 0.07f;
		curPixelX = (int(moveTimer / frameDuration) % maxImages) * (int)PLAYER_WIDTH;
		curPixelY = (int)PLAYER_HEIGHT;
	}
	else if (wallsCollision.y < 0 && (direction == Direction::JUMP || direction == Direction::LEFT_JUMP
									  || direction == Direction::RIGHT_JUMP))
	{
		curPixelX = 0;
		curPixelY = 3 * (int)PLAYER_HEIGHT;
	}
	else if (stairsDownCollision && direction == Direction::DOWN)
	{
		const int maxImages = 3;
		const float frameDuration = 0.2f;
		curPixelX = (int)PLAYER_WIDTH * maxImages - ((int(moveTimer / frameDuration) % maxImages) * (int)PLAYER_WIDTH);
		curPixelY = 2 * (int)PLAYER_HEIGHT;
	}
	else if (stairsUpCollision && direction == Direction::UP)
	{
		const int maxImages = 3;
		const float frameDuration = 0.2f;
		curPixelX = (int(moveTimer / frameDuration) % maxImages) * (int)PLAYER_WIDTH;
		curPixelY = 2 * (int)PLAYER_HEIGHT;
	}
	else if (stairsDownCollision && stairsUpCollision && direction != Direction::RIGHT && direction != Direction::LEFT)
	{
		curPixelX = 0;
		curPixelY = 2 * (int)PLAYER_HEIGHT;
	}
	else if (direction == Direction::LEFT || direction == Direction::RIGHT)
	{
		const int maxImages = 16;
		const float frameDuration = 0.05f;
		curPixelX = (int(moveTimer / frameDuration) % maxImages) * (int)PLAYER_WIDTH;
		curPixelY = 0;
		if (moveTimer > maxImages * frameDuration || direction == Direction::NONE)
		{
			moveTimer = 0;
		}
	}
	bounds.setTextureRect(sf::IntRect(curPixelX, curPixelY, (int)PLAYER_WIDTH, (int)PLAYER_HEIGHT));
	bounds.move(movement);
}

void Player::checkAbilities()
{
	if (fireball.isActive)
	{
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		bool isRight = bounds.getScale() == sf::Vector2f(1, 1);
		fireball.activateFireball(isRight, bounds.getPosition());
	}
}

void Player::updatePlayerDirection()
{
	direction = Direction::NONE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		direction = Direction::UP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		direction = Direction::DOWN;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		direction = Direction::LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		direction = Direction::RIGHT;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
	{
		direction = Direction::LEFT_JUMP;
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
	{
		direction = Direction::RIGHT_JUMP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		direction = Direction::JUMP;
	}
}

float Player::getCoordinateX()
{
	return bounds.getPosition().x;
}
float Player::getCoordinateY()
{
	return bounds.getPosition().y;
}