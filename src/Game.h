#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "Field.h"
#include "Player.h"
#include "Enemy.h"
#include "Key.h"
#include "GameHud.h"
#include "ExitDoor.h"
#include "SFML/Audio/Music.hpp"

class Game
{
 public:
	ExitDoor exitDoor;
	Enemy worm;
	Camera camera;
	GameHud gameHud;
	explicit Game(sf::RenderWindow& window);
	void createWindow();
	void update(sf::Clock& clock);
	void render();
	void handleEvents();
	void winning(float elapsedTime);
	void win();
	sf::RectangleShape winScreenBounds;
	sf::Texture winScreenTexture;
	sf::Image winScreenImage;
	sf::Texture texture;
	Field field;
	Player player;
	Key bronzeKey;
	Key silverKey;
	Key goldKey;
	bool isWining = false;
	bool isWin = false;
	sf::RectangleShape leftCurtain;
	sf::RectangleShape rightCurtain;
 private:
	sf::RenderWindow& window;
	sf::Music music;
};

#endif //_GAME_H_
