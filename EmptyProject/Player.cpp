#include "DXUT.h"
#include "Player.h"
#include "global.h"

#define PLAYER_WH 8


Player::Player()
{

	playerState = ON_EDGE;
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
		if (playerState == VISITING)
		{
			px = startPos.x;
			py = startPos.y;
			press = false;
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

		for (int i = 1; i <= speed; ++i)
		{
			nx = px + 1;
			ny = py;

			if (nx<0 || nx>=WIDTH || ny < 0 || ny>=HEIGHT)
				break;

			playerMove();
		}
	}
	//left
	else if (((GetAsyncKeyState(VK_LEFT) & 0x8000) != 0) && px >0)
	{

		for (int i = 1; i <= speed; ++i)
		{
			nx = px - 1; 
			ny = py;

			if (nx < 0 || nx >= WIDTH || ny < 0 || ny >= HEIGHT)
				break;

			playerMove();
		}
	}
	//up
	else if (((GetAsyncKeyState(VK_UP) & 0x8000) != 0))//&& py <0
	{

			for (int i = 1; i <= speed; ++i)
			{
				nx = px;
				ny = py - 1;

				if (nx < 0 || nx >= WIDTH || ny < 0 || ny >= HEIGHT)
					break;
				playerMove();
		}
	}
	//down
	else if (((GetAsyncKeyState(VK_DOWN) & 0x8000) != 0) )
	{

		for (int i = 1; i <= speed; ++i)
		{
			nx = px;
			ny = py + 1;
			if (nx < 0 || nx >= WIDTH || ny < 0 || ny >= HEIGHT)
				break;
			playerMove();
		}
	};
}

void Player::playerMove()
{

	if (map[py * WIDTH + px] == MAP_PROPERTY_EDGE && map[ny * WIDTH + nx] == MAP_PROPERTY_EDGE)
	{
		px = nx;
		py = ny;
	}
	if (map[py * WIDTH + px] == MAP_PROPERTY_EDGE && map[ny * WIDTH + nx] == MAP_PROPERTY_EMPTY && press)
	{
		startPos.x = px;
		startPos.y = py;

		px = nx;
		py = ny;
		visitingPos.push_back(D3DXVECTOR2(px, py));
		map[py * WIDTH + px] = MAP_PROPERTY_VISITING;
		playerState = VISITING;
	}
	if (map[py * WIDTH + px] == MAP_PROPERTY_VISITING && map[ny * WIDTH + nx] == MAP_PROPERTY_EMPTY && press)
	{
		px = nx;
		py = ny;
		visitingPos.push_back(D3DXVECTOR2(px, py));
		map[py * WIDTH + px] = MAP_PROPERTY_VISITING;
	}
	if (map[py * WIDTH + px] == MAP_PROPERTY_VISITING && map[ny * WIDTH + nx] == MAP_PROPERTY_EDGE && press)
	{
		px = nx;
		py = ny;
		startSetProperty = true;
		playerState = ON_EDGE;

	}

}

void Player::Render()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXVECTOR3 pos(START_X + px-PLAYER_WH/2, START_Y + py - PLAYER_WH / 2, 0);
	sprite->Draw(*playerTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	sprite->End();
}