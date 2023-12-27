#include <iostream>
#include "GameHud.h"

GameHud::GameHud()
{
	emptyBronzeKeyImage.loadFromFile("../res/empty_bronze_key.png");
	emptyBronzeKeyImage.createMaskFromColor(sf::Color(224, 32, 64));
	emptyBronzeKeyTexture.loadFromImage(emptyBronzeKeyImage);
	emptyBronzeKeyBounds.setTexture(&emptyBronzeKeyTexture);
	emptyBronzeKeyBounds.setSize({37, 37});

	emptySilverKeyImage.loadFromFile("../res/empty_silver_key.png");
	emptySilverKeyImage.createMaskFromColor(sf::Color(224, 32, 64));
	emptySilverKeyTexture.loadFromImage(emptySilverKeyImage);
	emptySilverKeyBounds.setTexture(&emptySilverKeyTexture);
	emptySilverKeyBounds.setSize({37, 37});

	emptyGoldKeyImage.loadFromFile("../res/empty_gold_key.png");
	emptyGoldKeyImage.createMaskFromColor(sf::Color(224, 32, 64));
	emptyGoldKeyTexture.loadFromImage(emptyGoldKeyImage);
	emptyGoldKeyBounds.setTexture(&emptyGoldKeyTexture);
	emptyGoldKeyBounds.setSize({37, 37});

	filledBronzeKeyImage.loadFromFile("../res/filled_bronze_key.png");
	filledBronzeKeyImage.createMaskFromColor(sf::Color(224, 32, 64));
	filledBronzeKeyTexture.loadFromImage(filledBronzeKeyImage);
	filledBronzeKeyBounds.setTexture(&filledBronzeKeyTexture);
	filledBronzeKeyBounds.setSize({32, 32});

	filledSilverKeyImage.loadFromFile("../res/filled_silver_key.png");
	filledSilverKeyImage.createMaskFromColor(sf::Color(224, 32, 64));
	filledSilverKeyTexture.loadFromImage(filledSilverKeyImage);
	filledSilverKeyBounds.setTexture(&filledSilverKeyTexture);
	filledSilverKeyBounds.setSize({32, 32});

	filledGoldKeyImage.loadFromFile("../res/filled_gold_key.png");
	filledGoldKeyImage.createMaskFromColor(sf::Color(224, 32, 64));
	filledGoldKeyTexture.loadFromImage(filledGoldKeyImage);
	filledGoldKeyBounds.setTexture(&filledGoldKeyTexture);
	filledGoldKeyBounds.setSize({32, 32});

}

void GameHud::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(emptyBronzeKeyBounds, states);
	target.draw(emptySilverKeyBounds, states);
	target.draw(emptyGoldKeyBounds, states);
	if (isBronzeFilled)
	{
		target.draw(filledBronzeKeyBounds, states);
	}
	if (isSilverFilled)
	{
		target.draw(filledSilverKeyBounds, states);
	}
	if (isGoldFilled)
	{
		target.draw(filledGoldKeyBounds, states);
	}
}

void GameHud::update(sf::Vector2f cameraPosition, bool isBronzeFounded, bool isSilverFounded, bool isGoldFounded)
{
	emptyBronzeKeyBounds.setPosition(cameraPosition.x - 480, cameraPosition.y - 40);
	emptySilverKeyBounds.setPosition(cameraPosition.x - 480, cameraPosition.y - 20);
	emptyGoldKeyBounds.setPosition(cameraPosition.x - 480, cameraPosition.y);
	filledBronzeKeyBounds.setPosition(cameraPosition.x - 478, cameraPosition.y - 38);
	filledSilverKeyBounds.setPosition(cameraPosition.x - 478, cameraPosition.y - 18);
	filledGoldKeyBounds.setPosition(cameraPosition.x - 478, cameraPosition.y + 2);
	isBronzeFilled = isBronzeFounded;
	isSilverFilled = isSilverFounded;
	isGoldFilled = isGoldFounded;
}