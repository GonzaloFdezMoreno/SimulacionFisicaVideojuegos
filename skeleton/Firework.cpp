#include "Firework.h"
#include <time.h>



Firework::Firework(Vector3 pos, Vector3 vel, float damping, Vector3 accelerate, Vector4 color, int tam):Particle(pos,vel,damping,accelerate,color,tam,0,false,500) {
	
	//isFire = true;
	
}

Firework::~Firework() {

}


void Firework::update(double t){
	if(timeAlive>500){
		//explode();
		die = true;
	}
	/*if (timeAlive > 500) {
		
	}*/
	posit = physx::PxTransform(posit.p.x + veloc.x * t, posit.p.y + veloc.y * t, posit.p.z + veloc.z * t);
	//con damping

	veloc += accel * t;
	veloc *= pow(damp, t);
	timeAlive++;

}

std::list<Particle*> Firework::explode() {
	std::list<Particle*> fir;
	//UniformParticleGenerator* genF = new UniformParticleGenerator(posit.p,{3,3,3});
	
	for (int i = 0; i < 100; i++) {
		//std::list<Particle*>ep=(genF->generateParticles());
		//for (auto prt : ep) {

		/*float vx = rand() % 50;
		float vy = rand() % 50;*/
		//float vz = rand() % 50;

		auto vx = std::normal_distribution<float>{ 10, 20 }; //10,1
		auto vy = std::normal_distribution<float>{0, 1};
		auto vz = std::normal_distribution<float>{ 15, 11 };

		float negx = rand() % 10 + 1;
		float negy = rand() % 10 + 1;
		float negz = rand() % 10 + 1;

		//int tamrnd = rand() % 4 + 1;

		
		Vector3 velc = { vx(rnd),vy(rnd),vz(rnd)};

		if (negx < 5) {
			velc.x = -velc.x;
		}
		else if (negy < 5) {
			velc.y = -velc.y;
		}
		else if (negz < 5) {
			velc.z = -velc.z;
		}
	
		//srand(time(NULL));
		Particle* prt = new Particle(posit.p, velc*2, 0.5, { 0,-1,0 }, { 0,1,1,1 }, 1,0,false,300);
			fir.push_back(prt);

		//}
		
	}

	ended = true;
	timeAlive = 0;
	return fir;
}

