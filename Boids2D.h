#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include "BoidStructure2D.h"

class Boids2D : public SimpleScene
{
	public:
		Boids2D();
		~Boids2D();

		void Init() override;

		void createBoids(int xRes, int yRes);
		double getAngleAbsoluteVelocity(glm::vec2 absoluteVelocity);

		void drawBoids();

		glm::vec2 rule1(BoidStructure2D * bs);

		glm::vec2 rule2(BoidStructure2D * bs);

		glm::vec2 rule3(BoidStructure2D * bs);

		void moveBoids2NewPosition(float deltaTimeSeconds);

		void checkBoundary();

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		std::unordered_map<std::string, BoidStructure2D*> boids;
		const int total_boid_num = 40;
		const float triangleSide = 10;
		bool rule1TurnedOn = false;
		bool rule2TurnedOn = false;
		bool rule3TurnedOn = false;
		const double maxVelocity = 300, ruleDamping = 10, senseRadius = 75;
};
