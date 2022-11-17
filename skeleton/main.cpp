#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>
#include "Particle.h"
#include "Mshot.h"
#include "Plane.h"
#include "ParticleSystem.h"
#include "Firework.h"




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
Plane* plan = NULL;
ParticleSystem* psys = NULL;
//Firework* fwo = NULL;
std::vector<Firework*> fwoVec;


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
	plan = new Plane({ 0,-100,0 }, { 0,1,0,1 });

	psys = new ParticleSystem(2);

	
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

	if(psys!=NULL)
	psys->update(t);

	//mejor crear el generador de fuegos
	
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
		bullets.push_back(new Mshot(0.4, { GetCamera()->getDir() * 250 }, { GetCamera()->getEye() }, 0.99, { 0,-0.5,0 }, {0.3,0.4,0.5,1},2));
		
		break;
	case 'L': {
		//laser
		bullets.push_back(new Mshot(0.1, { GetCamera()->getDir() * 1000 }, { GetCamera()->getEye() }, 0.99, { 0,0,0 },{1,0,0,1},2));
		break; 
	}
	case 'C':
	{
		//canyon
		bullets.push_back(new Mshot(5, {GetCamera()->getDir() *150 }, {GetCamera()->getEye() }, 0.99, { 0,-2.0,0 },{0.7,0.6,0.2,1},5));
		break;
	}
	case 'F':
	{
		//bfuego
		//bullets.push_back(new Mshot(1, { GetCamera()->getDir() * 100 }, {GetCamera()->getEye() }, 0.9, { 0,0.5,0 },{0.8,0.4,0,1},5));

		//fuegos artificiales
		psys->activate = true;
		break;
	}
	case 'P':
	{
		//pompas
		
			srand(time(NULL));
			//aceleraciones aleatorias 
			float rx = rand() % 2+0;
			float ry = rand() % 2+1;
			float rz = rand() % 2+0;

			//para poner aceleraciones positivas y negativas  
			float negx = rand() % 10+1;
			float negy = rand() % 10+1;
			float negz = rand() % 10+1;

			int tamrnd = rand() % 4 + 1;

			if (negx < 5) {
				rx=rx-(2*rx);
			}
			else if (negy < 5) {
				ry=ry-(2*ry);
			}
			else if (negz < 5) {
				rz=rz-(2*rz);
			}

			bullets.push_back(new Mshot(0.1, {GetCamera()->getDir()*70 }, { GetCamera()->getEye() }, 0.7, { rx/10,ry/10,rz/10},{0,0,1,1},tamrnd));
		
		break;
	}

	case 'G':
		if (!psys->getgrav) {
			psys->getgrav = true;
		}
		
		break;
	case 'T':
		if (!psys->getwind) {
			psys->getwind = true;
			psys->createwindAreaForce();
		}
		
		break;
	
	case 'U':
		if (!psys->getexplosion) {
			psys->getexplosion = true;
			psys->createExplosionForce();
		}
		
		break;
	
	case 'H':
		if (!psys->getWhirl) {
			psys->getWhirl = true;
			
		}
		
		break;
	case 'X':
		//desactivar
		if (psys->getgrav) {
			psys->getgrav = false;
		}
		if (psys->getwind) {
			psys->getwind = false;
		}
		if (!psys->getexplosion) {
			psys->getexplosion = false;
		}
		if (psys->getWhirl) {
			psys->getWhirl = false;
		}
		psys->eraseForces();

		break;


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