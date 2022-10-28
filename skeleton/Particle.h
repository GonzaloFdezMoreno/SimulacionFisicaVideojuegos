#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <list>


class Particle {
public:
	Particle(Vector3 pos, Vector3 vel,float dapming,Vector3 accel,Vector4 color,int tam);
	~Particle();

	virtual void update(double t); //es el update
	virtual std::list<Particle*>  explode() { std::list<Particle*> lst; return lst; };
	//virtual Particle* clone()const;
	bool die = false;
	bool isFire = false;

	physx::PxTransform posit;

protected:
	Vector3 veloc;
	
	RenderItem* renderItemPart;
	float damp;
	Vector3 accel;

	float timeAlive = 0;
	
};