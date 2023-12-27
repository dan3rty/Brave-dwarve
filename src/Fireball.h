#ifndef _FIREBALL_H_
#define _FIREBALL_H_

#include <SFML/Graphics.hpp>
#include "Field.h"
#include "Enemy.h"
const float FIREBALL_WIDTH = 40.0f;
const float FIREBALL_HEIGHT = 40.0f;
const float FIREBALL_SPEED = 400.0f;
//TODO: все скорости в относительные перевести

class Fireball : public sf::Drawable
{
 public:
	sf::RectangleShape bounds;
	sf::Texture texture;
	sf::Image image;
	float moveTimer = 0;
	bool isActive = false;
	bool isRightDirection{};
	Fireball();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateFireball(float elapsedTime, Field& field, Enemy& enemy);
	void activateFireball(bool isRight, sf::Vector2f playerPosition);
};

#endif //_FIREBALL_H_
