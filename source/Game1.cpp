#include "Game1.h"

Game1::Game1() {
	
}

void Game1::Initialize() {
	GX_ClearVtxDesc();
    	GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
    	GX_SetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
	
	GX_SetNumChans(1);
	GX_SetNumTexGens(1);
	GX_SetTevOrder (GX_TEVSTAGE0, GX_TEXCOORD0,GX_TEXMAP0, GX_COLOR0A0);
        GX_SetTevOp (GX_TEVSTAGE0, GX_MODULATE);        
        GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);

	camera = new Camera( Game::gxrmode, (guVector){0, 2, -5}, (guVector){0,1,0}, (guVector){0,2,0});
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
	guMtxTransApply(model, model, 0,  0, 0);
	guMtxConcat(model, view, modelview);
	GX_LoadPosMtxImm(modelview, GX_PNMTX0);
	GX_LoadTexObj(&textures[0], GX_TEXMAP0);
	
	float width, height, depth;

	width = 30.0f;
	height = 12.5f;
	depth = 25.0f;
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
