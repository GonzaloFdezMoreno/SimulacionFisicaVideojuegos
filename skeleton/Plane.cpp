#include "Plane.h"

Plane::Plane(Vector3 pos,Vector4 color) {
	
	posit = physx::PxTransform(pos.x, pos.y, pos.z);
	
	renderItemPart = new RenderItem(CreateShape(physx::PxBoxGeometry(1000,1,1000)), &posit, color);

}

Plane::~Plane() {
	renderItemPart = nullptr;
	DeregisterRenderItem(renderItemPart);

}
