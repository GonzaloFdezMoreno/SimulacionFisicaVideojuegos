#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <string>
#include <vector>
#include <iostream>
#include "Particle.h"
#include <list>

class ParticleGenerator {
protected:
	std::string _nombre;
	Vector3 _meanpos, _meanvel;
	double _gen_probability;
	int nParticles;
	Particle* model;
	physx::PxRigidDynamic* obj;
public:
	ParticleGenerator(Vector3 pos,Vector3 vel);
	~ParticleGenerator();
	void setParticle(Particle* model);
	virtual std::list<Particle*> generateParticles() = 0;
	virtual std::list<physx::PxRigidDynamic*> generateObjects(physx::PxPhysics* phy,physx::PxScene* scene) = 0;

	//virtual std::list<Firework*> genFw();

};