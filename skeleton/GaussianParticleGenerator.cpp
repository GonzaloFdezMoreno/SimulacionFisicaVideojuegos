#include "GaussianParticleGenerator.h"



GaussianParticleGenerator::GaussianParticleGenerator(Vector3 pos,Vector3 vel):ParticleGenerator(pos,vel) {

	std_dev_pos =pos;

}
GaussianParticleGenerator::~GaussianParticleGenerator() {

}

std::list<Particle*> GaussianParticleGenerator::generateParticle() {
	std::list<Particle*> lPart;
	Particle* part = new Particle({std_dev_pos}, {std_dev_vel}, 1, { 0,0,0 }, { 0,0.6,1,1 }, 3);
	lPart.push_back(part);


	return lPart;

}