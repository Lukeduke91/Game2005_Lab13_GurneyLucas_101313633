#include "DisplayObject.h"
#include "ColliderShape.h"

class Box : public DisplayObject, public AABBCollider
{
public:
	Box();

	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
};

