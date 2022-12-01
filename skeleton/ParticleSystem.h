#pragma once
#include <list>
#include <iostream>
#include "Particle.h"
#include "Firework.h"
#include "ParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "FireworkGenerator.h"


#include "ParticleForceRegistry.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "WhirlpoolForceGenerator.h"


#include "AnchorForceGen.h"
#include "SpringForceGen.h"
#include <string>

using namespace std;

class ParticleSystem {
protected:
	std::list<Particle*> _particles;
	std::list<Firework*> _fireworks;
	std::list<ParticleGenerator*> _particles_generators;
	Vector3 gravity;
	int nump;

	ParticleForceRegistry* regfor;
public:
	ParticleSystem(int npart);
	~ParticleSystem();
	void update(double t);
	ParticleGenerator* getParticleGenerator(string nombre);
	void generateFireworkSystem();

	void createExplosionForce();
	void createwindAreaForce();

	void generateSpring();

	void eraseForces();

	ParticleGenerator* uPG = nullptr;
	ParticleGenerator* gPG = nullptr;
	//FireworkGenerator* fireworkSysGen = nullptr;
	ParticleGenerator* fireworkSysGen = nullptr;

	GravityForceGenerator* gforceGen = nullptr;
	WindForceGenerator* wforceGen = nullptr;
	ExplosionForceGenerator* expForceGen = nullptr;
	WhirlpoolForceGenerator* whForceGen = nullptr;

	bool activate = false;
	bool getgrav = false;
	bool getwind = false;
	bool getexplosion = false;
	bool getWhirl = false;

	bool create = false;

};