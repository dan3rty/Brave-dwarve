#include "Field.h"
#include <vector>
#include <memory>
#include <iostream>
#include "Unit.h"
#include "Player.h"

const float BLOCK_SIZE = 64.0f;
const size_t FIELD_WIDTH = 20;
Field::Field()
{
	std::vector<std::vector<int>> map = {
		{ 4 }, { 10 }, { 3 }, { 3 }, { 3 }, { 3 }, { 3 }, { 1 }, { 10 }, { 3 }, { 3 }, { 3 }, { 3 }, { 3 }, { 3 },
		{ 3 }, { 3 }, { 3 }, { 3 }, { 1 },
		{ 4 }, { 2 }, { 7 }, { 7 }, { 7 }, { 12 }, { 7, 25 }, { 4 }, { 2 }, { 7 }, { 12 }, { 14 }, { 7 }, { 7 }, { 7 },
		{ 14 }, { 7 }, { 12 }, { 7, 25 }, { 4 },
		{ 4 }, { 6 }, { 8, 17 }, { 8, 21 }, { 8 }, { 11 }, { 7 }, { 4 }, { 6, 24 }, { 8 }, { 8, 22 }, { 8, 15 },
		{ 8, 21 }, { 8, 24 }, { 8, 23 }, { 8, 15 }, { 11 }, { 7 }, { 7 }, { 4 },
		{ 4 }, { 10 }, { 3 }, { 3 }, { 3, 19 }, { 2 }, { 7 }, { 4 }, { 10 }, { 3 }, { 3 }, { 3 }, { 3, 19 }, { 3 },
		{ 3 }, { 1 }, { 2 }, { 7 }, { 7 }, { 4 },
		{ 4 }, { 2 }, { 7, 25 }, { 7 }, { 7, 19 }, { 7 }, { 7 }, { 4 }, { 2 }, { 7 }, { 7 }, { 7 }, { 7, 19 }, { 7 },
		{ 7 }, { 4 }, { 2 }, { 7 }, { 7 }, { 4 },
		{ 4 }, { 2 }, { 12 }, { 7 }, { 7, 19 }, { 7 }, { 7 }, { 27 }, { 2 }, { 7 }, { 9, 22 }, { 8, 21 }, { 8, 20 },
		{ 8, 24 }, { 8, 22 }, { 4 }, { 6 }, { 8 }, { 8 }, { 4 },
		{ 4 }, { 6 }, { 11 }, { 7 }, { 9, 20 }, { 11 }, { 7 }, { 12 }, { 7 }, { 7 }, { 27 }, { 3 }, { 3 }, { 3, 19 },
		{ 3 }, { 3 }, { 3, 19 }, { 3 }, { 3 }, { 1 },
		{ 4 }, { 1 }, { 6 }, { 7, 23 }, { 4 }, { 6 }, { 11 }, { 7 }, { 7 }, { 7 }, { 7 }, { 7 }, { 7 }, { 7, 19 },
		{ 7 }, { 7 }, { 7, 19 }, { 7 }, { 7 }, { 4 },
		{ 4 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 6 }, { 8 }, { 8 }, { 8 }, { 8 }, { 8 }, { 8 }, { 8, 20 }, { 8 },
		{ 8 }, { 8, 20 }, { 8 }, { 8 }, { 4 },
		{ 4 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 },
		{ 1 }, { 1 }, { 1 }, { 1 },
		{ 4 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 },
		{ 1 }, { 1 }, { 1 }, { 1 },
		{ 4 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 }, { 1 },
		{ 1 }, { 1 }, { 1 }, { 1 },
	};

//		{ 1 }, { 7 }, { 7 }, { 7 }, { 7 }, { 1 }, { 7 }, { 1 }, { 7 }, { 7 }, { 7 }, { 7 }, { 1 }, { 7 }, { 7 }, { 7 }, { 1 }, { 7 }, { 7 },
//		{ 7 }, { 1 }, { 7 }, { 7 }, { 1 }, { 7 }, { 7 }, { 7 }, { 1 }, { 7 }, { 7 }, { 1 }, { 7 }, { 7 }, { 1 }, { 7 }, { 7 }, { 7 }, { 1 },
//		{ 7 }, { 7 }, { 1 }, { 1 }, { 7 }, { 7 }, { 7 }, { 7 }, { 7 }, { 1 }, { 1 }, { 7 }, { 7 }, { 7 }, { 1 }, { 7 }, { 7 }, { 1 }, { 1 },
//		{ 7 }, { 7 }, { 1 }, { 1 }, { 7 }, { 7 }, { 7 }, { 7 }, { 7 }, { 1 }, { 7 }, { 7 }, { 7 }, { 7 }, { 1 }, { 7 }, { 1 }, { 7 }, { 1 },
//		{ 7 }, { 1 }, { 7 }, { 7 }, { 1 }, { 7 }, { 7 }, { 7 }, { 1 }, { 7 }, { 7 }, { 7 }, { 7 }, { 7 }, { 1 }, { 1 }, { 7 }, { 7 }, { 1 },
//		{ 1 }, { 7 }, { 7 }, { 7 }, { 7 }, { 1 }, { 7 }, { 1 }, { 7 }, { 7 }, { 7 }, { 7 }, { 7 }, { 7 }, { 1 }, { 7 }, { 7 }, { 7 }, { 1 },
//	};
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			const size_t offset = x + y * width;
			for (size_t z = 0; z <= map[offset].size(); z++)
			{
				sf::Vector2f position = {
					(float)x * BLOCK_SIZE + 320,
					(float)y * BLOCK_SIZE + 180
				};
				UnitType type;
				switch (map[offset][z])
				{
				case 1:
					type = UnitType::FULL_FILLED;
					break;
				case 2:
					type = UnitType::LEFT_FILLED;
					break;
				case 3:
					type = UnitType::BOTTOM_FREE;
					break;
				case 4:
					type = UnitType::LEFT_FREE;
					break;
				case 5:
					type = UnitType::LEFT_FREE_GRASS;
					break;
				case 6:
					type = UnitType::LEFT_FILLED_GRASS;
					break;
				case 7:
					type = UnitType::FULL_FREE;
					break;
				case 8:
					type = UnitType::GRASS;
					break;
				case 9:
					type = UnitType::GRASS_LEFT_FREE;
					break;
				case 10:
					type = UnitType::RIGHT_CORNER_FREE;
					break;
				case 11:
					type = UnitType::LEFT_GRASS;
					break;
				case 12:
					type = UnitType::LAMP_OFF;
					break;
				case 13:
					type = UnitType::LAMP_ON;
					break;
				case 14:
					type = UnitType::TOP_PILLAR;
					break;
				case 15:
					type = UnitType::DOWN_PILLAR;
					break;
				case 16:
					type = UnitType::MAIN_PILLAR;
					break;
				case 17:
					type = UnitType::RIGHT_POINTER;
					break;
				case 18:
					type = UnitType::UP_STAIRS;
					break;
				case 19:
					type = UnitType::MAIN_STAIRS;
					break;
				case 20:
					type = UnitType::DOWN_STAIRS;
					break;
				case 21:
					type = UnitType::MUSHROOM;
					break;
				case 22:
					type = UnitType::MUSHROOMS;
					break;
				case 23:
					type = UnitType::PICKAXE;
					break;
				case 24:
					type = UnitType::FLOWER;
					break;
				case 25:
					type = UnitType::FLOWERS;
					break;
				case 26:
					type = UnitType::VINE;
					break;
				case 27:
					type = UnitType::LEFT_CORNER_FREE;
					break;
				}
				const sf::Vector2f size = { BLOCK_SIZE, BLOCK_SIZE };
				std::shared_ptr<Unit> unit = std::make_shared<Unit>(
					type,
					position,
					size
				);
				units.push_back(unit);
			}
		}
	}
}

