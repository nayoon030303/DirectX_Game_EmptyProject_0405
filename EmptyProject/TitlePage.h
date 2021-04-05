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
	LPD3DXSPRITE sprite;


};

