#ifndef __GAME1_H__
#define __GAME1_H__

#include "Game.h"
#include "Camera.h"

#include "textures_tpl.h"
#include "textures.h"

#include "Platforms.h"
#include "Player.h"
#include "Enemy.h"
#include "SceneObject.h"

class Game1 : public Game {
	public:
		Game1();
		void Initialize();
		void LoadContent();
		void Run();
		void Update();
		void Draw();
		Camera* GetCamera();
		void DrawCube(Mtx44);

	private:
		Camera * camera;
		std::vector<GXTexObj> textures;
		std::vector<Platform*> platforms;
		std::vector<SceneObject*> sceneObjects;


	protected:
};

#endif
