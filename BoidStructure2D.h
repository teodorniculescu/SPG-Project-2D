#pragma once
#include <string>
#include <Core/Engine.h>
class BoidStructure2D
{
public:
	BoidStructure2D(Mesh *mesh, glm::vec2 position, glm::vec2 velocity);
	~BoidStructure2D();

	Mesh* getMesh();
	glm::vec2 getPosition();
	void setPosition(glm::vec2 position);
	glm::vec2 getVelocity();
	void setVelocity(glm::vec2 velocity);
	float getSightRadius();
	float getSightAngle();

private:
	Mesh *mesh;
	glm::vec2 velocity, position;
	const float sightRadius = 25, sightAngle = AI_DEG_TO_RAD(300);
};

