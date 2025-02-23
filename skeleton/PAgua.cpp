#include "PAgua.h"
#include <time.h>



PAgua::PAgua(Vector3 pos, Vector3 vel, float damping, Vector3 accelerate, Vector4 color, float tam,float mass):Particle(pos,vel,damping,accelerate,color,tam,mass,false,500) {
	
	//isFire = true;
	
}

PAgua::~PAgua() {

}


void PAgua::update(double t){
	if(posit.p.y<0){
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

std::list<Particle*> PAgua::explode() {
	std::list<Particle*> pag;
	for (int i = 0; i < 3; i++) {


		auto vx = std::normal_distribution<float>{ 5, 3 };
		auto vy = std::normal_distribution<float>{ 10, 1 };
		auto vz = std::normal_distribution<float>{ 5, 2 };

		float negx = rand() % 10 + 1;
		//float negy = rand() % 10 + 1;
		float negz = rand() % 10 + 1;

		//int tamrnd = rand() % 4 + 1;


		Vector3 velc = { vx(rnd),vy(rnd),vz(rnd) };

		if (negx < 5) {
			velc.x = -velc.x;
		}
		
		else if (negz < 5) {
			velc.z = -velc.z;
		}

		/*if (velc.y < 0) {
			velc.y *= 2;
		}*/
		//velc.y = rand() % 3 + 10;
		

		//srand(time(NULL));
		Particle* prt = new Particle(posit.p, velc * 2, 0.5, { 0,-1,0 }, { 0,1,1,1 }, 0.3, 0, false,75);
		pag.push_back(prt);



	}
	return pag;
}

