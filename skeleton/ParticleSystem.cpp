#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int npart) {

	/*uPG = new UniformParticleGenerator({2,2,0}, {1,2,1});
	_particles_generators.push_back(uPG);*/

	fireworkSysGen = new FireworkGenerator({ 0,20,0 }, { 0,100,0 });
	//_particles_generators.push_back(fireworkSysGen);

	/*Particle* pa = new Particle({ 0,30,0 }, { 0,-3,0 }, 1, { 3,10,7 }, { 0,0.6,1,1 }, 3);
	_particles.push_back(pa);*/
	gPG = new GaussianParticleGenerator({ 2,2,0 }, { 1,2,1 });
	_particles_generators.push_back(gPG);

	nump = npart;
	srand(time(NULL));



}
ParticleSystem::~ParticleSystem() {


}

void ParticleSystem::update(double t) {

	
	//for (int i = 0; i < 1; i++) {
		
		
		
		

		//std::list<Particle*> pa = uPG->generateParticles();
		std::list<Particle*> pa = gPG->generateParticles();

		for (auto pl : pa) {
			_particles.push_back(pl);
			
		}

		if (activate) {
			generateFireworkSystem();
		}
	//}

	for (auto pt = _particles.begin(); pt!=_particles.end();) {
		
			(*pt)->update(t);
		
		

		if (( * pt)->die) {
			std::list<Particle*> exp = (*pt)->explode();
			for (auto pl : exp) {
				_particles.push_back(pl);

			}
			delete *pt;
			pt=_particles.erase(pt);
		}
		else {
			pt++ ;
		}

	}

	//for (auto fw = _fireworks.begin(); fw != _fireworks.end();) {
	//	//if ((*fw)->isFire) {
	//		(*fw)->update(t);
	//	//}
	//	

	//	if ((*fw)->explodes && !(*fw)->ended) {
	//		std::list<Particle*> exp = (*fw)->explode();
	//		for (auto pt : exp) {
	//			_particles.push_back(pt);

	//		}
	//		//std::list<Particle*> fir;
	//		/*GaussianParticleGenerator* genF = new GaussianParticleGenerator({20,20,20}, { 3,3,3 });
	//		for (int i = 0; i < 25; i++) {
	//			std::list<Particle*>ep = (genF->generateParticles());
	//			for (auto prt : ep) {
	//				_particles.push_back(prt);

	//			}

	//		}*/
	//	}
	//	if ((*fw)->die) {
	//		
	//		delete* fw;
	//		fw = _fireworks.erase(fw);
	//	}
	//	
	//	else {
	//		fw++;
	//	}

	//}

	
}
//ParticleGenerator* ParticleSystem::getParticleGenerator(string nombre) {
//
//}
void ParticleSystem::generateFireworkSystem() {
	//std::list<Firework*> fir = fireworkSysGen->generateParticles();
	std::list<Particle*> fir = fireworkSysGen->generateParticles();

	for (auto pl : fir) {

		//_fireworks.push_back(pl);
		_particles.push_back(pl);

	}
	activate = false;
   
}