void Field::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& unit : units)
	{
		target.draw(*unit, states);
	}
}

static sf::FloatRect moveRect(const sf::FloatRect& rect, sf::Vector2f& offset)
{
	return { rect.left + offset.x, rect.top + offset.y, rect.width, rect.height };
}

static bool isBetween(float value, float minValue, float maxValue)
{
	return (value >= minValue) && (value <= maxValue);
}

static Direction selectShiftDirection(float leftShift, float rightShift,
	float topShift, float bottomShift,
	float minShift, float maxShift)
{
	Direction result = Direction::NONE;
	float bestShift = FIELD_WIDTH * BLOCK_SIZE;
	if (isBetween(leftShift, minShift, maxShift) && (leftShift < bestShift))
	{
		result = Direction::LEFT;
		bestShift = leftShift;
	}
	if (isBetween(rightShift, minShift, maxShift) && (rightShift < bestShift))
	{
		result = Direction::RIGHT;
		bestShift = rightShift;
	}
	if (isBetween(topShift, minShift, maxShift) && (topShift < bestShift))
	{
		result = Direction::UP;
		bestShift = topShift;
	}
	if (isBetween(bottomShift, minShift, maxShift) && bottomShift < bestShift)
	{
		result = Direction::DOWN;
		bestShift = bottomShift;
	}

	return result;
}

