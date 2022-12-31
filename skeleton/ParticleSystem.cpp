#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int npart) {

	uPG = new UniformParticleGenerator({2,2,0}, {1,2,1});
	_particles_generators.push_back(uPG);

	fireworkSysGen = new FireworkGenerator({ 0,20,0 }, { 0,100,0 });
	//_particles_generators.push_back(fireworkSysGen);

	/*Particle* pa = new Particle({ 0,30,0 }, { 0,-3,0 }, 1, { 3,10,7 }, { 0,0.6,1,1 }, 3);
	_particles.push_back(pa);*/
	gPG = new GaussianParticleGenerator({ 2,2,0 }, { 1,2,1 });
	_particles_generators.push_back(gPG);
	 
	regfor = new ParticleForceRegistry();
	
	nump = npart;
	srand(time(NULL));

	gforceGen = new GravityForceGenerator({ 0,-9.8,0 });
	whForceGen = new WhirlpoolForceGenerator(1, 0.5, { 20,100,20 },0.4);


}
ParticleSystem::~ParticleSystem() {


}

void ParticleSystem::update(double t) {
	
	
	//for (int i = 0; i < 1; i++) {
		
		
	
		

		std::list<Particle*> pa = uPG->generateParticles();
		//std::list<Particle*> pa = gPG->generateParticles();

		for (auto pl : pa) {
			_particles.push_back(pl);
			
		}

		if (activate) {
			generateFireworkSystem();
		}

		if (create) {
			//generateSpring();
			generateMultiSpring();
		}
		if (flotar) {
			flota();
		}
	//}

		regfor->updateForces(t);

	for (auto pt = _particles.begin(); pt!=_particles.end();) {
		if (getgrav) {
			regfor->addRegistry(gforceGen, (*pt));
		}
		if (getwind) {
			if(wforceGen!=nullptr)
			regfor->addRegistry(wforceGen, (*pt));
		}
		if (getexplosion) {
			if(expForceGen!=nullptr)
			regfor->addRegistry(expForceGen, (*pt));
		}
		if (getWhirl) {
			regfor->addRegistry(whForceGen, (*pt));
		}

		
		(*pt)->update(t);
		 
		

		if (( * pt)->die) {
			std::list<Particle*> exp = (*pt)->explode();
			for (auto pl : exp) {
				_particles.push_back(pl);

			}
			regfor->deleteParticleRegistry((*pt));
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

void ParticleSystem::createExplosionForce() {
	
	expForceGen = new ExplosionForceGenerator({ 30,90,20 }, 30,2);
}

void ParticleSystem::createwindAreaForce() {
	wforceGen = new WindForceGenerator({ 1,0,0 }, 0.5, 0);
}

void ParticleSystem::generateSpring() {
	//con punto fijo
	Particle* panch = new Particle({ 50,50,50 }, { 0,-5,0 }, 0.9, { 0,-9.8,0 }, { 0,1,1,1 }, 3, 2,false,0);
	AnchorForceGen* anfor = new AnchorForceGen(1, 10, { 50,70,50 });
	regfor->addRegistry(anfor, panch);
	_particles.push_back(panch);
	create = false;

	//2 moviles
	Particle* par1 = new Particle({ 20,50,20 }, { 0,0,0 }, 0.9, { 0,0,0 }, { 0,1,1,1 }, 3, 1,false,0);
	Particle* par2 = new Particle({ -10,50,20 }, { 0,0,0 }, 0.9, { 0,0,0 }, { 0,1,1,1 }, 3, 2,false,0);

	SpringForceGen* sf1 = new SpringForceGen(3, 20, par2);
	SpringForceGen* sf2 = new SpringForceGen(3, 20, par1);

	regfor->addRegistry(sf1, par1);
	regfor->addRegistry(sf2, par2);

	_particles.push_back(par1);
	_particles.push_back(par2);
}

void ParticleSystem::flota() {
	Particle* paflo = new Particle({ 70,0,-70 }, { 0,0,0 }, 0.9, { 0,-9.8,0 }, { 0,1,1,1 }, 5, 5, false,0);
	BuoyancyForceGen* flofor = new BuoyancyForceGen(5,3,10);
	regfor->addRegistry(flofor, paflo);
	_particles.push_back(paflo);
	flotar = false;
}

//void ParticleSystem::eraseForces() {
//	
//	wforceGen = nullptr;
//	expForceGen = nullptr;
//}




void ParticleSystem::generateMultiSpring() {
	//con punto fijo
	Particle* panch = new Particle({ 50,65,50 }, { 0,0,0 }, 0.9, { 0,-2,0 }, { 0,1,1,1 }, 1, 2, false, 0);
	AnchorForceGen* anfor = new AnchorForceGen(1, 10, { 50,70,50 });
	regfor->addRegistry(anfor, panch);
	_particles.push_back(panch);
	create = false;
	vector<Particle*> pcuerda(5);

	for (int j = 0; j < pcuerda.size(); j++) {
		float newy = (60 - (j*5));
		pcuerda[j] = new Particle({ 50,newy,50}, {0,0,0}, 0.9, {0,0,0}, {0,1,1,1}, 1, 2, false, 0);
		_particles.push_back(pcuerda[j]);
	}



	for (int i = 0; i < pcuerda.size(); i++) {
		if (i == 0) {
			SpringForceGen* sfX = new SpringForceGen(10, 15, panch);
			regfor->addRegistry(sfX, pcuerda[i]);

		}
		else {
			SpringForceGen* sfX = new SpringForceGen(10, 15*(i+1), panch);
			regfor->addRegistry(sfX, pcuerda[i]);
		}
	}
}
