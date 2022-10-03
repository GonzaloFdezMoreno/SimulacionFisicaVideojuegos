#pragma once

#include "core.hpp"
#include "RenderUtils.hpp"


class Plane {
public:
	Plane(Vector3 pos,Vector4 color);
	~Plane();

	//void integrate(double t); //es el update


protected:
	
	physx::PxTransform posit;
	RenderItem* renderItemPart;
	
};