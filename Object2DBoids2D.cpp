#include "Object2DBoids2D.h"

#include <Core/Engine.h>
#include <iostream>

glm::mat3 Object2DBoids2D::Translate(glm::mat3 matrix, glm::vec2 vect) {
	glm::mat3 aux = glm::mat3(0, 0, 0, 0, 0, 0, vect[0], vect[1], 0);
	return matrix + aux;
}

glm::mat3 Object2DBoids2D::Rotate(glm::mat3 matrix, double angleRadians) {
	double cs = cos(angleRadians), ss = sin(angleRadians);
	return matrix * glm::mat3(cs, ss, 0, -ss, cs, 0, 0, 0, 1);
}

double Object2DBoids2D::distanceBetweenPoints(glm::vec2 pointA, glm::vec2 pointB) {
	double result;
	result = pow((pointA.x - pointB.x), 2);
	result += pow((pointA.y - pointB.y), 2);
	result = sqrt(result);
	return result;
}

Mesh* Object2DBoids2D::CreateTriangle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;
	const float sine60 = 0.86602, xmodif = sine60 / 2, ymodif = 0.75;
	glm::vec3 cU = (color * glm::vec3(2.0));
	for (int i = 0; i < 3; i++)
		if (cU[i] > 1.0)
			cU[i] = 1.0;
	glm::vec3 cL = (color / glm::vec3(2.0));

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(0, sine60 + 0.5, 0) * glm::vec3(length), cU),
		VertexFormat(corner + glm::vec3(ymodif, -xmodif, 0) * glm::vec3(length), cL),
		VertexFormat(corner + glm::vec3(-ymodif, -xmodif, 0) * glm::vec3(length), cL)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2};
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2DBoids2D::CreateCircle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;
	unsigned short numDots = 36;
	double angleIncrement = AI_DEG_TO_RAD(360 / numDots);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color)
	};
	for (int i = 0; i < numDots; i++)
		vertices.push_back(VertexFormat(corner + glm::vec3(length * cos(angleIncrement * i), length * sin(angleIncrement * i), 0), color));

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, numDots, 1};
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		for (int i = 0; i < numDots - 1; i++) {
			indices.push_back(0);
			indices.push_back(i + 1);
			indices.push_back(i + 2);
		}
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2DBoids2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

