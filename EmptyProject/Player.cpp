#include "DXUT.h"
#include "Player.h"
#include "global.h"

#define PLAYER_WH 8


Player::Player()
{
	px = 0;
	py = 0;
	VISITING = false;
	startSetProperty = false;
	speed = 5;
	press = false;
	D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);

	playerTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device(),
		"source/img/player.png",
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
		playerTex
	);
}

Player::~Player()
{
	sprite->Release();
	(*playerTex)->Release();
}

void Player::Update()
{

	if (px < 0)
		px = 0;
	if (py < 0)
		py = 0;
	if (px >= WIDTH)
		px = WIDTH -1;
	if (py >= HEIGHT)
		py = HEIGHT -1;



	if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0)
	{
		press = true;
	}
	else
	{
		press = false;
		if (VISITING)
		{
			px = startPos.x;
			py = startPos.y;
			for (int i = 0; i < visitingPos.size(); ++i)
			{
				int nx = visitingPos[i].x;
				int ny = visitingPos[i].y;
				map[ny * WIDTH + nx] = MAP_PROPERTY_EMPTY;
			}
			visitingPos.clear();

		}
	}

	//right
	if (((GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0) && px <= WIDTH - 1)
	{
		playerMove(+1, 0);
		
	}
	//left
	else if (((GetAsyncKeyState(VK_LEFT) & 0x8000) != 0) && px >0)
	{
		playerMove(-1, 0);
	}
	//up
	else if (((GetAsyncKeyState(VK_UP) & 0x8000) != 0))//&& py <0
	{
		playerMove(0, -1);
	}
	//down
	else if (((GetAsyncKeyState(VK_DOWN) & 0x8000) != 0) )
	{
		playerMove(0, 1);
	}
}

void Player::playerMove(int x, int y)
{
	for (int i = 0; i < speed; ++i)
	{
		nx = px + x;
		ny = py + y;

		if (nx < 0 || nx >= WIDTH || ny < 0 || ny >= HEIGHT)
			break;

		if (map[py * WIDTH + px] == MAP_PROPERTY_EDGE 
			&& map[ny * WIDTH + nx] == MAP_PROPERTY_EDGE)
		{
			px = nx;
			py = ny;
		}

		else if (map[py * WIDTH + px] == MAP_PROPERTY_EDGE 
			&& map[ny * WIDTH + nx] == MAP_PROPERTY_EMPTY 
			&& press)
		{
			startPos.x = px;
			startPos.y = py;
			px = nx;
			py = ny;
			//visitingPos.push_back(D3DXVECTOR2(px, py));
			map[py * WIDTH + px] = MAP_PROPERTY_VISITING;
			VISITING = true;
		}

		else if (map[py * WIDTH + px] == MAP_PROPERTY_VISITING && map[ny * WIDTH + nx] == MAP_PROPERTY_EMPTY && press)
		{
			visitingPos.push_back(D3DXVECTOR2(px, py));
			px = nx;
			py = ny;
			map[py * WIDTH + px] = MAP_PROPERTY_VISITING;
		}
		else if (map[py * WIDTH + px] == MAP_PROPERTY_VISITING && map[ny * WIDTH + nx] == MAP_PROPERTY_EDGE && press)
		{
			press = false;
			VISITING = false;
			px = nx;
			py = ny;
			startSetProperty = true;


		}
	}

}

void Player::Render()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXVECTOR3 pos(START_X + px-PLAYER_WH/2, START_Y + py - PLAYER_WH / 2, 0);
	sprite->Draw(*playerTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	sprite->End();
}