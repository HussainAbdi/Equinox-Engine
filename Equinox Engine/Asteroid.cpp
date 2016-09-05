#include "Precompiled.h"


Asteroid::Asteroid(Planet * planet,vector<Asteroid> *asteroids)
{
	this->m_orbitAngle = 0;
	this->planetX = planet->getPosition().x;
	this->planetY = planet->getPosition().y;
	float astRadius = planet->getRadius()*0.2;
	this->setRadius(planet->getRadius()*0.2);
	this->m_orbitRadius = planet->getRadius() * 2;
	this->setPosition(planet->getPosition().x+this->m_orbitRadius, planet->getPosition().y);
	this->setOrigin(astRadius, astRadius);
	asteroids->push_back(*this);
}


Asteroid::~Asteroid()
{
}


void Asteroid::update(Ball * ball) {
	float totalRadius = this->getRadius() + ball->getRadius();
	float totalRadiusSquared = totalRadius * totalRadius;
	sf::Vector2f DistanceVec(this->getPosition().x - ball->getPosition().x, this->getPosition().y - ball->getPosition().y);
	sf::Vector2f DistanceVecSquared(powf(DistanceVec.x, 2), powf(DistanceVec.y, 2));
	if (DistanceVecSquared.x + DistanceVecSquared.y < totalRadiusSquared) {
		gameover = true;
		ball->m_velocity = sf::Vector2f(0, 0);
		return;
	}

}

void Asteroid::circOrbit() {
	float x = planetX + cos(this->m_orbitAngle)*this->m_orbitRadius;
	float y = planetY + sin(this->m_orbitAngle)*this->m_orbitRadius;
	this->setPosition(x, y);
	if (this->m_orbitAngle < 2 * PI) {
		this->m_orbitAngle += 0.01;
	}
	else
	{
		this->m_orbitAngle = 0;
	}
}