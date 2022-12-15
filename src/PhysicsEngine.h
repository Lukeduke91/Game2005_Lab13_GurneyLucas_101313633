#include <list>
#include<glm/vec2.hpp>


class RigidBody;
class ColliderCircle;
class ColliderHalfPlane;
class AABBCollider;

class PhysicsEngine
{
	float FixedDeltaTime = 1.0f / 60.0f;
	glm::vec2 gravityAcceleration = glm::vec2(981, 0);
	//float Length;
private:
	std::list<RigidBody*> physicsObjects;


public:
	void AddObject(RigidBody* rigidBody);
	void Update();

	bool CircleHalfPlaneCollisionResponse(ColliderCircle* circle, ColliderHalfPlane* halfPlane);
	bool CircleCircleCollisionResponse(ColliderCircle* circle, ColliderCircle* circleB);
	float GetMinimumTranslationVector1D(float centerA, float radiusA, float centerB, float radiusB);
	bool AABBCollisionResponse(AABBCollider* aabb, AABBCollider* AABB);
	bool AABBCircleCollisionResponse(AABBCollider* AABB, ColliderCircle* Circle);

	/*float DistanceBetween(glm::vec2 a, glm::vec2 b);
	float Length(glm::vec2 ABLength);*/
};
