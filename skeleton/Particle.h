#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"


class Particle {
public:
	Particle(Vector3 pos, Vector3 vel,float dapming,Vector3 accel,Vector4 color,int tam);
	~Particle();

	void integrate(double t); //es el update
	 

protected:
	Vector3 veloc;
	physx::PxTransform posit;
	RenderItem* renderItemPart;
	float damp;
	Vector3 accel;
};