#ifndef _EXITDOOR_H_
#define _EXITDOOR_H_
#include <SFML/Graphics.hpp>

class ExitDoor : public sf::Drawable
{
 public:
	float animationTimer = 0;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool update(const sf::FloatRect& playerPosition, bool isThreeKeys, float elapsedTime);
	void open(float elapsedTime);
	ExitDoor();
	sf::RectangleShape bounds;
	sf::Texture texture;
	sf::Image image;
	bool isOpened = false;
	bool isOpening = false;
};

#endif //_EXITDOOR_H_
