#include "Box.h"
#include "Util.h"

Box::Box()
{
	GetRigidBody()->collider = this;
	GetRigidBody()->collider->rigidBody = GetRigidBody();
}

void Box::Draw()
{
	Util::DrawRect(GetTransform()->position - glm::vec2(colliderWidth, colliderHeight),
		colliderWidth, colliderHeight, glm::vec4(0.7f, 0.6f, 0.0f, 1.0f));
}

void Box::Update()
{
}

void Box::Clean()
{
}
