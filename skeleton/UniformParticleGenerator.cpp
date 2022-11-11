#include "UniformParticleGenerator.h"


UniformParticleGenerator::UniformParticleGenerator(Vector3 vel,Vector3 pos):ParticleGenerator(pos,vel) {

	


}
UniformParticleGenerator::~UniformParticleGenerator() {

} 

std::list<Particle*> UniformParticleGenerator::generateParticles() {
	//Crear lista nueva desde aqui
	std::list<Particle*> lPart;
	float rx = rand() % 50;
	//float ry = rand() % 50;
	float rz = rand() % 50;

	Particle* part = new Particle({rx,60,30}, { 5,10,-10 }, 1, { 0,-7,0 }, { 0,0.6,1,1 }, 1,0);
	lPart.push_back(part);
	


	return lPart;
}
