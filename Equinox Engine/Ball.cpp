#include "Precompiled.h"
using namespace std;


Ball::Ball(float radius, float positionX, float positionY)
{
	this->m_velocity = sf::Vector2f(0, 0);
	this->setRadius(radius);
	this->setPosition(positionX, positionY);
	this->setOrigin(radius, radius);
	float volume = PI*radius*radius;
	m_density = 10; //10 works for slight orbit;
	this->m_mass = volume * m_density;
	this->m_invmass = 1 / m_mass;
}


Ball::~Ball()
{
}

//void Ball::setCentre() {
	//m_centre.x = this->getPosition().x;
	//m_centre.y = this->getPosition().y;
//}

void Ball::circOrbit(Wormhole * goal, float dt) {
	sf::Vector2f orbRadius(this->getPosition().x - goal->getPosition().x, this->getPosition().y - goal->getPosition().y);
	//cout << orbRadius.x << "," << orbRadius.y << endl;
	sf::Vector2f orbRadiusSquared(orbRadius.x*orbRadius.x, orbRadius.y*orbRadius.y);
	float magnitude = sqrtf(orbRadiusSquared.x + orbRadiusSquared.y);
	sf::Vector2f orbRadiusUnitVec = orbRadius / magnitude;
	//cout << orbRadiusUnitVec.x << "," << orbRadiusUnitVec.y << endl;
	sf::Vector2f velocityUnitVec(orbRadiusUnitVec.y *(-1),orbRadiusUnitVec.x);
	//cout << velocityUnitVec.x << "," << velocityUnitVec.y << endl;
	float velocityX = (sqrtf(goal->getMass() / orbRadius.x))* velocityUnitVec.x;
	float velocityY = (sqrtf(goal->getMass() / orbRadius.y))* velocityUnitVec.y;
	m_velocity = sf::Vector2f(velocityX, velocityY);
	//cout << m_velocity.x << "," << m_velocity.y << endl;
	//sf::Vector2f pos(this->getPosition());
	//pos += m_velocity *dt;
	//cout << pos.x << "," << pos.y << endl;
	//this->setPosition(pos);
	//ERROR: Works split second then dissapears...
}

void Ball::thrustVelocity(sf::Vector2f force, float time) {
	//point acceleration = force / mass;
	//centre += velocity * dt;
	//velocity += acceleration * dt;
	m_velocity = (force * m_invmass) * time;
	cout << m_invmass << endl;
	cout << m_mass << endl;
	cout << m_velocity.x << "," << m_velocity.y << endl;
}

void Ball::update(vector<Planet> planets,float dt, Wormhole *goal, vector<Asteroid> asteroids)
{
	// velocity Verlet method integration
	sf::Vector2f acc, newAcc;
	sf::Vector2f pos = this->getPosition();
	updateObjs(planets, goal, asteroids);
	acc = m_force / m_mass;
	sf::Vector2f halfAcc(acc.x / 2, acc.y / 2);
	m_force = sf::Vector2f(0, 0);
	pos += (m_velocity + dt * halfAcc) * dt;
	//cout << pos.x << "," << pos.y << endl;
	updateObjs(planets, goal, asteroids);
	newAcc = m_force / m_mass;
	m_force = sf::Vector2f(0, 0);
	sf::Vector2f totalAcc(acc + newAcc);
	sf::Vector2f avgAcc(totalAcc.x / 2, totalAcc.y / 2);
	m_velocity += avgAcc * dt;
	//cout << m_velocity.x << " " << m_velocity.y << endl;
	this->setPosition(pos);
		
}

void Ball::update(Wormhole * goal, float dt)
{
		// velocity Verlet method integration
		sf::Vector2f acc, newAcc;
		sf::Vector2f pos = this->getPosition();
		goal->update(this);
		//this->circOrbit(goal, dt);
		acc = m_force / m_mass;
		sf::Vector2f halfAcc(acc.x / 2, acc.y / 2);
		pos += (m_velocity + dt * halfAcc) * dt;
		m_force = sf::Vector2f(0, 0);
		//cout << pos.x << "," << pos.y << endl;
		goal->update(this);
		//this->circOrbit(goal, dt);
		newAcc = m_force / m_mass;
		m_force = sf::Vector2f(0, 0);
		sf::Vector2f totalAcc(acc + newAcc);
		sf::Vector2f avgAcc(totalAcc.x / 2, totalAcc.y / 2);
		m_velocity += avgAcc * dt;
		//cout << m_velocity.x << " " << m_velocity.y << endl;
		this->setPosition(pos);
}

void Ball::update(float dt)
{
	sf::Vector2f pos = this->getPosition();
	pos += m_velocity * dt;
	this->setPosition(pos);
}

void Ball::align(sf::Vector2i *localPosition) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		isBallSelected(*localPosition, this->getPosition());
		if (this->m_ballSelected) {
			if (localPosition->y - 20 > 0 && localPosition->y + 20 < 900) {
					this->setPosition(this->getPosition().x, localPosition->y);
			}
		}
	}
	else if (!(sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
		this->m_ballSelected = false;
	}
	
}

void Ball::isBallSelected(sf::Vector2i localPosition, sf::Vector2f ball1Centre) {
	float calc;
	calc = powf(localPosition.x - ball1Centre.x, 2) + powf(localPosition.y - ball1Centre.y, 2);
	//cout << calc << endl;
	if (calc < powf(this->getRadius(), 2)) {
		this->m_ballSelected = true;
		//cout << "ball selected" << endl;
	}
}

void Ball::updateObjs(vector<Planet> planets, Wormhole *goal, vector<Asteroid> asteroids) {
	for (int i = 0; i < planets.size(); i++) {
		planets[i].update(this);
	}
	for (int i = 0; i < asteroids.size(); i++) {
		asteroids[i].update(this);
	}
	goal->update(this);
}