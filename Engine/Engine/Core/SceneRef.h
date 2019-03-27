#ifndef SCENE_REF_H_
#define SCENE_REF_H_

#include "Types.h"

class Scene;

class SceneRef
{
private:
	Scene* scene;
	u64 sceneID;
	u64 topID;

public:
	inline SceneRef() :
		scene(nullptr),
		sceneID(U64_MAX),
		topID(U64_MAX)
	{
		// Nothing interesting to do here
	}
	
	inline SceneRef(Scene* parentScene, u64 sID, u64 tID = U64_MAX) :
		scene(parentScene),
		sceneID(sID),
		topID(tID)
	{
		// Nothing interesting to do here
	}
	
	inline ~SceneRef()
	{
		// Nothing interesting to do here
	}

	inline Scene* GetScene()   { return scene; }
	inline u64    GetSceneID() { return sceneID; }
	inline u64    GetTopID()   { return topID; }

	inline void Move(u64 sID) { sceneID = sID; }
	inline void Move(u64 sID, u64 tID) { sceneID = sID; topID = tID; }
	inline void Move(Scene* newParentScene, u64 sID, u64 tID) { scene = newParentScene; sceneID = sID; topID = tID; }
};

#endif