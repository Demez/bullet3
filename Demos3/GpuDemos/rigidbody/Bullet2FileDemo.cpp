
#include "Bullet2FileDemo.h"
#include "BulletDataExtractor.h"
#include "GpuRigidBodyDemoInternalData.h"
#include "OpenGLWindow/GLInstancingRenderer.h"

Bullet2FileDemo::Bullet2FileDemo()
{
	m_loader = 0;
}
Bullet2FileDemo::~Bullet2FileDemo()
{
	delete 	m_loader;
}

void Bullet2FileDemo::setupScene(const ConstructionInfo& ci)
{
	b3Assert(ci.m_instancingRenderer);
#ifdef __APPLE__
//MPR doesn't work yet on Apple, so use a simpler test file
//see bool useMpr at the top of
//src/Bullet3OpenCL/NarrowphaseCollision/b3ConvexHullContact.cpp 


	const char* fileName="data/testFile.bullet";
#else
	const char* fileName="data/testFileFracture.bullet";
#endif
	FILE* f = 0;

	const char* prefix[]={"./","../","../../","../../../","../../../../"};
	int numPrefixes = sizeof(prefix)/sizeof(const char*);
	char relativeFileName[1024];

	for (int i=0;!f && i<numPrefixes;i++)
	{
		sprintf(relativeFileName,"%s%s",prefix[i],fileName);
		f = fopen(relativeFileName,"rb");
	}
	if (f)
	{
		fclose(f);
		createScene(*ci.m_instancingRenderer,*m_data->m_np,*m_data->m_rigidBodyPipeline,relativeFileName);
	}
//	m_loader = new b3BulletDataExtractor(*ci.m_instancingRenderer,*m_data->m_np,*m_data->m_rigidBodyPipeline);
//	m_loader->convertAllObjects(bulletFile);

	b3Vector3 pos=b3MakeVector3(-20,10,0);
	ci.m_instancingRenderer->setCameraTargetPosition(pos);
	ci.m_instancingRenderer->setCameraDistance(10);
}
