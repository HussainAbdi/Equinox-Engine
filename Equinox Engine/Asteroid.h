#pragma once
class Planet;
class Ball;
#include <iostream>
using namespace std;
class Asteroid : public sf::CircleShape
{
private:
	double m_orbitAngle;
	float m_orbitRadius;
	float planetX;
	float planetY;
public:
	Asteroid(Planet * planet, vector<Asteroid> *asteroids);
	~Asteroid();
	void update(Ball * ball);
	void circOrbit();
};

