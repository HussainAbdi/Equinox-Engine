#pragma once
class Planet;
class Wormhole;
class Asteroid;
//#include "Precompiled.h"
#include <iostream>
//#include "Planet.h"
using namespace std;
class Ball : public sf::CircleShape
{
private:
	//sf::Vector2f m_centre;
	float m_mass;
	float m_invmass;
	float m_density;
	bool m_ballYSet = false;
	bool m_ballSelected;
public:
	sf::Vector2f m_velocity;
	sf::Vector2f m_force;
	Ball(float radius,float posX, float posY);
	~Ball();
	void circOrbit(Planet * planet, float dt);
	void thrustVelocity(sf::Vector2f force, float time); // inital thrust
	void update(vector<Planet> planets,float dt, Wormhole *goal,vector<Asteroid> asteroids);
	void updateObjs(vector<Planet> planets, Wormhole *goal, vector <Asteroid> asteroids);
	void update(float dt);
	void update(Wormhole * goal, float dt);
	sf::Vector2f getVelocity() { return m_velocity; }
	float getMass() { return m_mass; }
	
	void align(sf::Vector2i *localPosition);
	void Ball::isBallSelected(sf::Vector2i localPosition, sf::Vector2f ball1Centre);
	//DEBUGGING
	void printRadius() {
		cout << this->getRadius() << endl;
	}
	void printCentre() {
		cout << this->getPosition().x << " "<< this->getPosition().y << endl;
	}
};

