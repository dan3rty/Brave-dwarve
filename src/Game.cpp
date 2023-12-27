#include <iostream>
#include "Game.h"
#include "Fireball.h"
constexpr unsigned ANTIALIASING_LEVEL = 8;
constexpr unsigned MAX_FPS = 60;
const float CURTAINS_SPEED = 300;

Game::Game(sf::RenderWindow& window) : window(window), worm({ 1240, 750 }), bronzeKey({ 430, 600 }, KEY_TYPE::BRONZE),
									   silverKey({ 1000, 530 }, KEY_TYPE::SILVER), goldKey({ 900, 340 }, KEY_TYPE::GOLD)
{
	leftCurtain.setFillColor(sf::Color::Black);
	leftCurtain.setSize({800, 800});
	leftCurtain.setPosition({-160, 180});
	rightCurtain.setFillColor(sf::Color::Black);
	rightCurtain.setSize({270, 800});
	rightCurtain.setPosition({2080, 180});
	winScreenImage.loadFromFile("../res/end.jpg");
	winScreenTexture.loadFromImage(winScreenImage);
	winScreenBounds.setTexture(&winScreenTexture);
	winScreenBounds.setPosition(640, 260);
	winScreenBounds.setSize({960, 540});
	music.openFromFile("../res/first_level.wav");
	music.play();
}

void Game::winning(float elapsedTime)
{
	sf::Vector2f movement = {CURTAINS_SPEED * elapsedTime, 0};
	leftCurtain.move(movement);
	movement.x *= -1;
	rightCurtain.move(movement);
	if (rightCurtain.getPosition().x < 590)
	{
		isWin = true;
	}
}

void Game::createWindow()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = ANTIALIASING_LEVEL;
	window.create(
		sf::VideoMode::getDesktopMode(),
		"Brave Dwarves", sf::Style::Fullscreen, settings);
	window.setFramerateLimit(MAX_FPS);
}

void Game::update(sf::Clock& clock)
{
	const float elapsedSeconds = clock.restart().asSeconds();
	if (isWining)
	{
		winning(elapsedSeconds);
	}
	else
	{
		player.updatePlayer(elapsedSeconds, field, worm);
		player.fireball.updateFireball(elapsedSeconds, field, worm);
		camera.setViewPosition(player.getCoordinateX(), player.getCoordinateY());
		worm.updateEnemy(elapsedSeconds, field);
		bronzeKey.update(player.bounds.getGlobalBounds(), elapsedSeconds);
		silverKey.update(player.bounds.getGlobalBounds(), elapsedSeconds);
		goldKey.update(player.bounds.getGlobalBounds(), elapsedSeconds);
		isWining = exitDoor.update(player.bounds.getGlobalBounds(),
			bronzeKey.isFounded && silverKey.isFounded && goldKey.isFounded, elapsedSeconds);
		gameHud.update(camera.view.getCenter(), bronzeKey.isFounded, silverKey.isFounded, goldKey.isFounded);
	}
}

void Game::render()
{
	if (!isWining && !isWin)
	{
		window.setView(camera.view);
		window.clear();
		window.draw(field);
		window.draw(exitDoor);
		window.draw(player);
		window.draw(player.fireball);
		window.draw(worm);
		window.draw(bronzeKey);
		window.draw(silverKey);
		window.draw(goldKey);
		window.draw(gameHud);
	}
	if (isWining && !isWin)
	{
		window.draw(leftCurtain);
		window.draw(rightCurtain);
	}
	if (isWin)
	{
		window.draw(winScreenBounds);
	}
	window.display();
}

void Game::handleEvents()
{
	sf::Event event{};
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

