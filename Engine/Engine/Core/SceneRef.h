#ifndef SCENE_REF_H_
#define SCENE_REF_H_

#include "Types.h"

class Scene;

class SceneRef
{
private:
	Scene* scene;
	u64 index;
	u64 sceneID;
	u64 topID;

	friend class Scene;

public:
	inline SceneRef() :
		scene(nullptr),
		index(U64_MAX),
		sceneID(U64_MAX),
		topID(U64_MAX)
	{
		// Nothing interesting to do here
	}
	
	inline SceneRef(Scene* parentScene, u64 ind, u64 sID, u64 tID = U64_MAX) :
		scene(parentScene),
		index(ind),
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
	inline u64    GetIndex()   { return index; }
	inline u64    GetSceneID() { return sceneID; }
	inline u64    GetTopID()   { return topID; }
};

#endif
