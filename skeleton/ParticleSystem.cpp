#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {

	ParticleGenerator* uPG=new UniformParticleGenerator({ 0,0,0 }, { 1,2,1 });
	_particles_generators.push_back(uPG);
}
ParticleSystem::~ParticleSystem() {


}

void ParticleSystem::update(double t) {
	//aqui el generateparticles
}
ParticleGenerator* ParticleSystem::getParticleGenerator(string nombre) {

}
void ParticleSystem::generateFireworkSystem() {

}