static float getBottom(const sf::FloatRect& rect)
{
	return rect.top + rect.height;
}

static float getRight(const sf::FloatRect& rect)
{
	return rect.left + rect.width;
}

sf::Vector2f
Field::checkFieldFloorCollision(const sf::FloatRect& oldBounds, const sf::Vector2f& movement, bool isStairs)
{
	sf::Vector2f newMovement = movement;
	if (newMovement == sf::Vector2f{ 0, 0 } || isStairs)
	{
		return newMovement;
	}

	sf::FloatRect newBounds = moveRect(oldBounds, newMovement);
	for (const auto& unit : units)
	{
		if (unit->getType() != UnitType::FULL_FILLED && unit->getType() != UnitType::LEFT_FREE
			&& unit->getType() != UnitType::BOTTOM_FREE && unit->getType() != UnitType::RIGHT_CORNER_FREE
			&& unit->getType() != UnitType::LEFT_CORNER_FREE)
		{
			continue;
		}

		sf::FloatRect unitBound = unit->getBounds().getGlobalBounds();
		if (newBounds.intersects(unitBound))
		{
			const sf::Vector2f unitPosition = { unitBound.left, unitBound.top };
			const sf::Vector2f playerPosition = { oldBounds.left, oldBounds.top };
			const auto delta = unitPosition - playerPosition;

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
				newMovement.y = unitBound.top + unitBound.height - oldBounds.top;
			}
			else if (bottomCollision)
			{
				newMovement.y = unitBound.top - oldBounds.height - oldBounds.top;
			}
			else if (leftCollision)
			{
				newMovement.x = unitBound.left + unitBound.width - oldBounds.left;
			}
			else if (rightCollision)
			{
				newMovement.x = unitBound.left - oldBounds.width - oldBounds.left;
			}

			newBounds = moveRect(oldBounds, newMovement);
		}
	}
	return newMovement;
}

bool Field::checkUpStairsCollision(sf::FloatRect oldBounds, const sf::Vector2f& movement)
{
	sf::Vector2f newMovement = movement;
	sf::FloatRect newBounds = moveRect(oldBounds, newMovement);
	for (const auto& unit : units)
	{
		sf::FloatRect unitBound = unit->getBounds().getGlobalBounds();
		if ((unit->getType() == UnitType::MAIN_STAIRS
			 || unit->getType() == UnitType::DOWN_STAIRS) && newBounds.intersects(unitBound))
		{
			return true;
		}
	}
	return false;
}

bool Field::checkDownStairsCollision(const sf::FloatRect& oldBounds, const sf::Vector2f& movement)
{
	sf::Vector2f newMovement = movement;
	newMovement.y += 40;
	sf::FloatRect newBounds = moveRect(oldBounds, newMovement);
	for (const auto& unit : units)
	{
		sf::FloatRect unitBound = unit->getBounds().getGlobalBounds();
		if ((unit->getType() == UnitType::MAIN_STAIRS) && unitBound.intersects(newBounds))
		{
			return true;
		}
	}
	return false;
}

sf::Vector2f Field::correctStairsMovement(const sf::FloatRect& oldBounds, const sf::Vector2f& movement)
{
	sf::Vector2f newMovement = movement;
	if (newMovement == sf::Vector2f{ 0, 0 })
	{
		return newMovement;
	}

	sf::FloatRect newBounds = moveRect(oldBounds, newMovement);
	for (const auto& unit : units)
	{
		sf::FloatRect unitBound = unit->getBounds().getGlobalBounds();
		if (newBounds.intersects(unitBound) && unit->getType() == UnitType::MAIN_STAIRS)
		{
			const sf::Vector2f unitPosition = { unitBound.left, unitBound.top };
			const sf::Vector2f playerPosition = { oldBounds.left, oldBounds.top };
			const auto delta = unitPosition - playerPosition;
			const bool topCollision = delta.y < 0
									  && std::abs(delta.y) >= std::abs(delta.x);

			const bool bottomCollision = delta.y > 0
										 && std::abs(delta.y) >= std::abs(delta.x);

			const bool leftCollision = delta.x < 0
									   && std::abs(delta.y) <= std::abs(delta.x);

			const bool rightCollision = delta.x > 0
										&& std::abs(delta.y) <= std::abs(delta.x);

			if (leftCollision || rightCollision || topCollision || bottomCollision)
			{
				newMovement.x = unitBound.left - 3 - oldBounds.left;
				return newMovement;
			}
		}
	}
	return newMovement;
}

