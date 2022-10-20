#pragma once
#include "ParticleGenerator.h"
#include "ParticleSystem.h"
#include <vector>
#include <string>
#include <list>

class UniformParticleGenerator:public ParticleGenerator {

private:
	Vector3 _vel_width;
	Vector3 _pos_width;
	std::list<Particle*> lPart;

public:
	UniformParticleGenerator(Vector3 vel,Vector3 pos);
	~UniformParticleGenerator();
	void update(double t);
	std::list<Particle*> generateParticles(Vector3 vel, Vector3 pos) override;
};