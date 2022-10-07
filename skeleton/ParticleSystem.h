#pragma once
#include <list>
#include <iostream>
#include "Particle.h"
#include "ParticleGenerator.h"
#include <string>

using namespace std;

class ParticleSystem {
protected:
	std::list<Particle*> _particles;
	std::list<ParticleGenerator*> _particles_generators;
public:
	void update(double t);
	ParticleGenerator* getParticleGnerator(string nombre);
	void generateFireworkSystem();
};