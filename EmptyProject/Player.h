#pragma once
#include "DXUT.h"
#include <vector>

using namespace std;

class Player
{
public:
	Player();
	virtual ~Player();
	void Render();
	void Update();
	void playerMove(int x, int y);

	int px;
	int py;
	int nx;
	int ny;
	int speed;
	int score;
	int hp;
	bool press; 
	bool startSetProperty;
	D3DXVECTOR2 startPos;
	//enum  PlayerState
	//{
	//	ON_EDGE,
	//	VISITING
	//};
	bool VISITING;
	vector<D3DXVECTOR2> visitingPos;

	LPDIRECT3DTEXTURE9* playerTex;
	LPD3DXSPRITE sprite;
};

