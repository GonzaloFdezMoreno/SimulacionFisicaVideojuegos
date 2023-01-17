#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <list>
#include <iostream>

#include "ParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "ObjectForceRegistry.h"
#include "RigidBody.h"
#include "StaticRigidBody.h"
#include <random>
#include <list>

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

	void addToList(RigidBody* rigid);

	void createDiana();
	void createDiana2();
	void createDiana3();
	void createDiana4();
	void createDiana5();
	
	void addPoints() { points++; }

	bool diana1destruida = false;
	bool diana2destruida = false;
	bool diana3destruida = false;
	bool diana4destruida = false;
	bool diana5destruida = false;



protected:
	std::mt19937 rnd;
	physx::PxPhysics* phy = NULL;
	physx::PxScene* scene = NULL;

	RenderItem* item = NULL;

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
	ExplosionForceGenerator* expForceGen2 = nullptr;
	ExplosionForceGenerator* expForceGen3 = nullptr;
	WhirlpoolForceGenerator* whForceGen = nullptr;

	std::vector<StaticRigidBody*> diana;

	float delay = 0;
	bool create = true;
	int points = 0;
	bool diana2creada = false;
	bool diana3creada = false;
	bool diana4creada = false;
	bool diana5creada = false;

	
};