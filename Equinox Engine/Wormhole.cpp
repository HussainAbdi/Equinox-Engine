#include "Precompiled.h"




Wormhole::Wormhole(float radius, float positionX, float positionY)
{
	this->setRadius(radius);
	this->setPosition(positionX, positionY);
	this->setOrigin(radius, radius);
	float volume = PI*radius*radius;
	m_density = 10; // 1000000
	this->m_mass = volume * m_density;
	this->m_invmass = 1 / m_mass;
}


Wormhole::~Wormhole()
{
}

bool Wormhole::WithinPullingDistance(Ball *ball) {
	float calc;
	calc = powf(ball->getPosition().x - this->getPosition().x, 2) + powf(ball->getPosition().y - this->getPosition().y, 2);
	if (calc < powf(this->getRadius()+ball->getRadius(), 2)) {
		return true;
	}
	else {
		return false;
	}

}

void Wormhole::update(Ball *ball) {
	//invDistanceVecSquared
	//if (!WithinPullingDistance(ball))
		//return;
	//ball->setRadius(ball->getRadius() - (ball->getRadius()*0.1));
	float totalRadius = this->getRadius() + ball->getRadius();
	sf::Vector2f DistanceVec(this->getPosition().x - ball->getPosition().x, this->getPosition().y - ball->getPosition().y);
	sf::Vector2f DistanceVecSquared(powf(DistanceVec.x, 2), powf(DistanceVec.y, 2));
	float distance = sqrt(DistanceVecSquared.x + DistanceVecSquared.y);
	if (distance <= totalRadius) {
		win = true;
		cout << "WIN" << endl;
		ball->m_velocity = sf::Vector2f(0, 0);
		return;
	}
	sf::Vector2f DistanceUnitVec = DistanceVec / distance;
	//sf::Vector2f invDistanceVecSquared(1 / DistanceVecSquared.x, 1 / DistanceVecSquared.y);
	float invDistanceSquared = 1 / (distance*distance);
	ball->m_force += ((this->m_mass * ball->getMass()) * invDistanceSquared)*DistanceUnitVec;
}
