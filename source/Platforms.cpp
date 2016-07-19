#include "Platforms.h"

Platform::Platform() {

}

Platform::Platform(f32 x, f32 y, f32 z, f32 w, f32 h, f32 d, GXTexObj tex) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	this->h = h;
	this->d = d;
	this->tex = tex;
	this->bouncy = false;
}

void Platform::Update() {

}

void Platform::SetBouncy(bool b) {
	this->bouncy = b;
}

bool Platform::GetBouncy() {
	return this->bouncy;
}

void Platform::Draw(Mtx44 view) {
	Mtx44 model, modelview;
	guMtxIdentity(model);
	guMtxTransApply(model, model, this->x, this->y, this->z);
	guMtxConcat(model, view, modelview);
	GX_LoadPosMtxImm(modelview, GX_PNMTX0);
	GX_InitTexObjWrapMode(&this->tex, GX_REPEAT, GX_REPEAT);
	
	GX_LoadTexObj(&this->tex, GX_TEXMAP0);

GX_InvalidateTexAll();
	
	f32 width, height, depth;
	width = this->w / 2.0f;
	height = this->h / 2.0f;
	depth = 0;
	
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(-width, height, depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(0, 0);
		GX_Position3f32(width, height, depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(1, 0);
		GX_Position3f32(width, -height, depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(1, 1);
		GX_Position3f32(-width, -height, depth);
		GX_Color4u8(255, 255, 255, 255);
		GX_TexCoord2f32(0, 1);
	GX_End();
}

f32 Platform::GetMaxX() { return this->x + (this->w / 2.0f); }
f32 Platform::GetMaxY() { return this->y + (this->h / 2.0f); }
f32 Platform::GetMinX() { return this->x - (this->w / 2.0f); }
f32 Platform::GetMinY() { return this->y - (this->h / 2.0f); }
