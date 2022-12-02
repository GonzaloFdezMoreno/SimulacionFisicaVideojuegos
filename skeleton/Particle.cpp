#include "Particle.h"
#include <time.h>

Particle::Particle(Vector3 pos,Vector3 vel,float damping,Vector3 accelerate,Vector4 color,int tam,double mass,bool box) {
	veloc = vel;
	posit = physx::PxTransform(pos.x, pos.y, pos.z);
	damp = damping;
	accel = accelerate;
	masa = mass;
	inv_mass = 1 / mass;
	cubo = box;
	if(!cubo)
	    renderItemPart = new RenderItem(CreateShape(physx::PxSphereGeometry(tam)), &posit, color);
	else
		renderItemPart = new RenderItem(CreateShape(physx::PxBoxGeometry(tam,tam,tam)), &posit, color);
	//al principio ninguna fuerza actua
	force = { 0,0,0 };

	//RegisterRenderItem(renderItemPart);
	
	//srand(time(NULL));

}

Particle::~Particle() {
	   // delete renderItemPart;
		
		DeregisterRenderItem(renderItemPart);
		
		renderItemPart = nullptr;

		
	
}
void Particle::update(double t) {

	if (masa <= 0) {
		inv_mass = 0;
	};

		//velocidad constante
		posit = physx::PxTransform(posit.p.x + veloc.x * t, posit.p.y + veloc.y * t, posit.p.z + veloc.z * t);
		//con damping
		
		veloc += ((inv_mass*force)+accel) * t;
		
		veloc *= pow(damp, t);
		

	timeAlive++;
	
	//if (timeAlive > 500) {
	/*if (timeAlive > 5000) {

		die = true;
	}*/

	noForce();
}

