#include "UniformParticleGenerator.h"


UniformParticleGenerator::UniformParticleGenerator(Vector3 vel,Vector3 pos):ParticleGenerator(pos,vel) {

	


}
UniformParticleGenerator::~UniformParticleGenerator() {

}

std::list<Particle*> UniformParticleGenerator::generateParticles(Vector3 pos,Vector3 vel) {
	//Crear lista nueva desde aqui
	Particle* part = new Particle(pos, vel, 0.99, { 0,-1,0 }, { 0,0.6,1,1 }, 3);
	
	return ; 
}
