#include "HalfPlane.h"
#include "Util.h"

HalfPlane::HalfPlane()
{
	GetRigidBody()->collider = this;
	GetRigidBody()->collider->rigidBody = GetRigidBody();
}

void HalfPlane::SetOrientation(float angle)
{
	m_orientationAngle = angle;
	m_normal = Util::AngleMagnitudeToVec2(angle, 1.0f);
}

void HalfPlane::Draw()
{
	glm::vec2 start = GetTransform()->position;
	glm::vec2 end = start + (m_normal * NORMAL_RENDER_SCALE);
	//Draw normal
	Util::DrawLine(start, end);

	glm::vec2 perpendicular = Util::AngleMagnitudeToVec2(m_orientationAngle + 90.0f, 1.0f);

	Util::DrawLine(start - perpendicular * 1000000.0f, start + perpendicular * 1000000.0f);
}

void HalfPlane::Update()
{
}

void HalfPlane::Clean()
{
}
