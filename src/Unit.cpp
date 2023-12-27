#include <iostream>
#include "Unit.h"

Unit::Unit(UnitType type, sf::Vector2f position, sf::Vector2f size)
{
	switch (type)
	{
	case UnitType::FULL_FILLED:
		image.loadFromFile("../res/filled_block.png");
		break;
	case UnitType::LEFT_FILLED:
		image.loadFromFile("../res/filled_left.png");
		break;
	case UnitType::BOTTOM_FREE:
		image.loadFromFile("../res/free_down.png");
		break;
	case UnitType::LEFT_FREE:
		image.loadFromFile("../res/free_left.png");
		break;
	case UnitType::LEFT_FREE_GRASS:
		image.loadFromFile("../res/free_left_grass.png");
		break;
	case UnitType::LEFT_FILLED_GRASS:
		image.loadFromFile("../res/grass_with_wall.png");
		break;
	case UnitType::FULL_FREE:
		image.loadFromFile("../res/free_space.png");
		break;
	case UnitType::GRASS:
		image.loadFromFile("../res/grass.png");
		break;
	case UnitType::GRASS_LEFT_FREE:
		image.loadFromFile("../res/grass_left_free.png");
		break;
	case UnitType::RIGHT_CORNER_FREE:
		image.loadFromFile("../res/free_space_right_corner.png");
		break;
	case UnitType::LEFT_GRASS:
		image.loadFromFile("../res/grass_right_free.png");
		break;
	case UnitType::LAMP_OFF:
		image.loadFromFile("../res/lamp_off.png");
		break;
	case UnitType::LAMP_ON:
		image.loadFromFile("../res/lamp_on.png");
		break;
	case UnitType::TOP_PILLAR:
		image.loadFromFile("../res/pillar.png");
		break;
	case UnitType::DOWN_PILLAR:
		image.loadFromFile("../res/pillar_down.png");
		break;
	case UnitType::MAIN_PILLAR:
		image.loadFromFile("../res/pillar_main.png");
		break;
	case UnitType::RIGHT_POINTER:
		image.loadFromFile("../res/pointer_right.png");
		break;
	case UnitType::UP_STAIRS:
		image.loadFromFile("../res/stairs_up.png");
		break;
	case UnitType::MAIN_STAIRS:
		image.loadFromFile("../res/stairs_main.png");
		break;
	case UnitType::DOWN_STAIRS:
		image.loadFromFile("../res/stairs_down.png");
		break;
	case UnitType::MUSHROOM:
		image.loadFromFile("../res/mushroom.png");
		break;
	case UnitType::MUSHROOMS:
		image.loadFromFile("../res/mushrooms.png");
		break;
	case UnitType::PICKAXE:
		image.loadFromFile("../res/pickaxe.png");
		break;
	case UnitType::FLOWER:
		image.loadFromFile("../res/flower.png");
		break;
	case UnitType::FLOWERS:
		image.loadFromFile("../res/flowers.png");
		break;
	case UnitType::VINE:
		image.loadFromFile("../res/loza.png");
		break;
	case UnitType::LEFT_CORNER_FREE:
		image.loadFromFile("../res/free_corner.png");
		break;
	}
	unitType = type;
	bounds.setPosition(position);
	bounds.setSize(size);
	image.createMaskFromColor(sf::Color(237, 28, 36));
	texture.loadFromImage(image);
	bounds.setTexture(&texture);
}

void Unit::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(bounds, states);
}

UnitType Unit::getType()
{
	return unitType;
}

sf::RectangleShape& Unit::getBounds()
{
	return bounds;
}