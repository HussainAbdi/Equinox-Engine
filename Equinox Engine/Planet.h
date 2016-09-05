#pragma once
class Ball;
//#include "Precompiled.h"
//#include "Ball.h"
class Planet : public sf::CircleShape
{
private:
	//sf::Vector2f m_centre;
	//sf::Vector2f m_force;
	float m_mass;
	float m_density;
	float m_invmass;
public:
	Planet(vector<Planet> *,float radius,float posX,float posY);
	~Planet();
	bool WithinPullingDistance(Ball *ball);
	void update(Ball *ball);
};

