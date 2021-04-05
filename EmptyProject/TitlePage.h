#pragma once
#include "DXUT.h"
#include "Page.h"

class TitlePage :public Page
{
public:

	TitlePage();
	virtual ~TitlePage();
	void Render() override;
	void Update() override;

	LPDIRECT3DTEXTURE9* titleTex;
	LPDIRECT3DTEXTURE9* gameStartTex;
	LPDIRECT3DTEXTURE9* gameIntroductionTex;
	LPDIRECT3DTEXTURE9* rankingTex;
	LPDIRECT3DTEXTURE9* creditTex;
	LPDIRECT3DTEXTURE9* exitTex;
	LPD3DXSPRITE sprite;


};

