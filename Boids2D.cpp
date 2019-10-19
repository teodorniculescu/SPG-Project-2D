#include "Boids2D.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Object2DBoids2D.h"

using namespace std;

Boids2D::Boids2D()
{
}

Boids2D::~Boids2D()
{
}

void Boids2D::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;

	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;

	createBoids(resolution.x, resolution.y);
}

void Boids2D::createBoids(int xRes, int yRes) {
	int xCoord, yCoord;
	float xVel, yVel;
	Mesh* boid;
	glm::vec2 velocity, position;
	std::string name;

	for (int boid_num = 0; boid_num < total_boid_num; boid_num++) {
		name = "boid" + std::to_string(boid_num);
		boid = Object2DBoids2D::CreateTriangle(name, glm::vec3(0, 0, 0), triangleSide, glm::vec3(1, 0, 0), true);
		xCoord = rand() % (xRes + 1);
		yCoord = rand() % (yRes + 1);
		position = glm::vec2(xCoord, yCoord);
		// generate random float number between 0 and 1
		xVel = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
		yVel = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
		// convert it to a number between -1 and 1
		xVel = (xVel * 2) - 1;
		yVel = (yVel * 2) - 1;
		// apply a base speed increase to it
		float constSpeed = 20;
		xVel *= constSpeed;
		yVel *= constSpeed;
		velocity = glm::vec2(xVel, yVel);
		this->boids[name] = new BoidStructure2D(boid, position, velocity);
	}
}

void Boids2D::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

double Boids2D::getAngleAbsoluteVelocity(glm::vec2 absoluteVelocity) {
	double angle = atan2(absoluteVelocity.y, absoluteVelocity.x);
	return angle;
}

void Boids2D::drawBoids() {
	static glm::mat3 modelMatrix;
	static double angle;

	for (int boid_num = 0; boid_num < total_boid_num; boid_num++) {
		std::string name = "boid" + std::to_string(boid_num);
		BoidStructure2D *bs = this->boids[name];
		modelMatrix = Object2DBoids2D::Translate(glm::mat3(1), bs->getPosition());
		angle = getAngleAbsoluteVelocity(bs->getVelocity());
		modelMatrix = Object2DBoids2D::Rotate(modelMatrix, AI_DEG_TO_RAD(-90) + angle);
		RenderMesh2D(bs->getMesh(), shaders["VertexColor"], modelMatrix);
	}
}
//Boids try to fly towards the centre of mass of neighbouring boids. 
glm::vec2 Boids2D::rule1(BoidStructure2D *bs) {
	return glm::vec2(0);
}
//Boids try to keep a small distance away from other objects (including other boids). 
glm::vec2 Boids2D::rule2(BoidStructure2D *bs) {
	return glm::vec2(0);
}
//Boids try to match velocity with near boids. 
glm::vec2 Boids2D::rule3(BoidStructure2D *bs) {
	return glm::vec2(0);
}

void Boids2D::moveBoids2NewPosition(float deltaTimeSeconds) {
	glm::vec2 v1, v2, v3;
	for (int boid_num = 0; boid_num < total_boid_num; boid_num++) {
		std::string name = "boid" + std::to_string(boid_num);
		BoidStructure2D *bs = this->boids[name];
		v1 = rule1(bs);
		v2 = rule2(bs);
		v3 = rule3(bs);
		glm::vec2 velocity = bs->getVelocity() + v1 + v2 + v3;
		bs->setPosition(bs->getPosition() + velocity * deltaTimeSeconds);
	}
}

void Boids2D::Update(float deltaTimeSeconds)
{
	drawBoids();
	moveBoids2NewPosition(deltaTimeSeconds);
}

void Boids2D::FrameEnd()
{

}

void Boids2D::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Boids2D::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Boids2D::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Boids2D::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Boids2D::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Boids2D::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Boids2D::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Boids2D::OnWindowResize(int width, int height)
{
}
