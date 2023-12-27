#ifndef _KEY_H_
#define _KEY_H_

#include <SFML/Graphics.hpp>

const float KEY_SIZE = 32;

enum struct KEY_TYPE
{
	BRONZE,
	SILVER,
	GOLD
};

class Key : public sf::Drawable
{
 public:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(const sf::FloatRect &playerPosition, float elapsedTime);
	Key(const sf::Vector2f& initialPosition, KEY_TYPE keyType);
	KEY_TYPE type;
	sf::RectangleShape bounds;
	sf::Texture texture;
	sf::Image image;
	float animationTimer = 0;
	int xTexture;
	bool isFounded = false;
};

#endif //_KEY_H_
