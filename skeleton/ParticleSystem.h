#pragma once
#include <list>
#include <iostream>
#include "Particle.h"
#include "Firework.h"
#include "PAgua.h"
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
#include "BuoyancyForceGen.h"
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
	void generateMultipleFireworkSystem();

	void createExplosionForce();
	void createwindAreaForce();

	void generateSpring();
	void generateMultiSpring(float d,float l);
	void flota();

	void eraseForces();

	ParticleGenerator* uPG = nullptr;
	ParticleGenerator* gPG = nullptr;
	//FireworkGenerator* fireworkSysGen = nullptr;
	ParticleGenerator* fireworkSysGen = nullptr;
	ParticleGenerator* fireworkSysGen2 = nullptr;
	ParticleGenerator* fireworkSysGen3 = nullptr;
	ParticleGenerator* fireworkSysGen4 = nullptr;
	ParticleGenerator* fireworkSysGen5 = nullptr;

	GravityForceGenerator* gforceGen = nullptr;
	WindForceGenerator* wforceGen = nullptr;
	ExplosionForceGenerator* expForceGen = nullptr;
	WhirlpoolForceGenerator* whForceGen = nullptr;

	bool activate = false;
	bool activate2 = false;

	bool getgrav = false;
	bool getwind = false;
	bool getexplosion = false;
	bool getWhirl = false;

	bool create = false;
	bool create2 = false;
	bool created = false;
	bool created2 = false;
	bool flotar = false;
	bool fin = false;
};