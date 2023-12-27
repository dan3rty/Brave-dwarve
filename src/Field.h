#ifndef _FIELD_H_
#define _FIELD_H_

#include <SFML/Graphics.hpp>
#include <memory>
#include "Unit.h"

const UnitType WALLS[] = { UnitType::LEFT_FILLED_GRASS, UnitType::LEFT_FILLED, UnitType::LEFT_FREE,
						   UnitType::LEFT_FREE_GRASS, UnitType::LEFT_CORNER_FREE, UnitType::RIGHT_CORNER_FREE };

const UnitType FLOORS[] = { UnitType::FULL_FILLED, UnitType::LEFT_CORNER_FREE, UnitType::RIGHT_CORNER_FREE };

class Field : public sf::Drawable
{
 public:
	Field();
	size_t width = 20;
	size_t height = 12;
	std::vector<std::shared_ptr<Unit>> units;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Vector2f checkFieldFloorCollision(const sf::FloatRect& oldBounds, const sf::Vector2f& movement, bool isStairs);
	bool checkUpStairsCollision(sf::FloatRect oldBounds, const sf::Vector2f& movement);
	bool checkDownStairsCollision(const sf::FloatRect& oldBounds, const sf::Vector2f& movement);
	sf::Vector2f correctStairsMovement(const sf::FloatRect& oldBounds, const sf::Vector2f& movement);
};

#endif //_FIELD_H_
