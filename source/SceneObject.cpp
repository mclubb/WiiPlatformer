#include "SceneObject.h"

SceneObject::SceneObject() {

}

SceneObject::SceneObject(f32 x, f32 y, f32 z, f32 w, f32 h, f32 d, GXTexObj tex) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	this->h = h;
	this->d = d;
	this->tex = tex;
	this->bouncy = false;
}

void SceneObject::Update() {

}

void SceneObject::SetBouncy(bool b) {
	this->bouncy = b;
}

bool SceneObject::GetBouncy() {
	return this->bouncy;
}

void SceneObject::Draw(Mtx44 view) {
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

f32 SceneObject::GetMaxX() { return this->x + (this->w / 2.0f); }
f32 SceneObject::GetMaxY() { return this->y + (this->h / 2.0f); }
f32 SceneObject::GetMinX() { return this->x - (this->w / 2.0f); }
f32 SceneObject::GetMinY() { return this->y - (this->h / 2.0f); }
