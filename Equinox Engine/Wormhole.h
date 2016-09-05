#pragma once
class Wormhole : public sf::CircleShape
{
private:
	float m_mass;
	float m_invmass;
	float m_density;
public:
	Wormhole(float radius, float positionX, float positionY);
	~Wormhole();
	bool WithinPullingDistance(Ball *ball);
	void update(Ball *ball);
	float getMass() { return m_mass; }
};

