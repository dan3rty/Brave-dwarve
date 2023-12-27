#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <SFML/Graphics.hpp>
#include "Field.h"

//TODO: сделать состояния для врага: живой, умирает, воскрешается
class Enemy : public sf::Drawable
{
 public:
	sf::RectangleShape bounds;
	bool isRight;
	sf::Texture texture;
	sf::Image image;
	float moveTimer = 0;
	float deathTimer = 0;
	float reviveTimer = 0;
	float deathAnimationTimer = 0;
	int curTexturePixelY = 0;
	int curTexturePixelX = 0;
	bool isAlive = false;
	bool isDying = false;
	sf::Vector2f initialPosition;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateEnemy(float elapsedTime, Field& field);
	void updateEnemyDirection();
	sf::Vector2f getMovement(float elapsedTime, Field& field);
	void reviveEnemy(float elapsedTime);
	explicit Enemy(const sf::Vector2f& initialPosition);
	sf::Vector2f checkEnemyCollision(const sf::FloatRect& oldBounds, const sf::Vector2f& movement);
	void die();
	void dying(float elapsedTime);
};

#endif //_ENEMY_H_
