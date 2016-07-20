#include "Game1.h"

Game1::Game1() {
	
}

void Game1::Initialize() {
	camera = new Camera( Game::gxrmode, (guVector){3, 2, 5}, (guVector){0,1,0}, (guVector){3,2,0});
}

void Game1::LoadContent() {

	// Load the textures
	TPLFile texturesTPL;

	GXTexObj _background;
	GXTexObj _tile2;
	TPL_OpenTPLFromMemory(&texturesTPL, (void *)textures_tpl, textures_tpl_size);
	TPL_GetTexture(&texturesTPL, background, &_background);
	TPL_GetTexture(&texturesTPL, tiletwo, &_tile2);
	textures.push_back(_background);
	textures.push_back(_tile2);

	platforms.push_back(new Platform(0, 0, 0, 1, 1, 0, textures[1]));
	platforms.push_back(new Platform(1, 0, 0, 1, 1, 0, textures[1]));
	platforms.push_back(new Platform(2, 0, 0, 1, 1, 0, textures[1]));
	platforms.push_back(new Platform(3, 0, 0, 1, 1, 0, textures[1]));
	platforms.push_back(new Platform(4, 0, 0, 1, 1, 0, textures[1]));
	platforms.push_back(new Platform(5, 0, 0, 1, 1, 0, textures[1]));
	platforms.push_back(new Platform(6, 0, 0, 1, 1, 0, textures[1]));
	platforms.push_back(new Platform(7, 0, 0, 1, 1, 0, textures[1]));
}

void Game1::Update() {
	Game::Update();

	// Update goes here
	camera->Update();

}


void Game1::Draw() {
	// Draw goes here
	camera->Setup3D();
	
	DrawCube(*camera->GetView());

	int i = 0;
	for(i = 0; i < (int)platforms.size(); i++) {
		platforms[i]->Draw(*camera->GetView());
	}
	
	Game::Draw();
}

void Game1::DrawCube(Mtx44 view) {
	Mtx44 model, modelview;
	guMtxIdentity(model);
	guMtxTransApply(model, model, 0,  2, 0);
	guMtxConcat(model, view, modelview);
	GX_LoadPosMtxImm(modelview, GX_PNMTX0);
	GX_LoadTexObj(&textures[0], GX_TEXMAP0);
	
	float width, height, depth;

	width = 30.0f;
	height = 12.5f;
	depth = -25.0f;
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(-width, -height, depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(0,1);  

		GX_Position3f32(width, -height, depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(1,1);

		GX_Position3f32(width, height, depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(1,0);

		GX_Position3f32(-width, height, depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(0,0);
	GX_End();
}

Camera* Game1::GetCamera() {
	return this->camera;
}

void Game1::Run() {

	while(Game::IsRunning()) {
		Update();
		Draw();
	}
}
