#include "Actor.h"

Actor::Actor() :position(glm::vec3(0.0)), scale(glm::vec3(1.0)), upVector(glm::vec3(0.0, 1.0, 0.0)), phi(0.0f), theta(0.0f)
{
}

Actor::~Actor()
{
}

void Actor::update()
{
	modelMat = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(phi), upVector) * glm::scale(glm::mat4(1.0f), scale);

	glm::mat4 A = modelMat;
	A[3] = glm::vec4(0, 0, 0, 1);
	InvTransposeMat = glm::transpose(glm::inverse(A));
}

void Actor::updateOrbit(float deltaX, float deltaY, float deltaZ)
{
	theta += deltaX;
	phi += deltaY;

	float radTheta = glm::radians(theta);
	float radPhi = glm::radians(phi);

	rotation = glm::rotate(glm::mat4(1.0f), radTheta, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), radPhi, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMat = glm::translate(glm::mat4(1.0f), position) * rotation * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, deltaZ)) * glm::scale(glm::mat4(1.0f), scale);

	glm::mat4 A = modelMat;
	A[3] = glm::vec4(0, 0, 0, 1);
	InvTransposeMat = glm::transpose(glm::inverse(A));

	position += glm::vec3(rotation * glm::vec4(0.0f, 0.0f, deltaZ, 1.0f));
}

void Actor::updatePosition(float deltaX, float deltaY, float deltaZ)
{
	float radTheta = glm::radians(theta);
	float radPhi = glm::radians(phi);

	rotation = glm::rotate(glm::mat4(1.0f), radTheta, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), radPhi, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMat = glm::translate(glm::mat4(1.0f), position) * rotation * glm::translate(glm::mat4(1.0f), glm::vec3(deltaX, deltaY, deltaZ)) * glm::scale(glm::mat4(1.0f), scale);

	glm::mat4 A = modelMat;
	A[3] = glm::vec4(0, 0, 0, 1);
	InvTransposeMat = glm::transpose(glm::inverse(A));

	position += glm::vec3(rotation * glm::vec4(deltaX, deltaY, deltaZ, 1.0f));
}