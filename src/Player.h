#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics.hpp>
#include "Field.h"
#include "Fireball.h"

const float PLAYER_HEIGHT = 93.0f;
const float PLAYER_WIDTH = 80.0f;
enum struct Direction
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	JUMP,
	LEFT_JUMP,
	RIGHT_JUMP,
	FALL
};

class Player : public sf::Drawable
{
 public:
	sf::RectangleShape bounds;
	Direction direction;
	sf::Texture texture;
	sf::Image image;
	float moveTimer = 0;
	Fireball fireball;
	Player();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updatePlayer(float elapsedTime, Field& field, Enemy& enemy);
	void updatePlayerDirection();
	sf::Vector2f getMovement(float elapsedTime, Field& field, Enemy& enemy);
	void checkAbilities();
	float getCoordinateX();
	float getCoordinateY();
	int hp = 3;
	bool isFalling = false;
};

#endif //_PLAYER_H_
