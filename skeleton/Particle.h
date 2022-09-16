#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"


class Particle {
public:
	Particle(Vector3 pos, Vector3 vel);
	~Particle();

	void integrate(double t); //es el update
	 

private:
	Vector3 veloc;
	physx::PxTransform posit;
	RenderItem* renderItemPart;
};