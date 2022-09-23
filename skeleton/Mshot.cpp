#include "Mshot.h"

Mshot::Mshot(double masa,Vector3 vel,Vector3 pos,float damping,Vector3 accelerate){

	mass = masa;

	veloc = vel;
	posit = physx::PxTransform(pos.x, pos.y, pos.z);
	damp = damping;
	accel = accelerate;
	renderItemPart = new RenderItem(CreateShape(physx::PxSphereGeometry(5)), &posit, { 0,0,1,1 });
}

Mshot::~Mshot() {
	renderItemPart = nullptr;
	DeregisterRenderItem(renderItemPart);
}

void Mshot::integrate(double t) {
	//velocidad constante
	posit = physx::PxTransform(posit.p.x + veloc.x * t, posit.p.y + veloc.y * t, posit.p.z + veloc.z * t);
	//con damping

	veloc = mass*accel;
	veloc *= pow(damp, t);

}