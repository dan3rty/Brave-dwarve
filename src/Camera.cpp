#include <iostream>
#include "Camera.h"

Camera::Camera()
{
	view.reset(sf::FloatRect(0, 0, 960, 540));
}

void Camera::setViewPosition(float x, float y)
{

	view.setCenter(correctViewPosition(x, y));
}

sf::Vector2f Camera::correctViewPosition(float x, float y)
{
	//TODO: волшебные цифры поправить (в константы вынести и придумать как их посчитать вообще)
	if (x < 798)
	{
		x = 798;
	}
	if (y < 450)
	{
		y = 450;
	}
	if (y > 671)
	{
		y = 671;
	}
	if (x > 1121)
	{
		x = 1121;
	}
	return {x, y};
}