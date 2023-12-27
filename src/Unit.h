#ifndef _UNIT_H_
#define _UNIT_H_

#include <SFML/Graphics.hpp>

enum struct UnitType
{
	FULL_FILLED,
	LEFT_FILLED,
	BOTTOM_FREE,
	LEFT_FREE,
	LEFT_FREE_GRASS,
	LEFT_FILLED_GRASS,
	FULL_FREE,
	GRASS,
	GRASS_LEFT_FREE,
	RIGHT_CORNER_FREE,
	LEFT_GRASS,
	LAMP_OFF,
	LAMP_ON,
	TOP_PILLAR,
	DOWN_PILLAR,
	MAIN_PILLAR,
	RIGHT_POINTER,
	UP_STAIRS,
	MAIN_STAIRS,
	DOWN_STAIRS,
	MUSHROOM,
	MUSHROOMS,
	PICKAXE,
	FLOWER,
	FLOWERS,
	VINE,
	LEFT_CORNER_FREE,
};

class Unit : public sf::Drawable
{
 public:
	Unit(UnitType type, sf::Vector2f position, sf::Vector2f size);
	UnitType getType();
	sf::RectangleShape& getBounds();
 private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	UnitType unitType;
	sf::RectangleShape bounds;
	sf::Texture texture;
	sf::Image image;
};

#endif //_UNIT_H_
