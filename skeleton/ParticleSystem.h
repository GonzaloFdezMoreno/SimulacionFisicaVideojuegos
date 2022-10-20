#pragma once
#include <list>
#include <iostream>
#include "Particle.h"
#include "ParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include <string>

using namespace std;

class ParticleSystem {
protected:
	std::list<Particle*> _particles;
	std::list<ParticleGenerator*> _particles_generators;
	Vector3 gravity;
	int nump;
public:
	ParticleSystem(int npart);
	~ParticleSystem();
	void update(double t);
	ParticleGenerator* getParticleGenerator(string nombre);
	void generateFireworkSystem();

	ParticleGenerator* uPG = nullptr;
	ParticleGenerator* gPG = nullptr;

};