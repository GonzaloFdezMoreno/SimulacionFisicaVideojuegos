#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <list>



class Particle {
public:
	Particle(Vector3 pos, Vector3 vel, float dapming, Vector3 accel, Vector4 color, int tam, double mass, bool box);
	~Particle();

	virtual void update(double t); //es el update
	virtual std::list<Particle*>  explode() { std::list<Particle*> lst; return lst; };

	void addForce(Vector3 f) { force += f; }
	void noForce() { force *= 0; }
	//virtual Particle* clone()const;
	bool die = false;
	bool isFire = false;

	physx::PxTransform posit;
	Vector3 veloc;
	float damp;
	float inv_mass;
	double masa;
	
	//bool wiGravity = false;
	//bool wiWind = false;

protected:
	
	
	RenderItem* renderItemPart;
	
	Vector3 accel;
	

	float timeAlive = 0;

	Vector3 force;
	bool cubo=false;
	
};