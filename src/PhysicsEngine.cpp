#include "PhysicsEngine.h"
#include "RigidBody.h"
#include "GameObject.h"
#include "ColliderShape.h"
#include "Util.h"
#include <iostream>

void PhysicsEngine::AddObject(RigidBody* rigidBody)
{
	physicsObjects.push_back(rigidBody);

}

void PhysicsEngine::Update()
{
	for each (RigidBody * rb in physicsObjects)
	{
		rb->velocity += rb->gravityScale * gravityAcceleration * FixedDeltaTime;

		rb->velocity *= rb->damping;

		rb->gameObject->GetTransform()->position += rb->velocity * FixedDeltaTime;

		rb->netForce = glm::vec2(0, 0);
	}

	/*for (int i = 0; i < 3; i++)
	{
		for (int j = i + 1; j < 3; j++)
		{

		}
	}*/
	for (auto iterator = physicsObjects.begin(); iterator != physicsObjects.end(); iterator++)
	{
		RigidBody* rbA = (*iterator);

		auto iteratorB = iterator;
		iteratorB++;

		//iteratorB = end
		for (; iteratorB != physicsObjects.end(); iteratorB++)
		{
			RigidBody* rbB = (*iteratorB);

			if (rbA->collider->GetShape() == CIRCLE && rbB->collider->GetShape() == CIRCLE)
			{
				CircleCircleCollisionResponse((ColliderCircle*)rbA->collider, (ColliderCircle*)rbB->collider);
			}
			else if (rbA->collider->GetShape() == CIRCLE && rbB->collider->GetShape() == HALFPLANE)
			{
				CircleHalfPlaneCollisionResponse((ColliderCircle*)rbA->collider, (ColliderHalfPlane*)rbB->collider);
			}
			else if (rbA->collider->GetShape() == HALFPLANE && rbB->collider->GetShape() == CIRCLE)
			{
				CircleHalfPlaneCollisionResponse((ColliderCircle*)rbB->collider, (ColliderHalfPlane*)rbA->collider);
			}
			else if (rbA->collider->GetShape() == AABB && rbB->collider->GetShape() == AABB)
			{
				AABBCollisionResponse((AABBCollider*)rbB->collider, (AABBCollider*)rbA->collider);
			}
			else if (rbA->collider->GetShape() == CIRCLE && rbB->collider->GetShape() == AABB)
			{
				AABBCircleCollisionResponse((AABBCollider*)rbB->collider, (ColliderCircle*)rbA->collider);
			}
			//if distancebetween(A,B) < A.radius + B.radius, then they are colliding. Print
			//if(Colliding(rbA, rbB))
			//if (DistanceBetween(rbA->gameObject->GetTransform()->position, rbB->gameObject->GetTransform()->position) < 
			//	(rbA->gameObject->GetWidth() + rbB->gameObject->GetWidth()))
			//{
			//	//->gameObject->GetWidth()
			//	std::cout << "Colliding!!!";
			//}
			// Create Classes Point, Circle, HalfPlane
			
		}
	}
}

bool PhysicsEngine::CircleHalfPlaneCollisionResponse(ColliderCircle* circle, ColliderHalfPlane* halfPlane)
{
	Transform* circleTranform = circle->rigidBody->gameObject->GetTransform();
	Transform* halfPlaneTransform = halfPlane->rigidBody->gameObject->GetTransform();

	glm::vec2 displacement = circleTranform->position - halfPlaneTransform->position;

	float distance = Util::Dot(displacement, halfPlane->m_normal);

	float overlap = circle->radius - distance;

	if (overlap <= 0)
	{
		return false;
	}

	glm::vec2 minimumTranslationVector = overlap * halfPlane->m_normal;

	circleTranform->position += minimumTranslationVector;

	return true;
}

