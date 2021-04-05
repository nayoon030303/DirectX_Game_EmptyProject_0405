#pragma once
#include "DXUT.h"
#include "Player.h"

class GameSystem
{
public:
	GameSystem();
	virtual ~GameSystem();

	void Render();
	void Update();
	void FloodFill(int index);
	void SetProperty();
	void Load();


	Player player;

	LPDIRECT3DTEXTURE9* backgroundTex;
	LPDIRECT3DTEXTURE9* maskTex;
	LPDIRECT3DTEXTURE9* dotTex;
	LPD3DXSPRITE sprite;

};

