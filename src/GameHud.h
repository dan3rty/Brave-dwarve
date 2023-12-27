#ifndef _GAMEHUD_H_
#define _GAMEHUD_H_
#include <SFML/Graphics.hpp>

class GameHud : public sf::Drawable
{
 public:
	sf::Image emptyBronzeKeyImage;
	sf::Texture emptyBronzeKeyTexture;
	sf::Image emptySilverKeyImage;
	sf::Texture emptySilverKeyTexture;
	sf::Image emptyGoldKeyImage;
	sf::Texture emptyGoldKeyTexture;
	sf::Image filledBronzeKeyImage;
	sf::Texture filledBronzeKeyTexture;
	sf::Image filledSilverKeyImage;
	sf::Texture filledSilverKeyTexture;
	sf::Image filledGoldKeyImage;
	sf::Texture filledGoldKeyTexture;
	GameHud();
	sf::RectangleShape emptyBronzeKeyBounds;
	sf::RectangleShape emptySilverKeyBounds;
	sf::RectangleShape emptyGoldKeyBounds;
	sf::RectangleShape filledBronzeKeyBounds;
	sf::RectangleShape filledSilverKeyBounds;
	sf::RectangleShape filledGoldKeyBounds;
	bool isBronzeFilled = false;
	bool isSilverFilled = false;
	bool isGoldFilled = false;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Vector2f cameraPosition, bool isBronzeFounded, bool isSilverFounded, bool isGoldFounded);
};

#endif //_GAMEHUD_H_