bool PhysicsEngine::CircleCircleCollisionResponse(ColliderCircle* circle, ColliderCircle* circleB)
{
	Transform* transformA = circle->rigidBody->gameObject->GetTransform();
	Transform* transformB = circleB->rigidBody->gameObject->GetTransform();

	glm::vec2 displacementAtoB = transformB->position - transformA->position;

	float distanceAtoB = Util::Magnitude(displacementAtoB);

	float overlap = (circle->radius + circleB->radius) - distanceAtoB;

	if (overlap < 0)
	{
		return false;
	}

	glm::vec2 collisionNormalAtoB = displacementAtoB / distanceAtoB;

	glm::vec2 minimumTranslationVector = collisionNormalAtoB * overlap;


	transformA->position -= minimumTranslationVector * 0.5f;
	transformB->position += minimumTranslationVector * 0.5f;

	glm::vec2 vBRelativeA = circle->rigidBody->velocity - circleB->rigidBody->velocity;

	float v2closing1 = Util::Dot(vBRelativeA, collisionNormalAtoB);

	if (v2closing1 > 0)
	{
		return true;
	}
	std::cout << "Works \n";

	//if (distanceAtoB < circle->radius + circleB->radius)
	float restitution = Util::Min(circle->rigidBody->bounsiness, circleB->rigidBody->bounsiness);

	float totalMass = circle->rigidBody->mass + circleB->rigidBody->mass;
	float impulse = -(1.0f + restitution) * v2closing1 * circle->rigidBody->mass * circleB->rigidBody->mass / (totalMass);

	glm::vec2 impulseA = -impulse * collisionNormalAtoB;
	glm::vec2 impulseB = impulse * collisionNormalAtoB;

	glm::vec2 deltaVA = impulseA / circle->rigidBody->mass;
	glm::vec2 deltaVB = impulseB / circleB->rigidBody->mass;

	circle->rigidBody->velocity += deltaVA;
	circleB->rigidBody->velocity += deltaVB;
}

float PhysicsEngine::GetMinimumTranslationVector1D(float centerA, float radiusA, float centerB, float radiusB)
{
	float displacementAtoB = centerB - centerA;
	float distance = abs(displacementAtoB);
	float overlap = (radiusA + radiusB) - distance;

	if (overlap < 0.0f)
	{
		return 0.0f;
	}
	
	float directionFromAtoB = Util::Sign(displacementAtoB);
	//float minimumTraslationVector = overlap;
	float minimumTraslationVector = displacementAtoB * overlap;
	return minimumTraslationVector;
}

bool PhysicsEngine::AABBCollisionResponse(AABBCollider* aabb, AABBCollider* AABB)
{
	Transform* transformA = aabb->rigidBody->gameObject->GetTransform();
	Transform* transformB = AABB->rigidBody->gameObject->GetTransform();

	float mtvX = GetMinimumTranslationVector1D(transformA->position.x, aabb->colliderWidth * 0.5f, 
											   transformB->position.x, AABB->colliderWidth * 0.5f);

	float mtvY = GetMinimumTranslationVector1D(transformA->position.y, aabb->colliderHeight * 0.5f,
											   transformB->position.y, AABB->colliderHeight * 0.5f);

	if (mtvX == 0.0f || mtvY == 0.0f) return false;
	glm::vec2 mtv2D;
	if (abs(mtvX) < abs(mtvY))
	{
		mtv2D = glm::vec2(mtvX, 0.0f);
	}

	else
	{
		mtv2D = glm::vec2(0.0f, mtvY);

	}
	transformA->position -= 0.5f * mtv2D;
	transformB->position += 0.5f * mtv2D;

	return true;
}

bool PhysicsEngine::AABBCircleCollisionResponse(AABBCollider* AABB, ColliderCircle* Circle)
{
	Transform* transformA = Circle->rigidBody->gameObject->GetTransform();
	Transform* transformB = AABB->rigidBody->gameObject->GetTransform();

	float mtvX = GetMinimumTranslationVector1D(transformA->position.x, Circle->radius * 0.5f,
		transformB->position.x, AABB->colliderWidth * 0.5f);

	float mtvY = GetMinimumTranslationVector1D(transformA->position.y, Circle->radius * 0.5f,
		transformB->position.y, AABB->colliderHeight * 0.5f);

	/*glm::vec2 displacementAtoB = transformB->position - transformA->position;
	float distanceAtoB = Util::Dot(displacementAtoB, glm::vec2(AABB->colliderWidth, AABB->colliderHeight));*/
	glm::vec2 closestPoint = Util::Clamp(transformA->position, transformB->position.x + AABB->colliderWidth / 2);
	//float distanceAtoB = Util::Magnitude(displacementAtoB);
	//Clamp(circle.point.x, x - W/2, x + W/2 )||(circle.xy, Box.Min,Box.Max
	float overlap = Circle->radius - Util::Distance(closestPoint, transformA->position);
	
	if (overlap < 0)
	{
		return true;
	}
	//std::cout << "hi\n";
	glm::vec2 direction = Util::Normalize(transformA->position - closestPoint);
	glm::vec2 mtv = direction * overlap;

	transformA->position += mtv;
	transformB->position -= mtv;
	//return false;
}

//float PhysicsEngine::DistanceBetween(glm::vec2 a, glm::vec2 b)
//{
//	return Length(b-a);
//}
//
//float PhysicsEngine::Length(glm::vec2 ABLength)
//{
//	return ABLength.y * ABLength.x;
//	// use return abL +AbL for the half plane
//}