#include "DXUT.h"
#include "GameSystem.h"
#include "global.h"
#include <stack>

using namespace std;

GameSystem::GameSystem()
{
	Load();

	player = new Player();

	//reset Map
	for (int i = 0; i < WIDTH * HEIGHT; ++i)
	{
		map[i] = MAP_PROPERTY_EMPTY;
		binaryMap[i] = MAP_PROPERTY_EMPTY;
	}
	for (int y = 0; y < HEIGHT; ++y)
	{
		map[y * WIDTH + 0] = MAP_PROPERTY_EDGE;
		map[y * WIDTH + (WIDTH-1)] = MAP_PROPERTY_EDGE;
		binaryMap[y * WIDTH + 0] = MAP_PROPERTY_VISIT;
		binaryMap[y * WIDTH + (WIDTH - 1)] = MAP_PROPERTY_VISIT;
	}
	for (int x = 0; x < WIDTH; ++x)
	{
		map[0 * WIDTH + x] = MAP_PROPERTY_EDGE;
		map[(HEIGHT-1) * WIDTH + x] = MAP_PROPERTY_EDGE;
		binaryMap[0 * WIDTH + x] = MAP_PROPERTY_VISIT;
		binaryMap[(HEIGHT - 1) * WIDTH + x] = MAP_PROPERTY_VISIT;
	}
}

GameSystem::~GameSystem()
{
	delete player;
	sprite->Release();
	(*backgroundTex)->Release();
	(*maskTex)->Release();
	(*dotTex)->Release();
}

void GameSystem::Update()
{
	player->Update();
	if (player->startSetProperty)
		SetProperty();
}

void GameSystem::Render()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXVECTOR3 pos(START_X, START_Y, 0);
	sprite->Draw(*maskTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	sprite->End();


	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	for (int i = 0; i < player->visitingPos.size(); ++i)
	{
		int nx = player->visitingPos[i].x;
		int ny = player->visitingPos[i].y;
		pos = D3DXVECTOR3(START_X + nx, START_Y + ny, 0);
		sprite->Draw(*dotTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 0, 0));
	}
	sprite->End();

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			if (map[y * WIDTH + x] == MAP_PROPERTY_EDGE)
			{
				pos = D3DXVECTOR3(START_X + x, START_Y + y, 0);
				sprite->Draw(*dotTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}
	}
	sprite->End();
	player->Render();

}

void GameSystem::FloodFill(int ind)
{
	stack<int> mapIndex;
	mapIndex.push(ind);

	while (!mapIndex.empty())
	{
		int index = mapIndex.top();
		mapIndex.pop();
		int nx = index % WIDTH;
		int ny = index / WIDTH;

		if (nx < 0)continue;
		if (ny < 0) continue;
		if (nx >= WIDTH)continue;
		if (ny >= HEIGHT)continue;
		if (map[ny * WIDTH + nx] != MAP_PROPERTY_EMPTY)continue;
		map[ny * WIDTH + nx] = MAP_PROPERTY_TEMP;

		mapIndex.push((ny-1) * WIDTH + nx);
		mapIndex.push((ny+1) * WIDTH + nx);
		mapIndex.push(ny * WIDTH + (nx-1));
		mapIndex.push(ny * WIDTH + (nx+1));

	}
}

void GameSystem::MakeBorder()
{
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			if (map[y*WIDTH+x] == MAP_PROPERTY_VISIT)
			{
				if (map[(y - 1) * WIDTH + x] == MAP_PROPERTY_EMPTY ||
					map[(y + 1) * WIDTH + x] == MAP_PROPERTY_EMPTY ||
					map[y * WIDTH + (x - 1)] == MAP_PROPERTY_EMPTY ||
					map[y * WIDTH + (x + 1)] == MAP_PROPERTY_EMPTY ||
					map[(y - 1) * WIDTH + (x + 1)] == MAP_PROPERTY_EMPTY ||
					map[(y - 1) * WIDTH + (x - 1)] == MAP_PROPERTY_EMPTY ||
					map[(y + 1) * WIDTH + (x + 1)] == MAP_PROPERTY_EMPTY ||
					map[(y + 1) * WIDTH + (x - 1)] == MAP_PROPERTY_EMPTY)
				{
					map[y * WIDTH + x] = MAP_PROPERTY_EDGE;
				}
					
			}
		}
	}
}

void GameSystem::SetProperty()
{
	FloodFill(300*WIDTH+300);

	for (int i = 0; i < WIDTH * HEIGHT; ++i)
	{
		if (map[i] == MAP_PROPERTY_TEMP)
		{
			binaryMap[i] = MAP_PROPERTY_EMPTY;
		}
		else
		{
			binaryMap[i] = MAP_PROPERTY_VISIT;
		}
	}

	memcpy(map, binaryMap, WIDTH * HEIGHT * sizeof(int));

	RECT tdr = { 0,0,WIDTH,HEIGHT };
	D3DLOCKED_RECT tlr;
	if (SUCCEEDED((*maskTex)->LockRect(0, &tlr, &tdr, 0)))
	{
		DWORD* p = (DWORD*)tlr.pBits;
		for (int i = 0; i < WIDTH * HEIGHT; ++i)
		{
			if (map[i] == MAP_PROPERTY_VISIT)
			{
				p[i] = mapData[i];
			}
			
		}
		(*maskTex)->UnlockRect(0);
	}

	
	player->visitingPos.clear();
	player->startSetProperty = false;
	player->VISITING = false;

	MakeBorder();
}



void GameSystem::Load()
{

	D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);

	backgroundTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device(),
		"source/img/background.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		0,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		nullptr,
		nullptr,
		backgroundTex
	);


	maskTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device(),
		"source/img/mask.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		0,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		nullptr,
		nullptr,
		maskTex
	);

	dotTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device(),
		"source/img/dot.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		0,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		nullptr,
		nullptr,
		dotTex
	);

	RECT tdr = { 0,0,WIDTH,HEIGHT };
	D3DLOCKED_RECT tlr;

	if (SUCCEEDED((*backgroundTex)->LockRect(0, &tlr, &tdr, 0)))
	{
		DWORD* p = (DWORD*)tlr.pBits;
		memcpy(mapData, p, WIDTH * HEIGHT * sizeof(int));
		(*backgroundTex)->UnlockRect(0);
	}
}