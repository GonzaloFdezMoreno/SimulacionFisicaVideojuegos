#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <list>
#include <iostream>

#include "ParticleGenerator.h"
#include "UniformParticleGenerator.h"

class WorldManager {
public:
	WorldManager(int nobj, physx::PxPhysics* phy, physx::PxScene* scene);
	~WorldManager();
	void update(double t);
	ParticleGenerator* getParticleGenerator(string nombre);
	

protected:

	physx::PxPhysics* phy = NULL;
	physx::PxScene* scene = NULL;
	std::list<physx::PxRigidDynamic*> _objects;
	
	std::list<ParticleGenerator*> _particles_generators;
	Vector3 gravity;
	int nob;
	
	ParticleGenerator* uPG = nullptr;

};