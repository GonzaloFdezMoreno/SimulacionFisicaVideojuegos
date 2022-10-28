#include "Particle.h"
#include <time.h>

Particle::Particle(Vector3 pos,Vector3 vel,float damping,Vector3 accelerate,Vector4 color,int tam) {
	veloc = vel;
	posit = physx::PxTransform(pos.x, pos.y, pos.z);
	damp = damping;
	accel = accelerate;
	renderItemPart = new RenderItem(CreateShape(physx::PxSphereGeometry(tam)), &posit, color);
	//RegisterRenderItem(renderItemPart);

	//srand(time(NULL));

}

Particle::~Particle() {
	   // delete renderItemPart;
		
		DeregisterRenderItem(renderItemPart);
		
		renderItemPart = nullptr;
	
}
void Particle::update(double t) {
	//velocidad constante
	posit = physx::PxTransform(posit.p.x + veloc.x * t, posit.p.y + veloc.y * t, posit.p.z + veloc.z * t);
	//con damping
	veloc += accel * t;
	veloc *= pow(damp, t);
	timeAlive++;
	
	if (timeAlive > 500) {

		die = true;
	}


}

