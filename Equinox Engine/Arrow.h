#pragma once
#include "Ball.h"
class Arrow : public sf::RectangleShape
{
private:
	sf::Vector2f m_size;
	sf::Vector2f m_dirVec;
	Ball * m_ball;
public:
	Arrow(Ball *,float,float);
	~Arrow();
	void update(sf::Vector2i*);
	sf::Vector2f getForce();
};

