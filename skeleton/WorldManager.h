#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <list>
#include <iostream>

#include "ParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "ObjectForceRegistry.h"
#include "RigidBody.h"

class WorldManager {
public:
	WorldManager(int nobj, physx::PxPhysics* phy, physx::PxScene* scene);
	~WorldManager();
	void update(double t);
	ParticleGenerator* getParticleGenerator(string nombre);
	
	bool getgrav = false;
	bool getwind = false;
	bool getexplosion = false;
	bool getWhirl = false;

	void createExplosionForce();
	void createwindAreaForce();


protected:

	physx::PxPhysics* phy = NULL;
	physx::PxScene* scene = NULL;
	std::list<RigidBody*> _objects;
	std::list<physx::PxRigidDynamic*> _rigidobjects;
	
	std::list<ParticleGenerator*> _particles_generators;
	Vector3 gravity;
	int nob;
	
	ParticleGenerator* uPG = nullptr;
	ObjectForceRegistry* regforobj;

	GravityForceGenerator* gforceGen = nullptr;
	WindForceGenerator* wforceGen = nullptr;
	ExplosionForceGenerator* expForceGen = nullptr;
	WhirlpoolForceGenerator* whForceGen = nullptr;

	float delay = 0;
	bool create = true;
};