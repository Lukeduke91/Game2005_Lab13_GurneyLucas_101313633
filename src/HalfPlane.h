#pragma once
#include "DisplayObject.h"
#include "ColliderShape.h"

class HalfPlane : public DisplayObject, public ColliderHalfPlane
{
public:
	HalfPlane();

	void SetOrientation(float angle);
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

private:
	const float NORMAL_RENDER_SCALE = 100.0f;
};

