#pragma once
#ifndef __RIGID_BODY__
#define __RIGID_BODY__
#include <glm/vec2.hpp>

class GameObject;
class ColliderShape;

struct RigidBody
{
	GameObject* gameObject = nullptr;
	ColliderShape* collider = nullptr;

	float bounsiness = 0.5f;
	float mass = 8.0f;
	glm::vec2 velocity = glm::vec2(0, 0);
	float gravityScale = 1.0f;
	float damping = 0.98f;
	glm::vec2 acceleration;
	bool isColliding = false;
	glm::vec2 netForce = glm::vec2(0, 0);

	float radius = 100.0f;
};
#endif /* defined (__RIGID_BODY__) */