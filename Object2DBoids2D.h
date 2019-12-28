#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2DBoids2D
{

	Mesh* CreateTriangle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);

	Mesh * CreateCircle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);

	glm::mat3 Translate(glm::mat3 matrix, glm::vec2 vect);

	glm::mat3 Rotate(glm::mat3 matrix, double angleRadians);

	double distanceBetweenPoints(glm::vec2 pointA, glm::vec2 pointB);

	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

}

