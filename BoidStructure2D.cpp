#include "BoidStructure2D.h"


BoidStructure2D::BoidStructure2D(Mesh * mesh, glm::vec2 position, glm::vec2 velocity)
{
	this->mesh = mesh;
	this->position = position;
	this->velocity = velocity;
}

BoidStructure2D::~BoidStructure2D()
{
}

Mesh * BoidStructure2D::getMesh()
{
	return mesh;
}

glm::vec2 BoidStructure2D::getPosition()
{
	return this->position;
}

void BoidStructure2D::setPosition(glm::vec2 position)
{
	this->position = position;
}


glm::vec2 BoidStructure2D::getVelocity()
{
	return this->velocity;
}

void BoidStructure2D::setVelocity(glm::vec2 velocity)
{
	this->velocity = velocity;
}

float BoidStructure2D::getSightRadius()
{
	return this->sightRadius;
}

float BoidStructure2D::getSightAngle()
{
	return this->sightAngle;
}

