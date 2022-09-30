#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>
#include "Particle.h"
#include "Mshot.h"




using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

Particle* partic = NULL;
std::vector<Mshot*> bullets ;


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	//Añadir elementos
	//partic = new Particle({ 0,50,0 },{ -10,20,0 }, 0.9, {0,-9.8,0});
	
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	for(auto b:bullets)
	//partic->integrate(t);
	b->integrate(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);
	

	switch(toupper(key))
	{
	case 'B':
		//pistola
		bullets.push_back(new Mshot(2, { GetCamera()->getDir()*2500}, {GetCamera()->getEye()}, 0.99, {0,-0.5,0}));
		
		break;
	case 'L': {
		//laser
		bullets.push_back(new Mshot(0.1, { GetCamera()->getDir() * 10000 }, { GetCamera()->getEye() }, 0.99, { 0,0,0 }));
		break; 
	}
	case 'C':
	{
		//canyon
		bullets.push_back(new Mshot(100, { GetCamera()->getDir().x,GetCamera()->getDir().y *2000,GetCamera()->getDir().z *1000 }, {GetCamera()->getEye() }, 0.99, { 0,-2.0,0 }));
		break;
	}
	case 'F':
	{
		//bfuego
		bullets.push_back(new Mshot(1, { GetCamera()->getDir() * 100 }, {GetCamera()->getEye() }, 0.9, { 0,0.6,0 }));
		break;
	}
	case 'G':
	{
		int i = 5;
		
		for (int j = 0; j < i; j++) {
			srand(time(NULL));
			float r = rand() % 10+1;
			
			//pompas
			bullets.push_back(new Mshot(1, { GetCamera()->getDir().x*r,GetCamera()->getDir().y * 10,GetCamera()->getDir().z + r }, { GetCamera()->getEye() }, 0.9, { 0,-0.2,0 }));
		}
		break;
	}

	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}