#include "ObjectManager.h"
#include "RenderEngine.h"

void ObjectManager::Add(GameObject targetObject)
{
	if (targetObject.isLightSource == true)
		targetObject.mesh.targetShader = &RenderEngine::Get()->shaderIDs[1];
	else
		targetObject.mesh.targetShader = &RenderEngine::Get()->shaderIDs[1];
	objectQueue.push_back(targetObject);
}

void ObjectManager::Update()
{
	for (int i = 0; i < objectQueue.size(); i++) {
		objectQueue[i].Update();
		RenderEngine::Get()->BindTexture(objectQueue[i].targetTexture);
		if (&objectQueue[i].mesh != nullptr && objectQueue[i].mesh.targetShader != nullptr) {
			glUseProgram(*objectQueue[i].mesh.targetShader);
			RenderEngine::Get()->RenderMesh(&objectQueue[i].mesh);
		}
			
	}
}
