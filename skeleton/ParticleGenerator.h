#pragma once
#include <string>
#include <vector>
#include "Particle.h"

class ParticleGenerator {
protected:
	string _nombre;
	Vector3 _meanpos, _meanvel;
	double _gen_probability;
	int nParticles;
	Particle* model;
public:
	void setParticle(Particle* model);
	virtual list<Particle*> generateParticles() = 0;

};