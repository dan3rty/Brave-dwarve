#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <SFML/Graphics.hpp>

class Camera
{
 public:
	Camera();
	void setViewPosition(float x, float y);
	static sf::Vector2f correctViewPosition(float x, float y);
	sf::View view;
	sf::Vector2f position;
};

#endif //_CAMERA_H_