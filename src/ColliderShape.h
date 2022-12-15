#pragma once
#include <GLM/vec2.hpp>


enum Shape
{
	CIRCLE,
	HALFPLANE,
	AABB
};

class ColliderShape
{
public:
	RigidBody* rigidBody = nullptr;
	virtual Shape GetShape() = 0;
};

class ColliderCircle : public ColliderShape
{
public:
	float radius = 40.0f;
	virtual Shape GetShape() override { return Shape::CIRCLE; };
};

class ColliderHalfPlane : public ColliderShape
{
public:
	glm::vec2 m_normal = glm::vec2(0.0f, -1.0f);
	float m_orientationAngle = 90.0f;

	virtual Shape GetShape() override { return Shape::HALFPLANE; };
};

class AABBCollider : public ColliderShape
{
public:
	float colliderWidth = 50.0f;
	float colliderHeight = 50.0f;

	virtual Shape GetShape() override { return Shape::AABB; };

};