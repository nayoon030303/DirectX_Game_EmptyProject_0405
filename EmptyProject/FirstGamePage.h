#pragma once
#include "DXUT.h"
#include "Page.h"
#include "GameSystem.h"

class FirstGamePage:public Page
{
public:
	FirstGamePage();
	virtual ~FirstGamePage();

	void Render() override;
	void Update() override;


	ID3DXFont* font;
	GameSystem gameSystem;
	LPDIRECT3DTEXTURE9* background;
	LPD3DXSPRITE sprite;
};

