#include "Precompiled.h"

Arrow::Arrow(Ball * ball, float sizeX, float sizeY)
{
	m_ball = ball;
	this->m_size = sf::Vector2f(sizeX, sizeY);
	this->setPosition(ball->getPosition().x + ball->getRadius(), ball->getPosition().y);
	this->setSize(m_size);
	this->setOrigin(0.f, m_size.y / 2);

}


Arrow::~Arrow()
{
}

void Arrow::update(sf::Vector2i * localPosition)
{
	this->setPosition(m_ball->getPosition().x, m_ball->getPosition().y);
	sf::Vector2f localPositionF(localPosition->x, localPosition->y);
	m_dirVec =  localPositionF - this->getPosition();
	float angle = (180/PI)*atanf(m_dirVec.y / m_dirVec.x);
	//cout << angle << endl;
	this->setRotation(angle);
	//cout << dirVec.x << " " << dirVec.y << endl;

}

sf::Vector2f Arrow::getForce()
{
	sf::Vector2f force(m_dirVec.x * 10000, m_dirVec.y * 10000); // *10000000
	cout << force.x << "," << force.y << endl;
	return force;
}

