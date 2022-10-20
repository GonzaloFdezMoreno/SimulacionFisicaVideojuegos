#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int npart) {

	uPG=new UniformParticleGenerator({ 2,2,0 }, { 1,2,1 });
	_particles_generators.push_back(uPG);
	/*Particle* pa = new Particle({ 0,30,0 }, { 0,-3,0 }, 1, { 3,10,7 }, { 0,0.6,1,1 }, 3);
	_particles.push_back(pa);*/
	//gPG = new GaussianParticleGenerator({ 2,2,0 }, { 1,2,1 });
	nump = npart;

}
ParticleSystem::~ParticleSystem() {


}

void ParticleSystem::update(double t) {

	
	for (int i = 0; i < nump; i++) {
		
		srand(time(NULL));
		float rx = rand() % 50;
		//float ry = rand() % 4 + 1;
		float rz = rand() % 50;

		float vx = rand() % 10;
		float vy = rand() % 10;
		float vz = rand() % 10;

		float negx = rand() % 10 + 1;
		float negy = rand() % 10 + 1;
		float negz = rand() % 10 + 1;

		int tamrnd = rand() % 4 + 1;

		if (negx < 5) {
			vx = vx - (2 * vx);
		}
		else if (negy < 5) {
			vy = vy - (2 * vy);
		}
		else if (negz < 5) {
			vz = vz - (2 * vz);
		}

		std::list<Particle*> pa = uPG->generateParticles({ rx,0,rz }, { vx,vy,vz });

		for (auto pl : pa) {
			_particles.push_back(pl);
			
		}
		
	}

	for (auto pt : _particles) {
		pt->integrate(t);
		if (pt->die) {
			pt->~Particle();
		}
	}
	
}
//ParticleGenerator* ParticleSystem::getParticleGenerator(string nombre) {
//
//}
void ParticleSystem::generateFireworkSystem() {

}