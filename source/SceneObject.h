#ifndef __SCENEOBJECT_H__
#define __SCENEOBJECT_H__


#include <gccore.h>

class SceneObject {
	public:
	    SceneObject();
		SceneObject(f32, f32, f32, f32, f32, f32, GXTexObj);
		void Update();
		void Draw(Mtx44);
		f32 GetMaxX();
		f32 GetMaxY();
		f32 GetMinX();
		f32 GetMinY();
		void SetBouncy(bool);
		bool GetBouncy();
	private:
		f32 x, y, z, w, h, d;
		bool bouncy;
		GXTexObj tex;
	protected:
};

#endif