#include "Precompiled.h"

Planet::Planet(vector<Planet> *planets,float radius, float positionX, float positionY)
{
	this->setRadius(radius);
	this->setPosition(positionX, positionY);
	this->setOrigin(radius, radius);
	float volume = PI* powf(radius, 2);
	m_density = 5000; //1000 works for slight orbit
	this->m_mass = volume * m_density;
	this->m_invmass = 1 / m_mass;
	planets->push_back(*this);
}


Planet::~Planet()
{
}

bool Planet::WithinPullingDistance(Ball *ball) {
	float calc;
	calc = powf(ball->getPosition().x - this->getPosition().x, 2) + powf(ball->getPosition().y - this->getPosition().y, 2);
	if (calc < powf(this->getRadius()*2,2)) {
		return true;
	}
	else {
		return false;
	}

}



void Planet::update(Ball *ball){
	//invDistanceVecSquared
	//bool canPull = this->WithinPullingDistance(ball);
	//if (!canPull)
		//return;
	float totalRadius = this->getRadius() + ball->getRadius();
	float totalRadiusSquared = totalRadius * totalRadius;
	sf::Vector2f DistanceVec(this->getPosition().x - ball->getPosition().x, this->getPosition().y - ball->getPosition().y);
	sf::Vector2f DistanceVecSquared(powf(DistanceVec.x, 2), powf(DistanceVec.y, 2));
	if (DistanceVecSquared.x + DistanceVecSquared.y <= totalRadiusSquared) {
		gameover = true;
		ball->m_velocity = sf::Vector2f(0, 0);
		return;
	}
	float distance = sqrt(DistanceVecSquared.x + DistanceVecSquared.y);
	sf::Vector2f DistanceUnitVec = DistanceVec / distance;
	//sf::Vector2f invDistanceVecSquared(1 / DistanceVecSquared.x, 1 / DistanceVecSquared.y);
	float invDistanceSquared = 1 / (distance*distance);
	ball->m_force += ((this->m_mass * ball->getMass()) * invDistanceSquared)*DistanceUnitVec;
}