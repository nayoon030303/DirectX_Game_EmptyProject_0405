#include "DXUT.h"
#include "FirstGamePage.h"

FirstGamePage::FirstGamePage()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);

	background = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device(),
		"source/img/gamebackground.png",
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
		background
	);
}

FirstGamePage::~FirstGamePage()
{
	sprite->Release();
	(*background)->Release();
}

void FirstGamePage::Update()
{
	gameSystem.Update();
}

void FirstGamePage::Render()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(*background, nullptr, nullptr,nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	sprite->End();

	gameSystem.Render();
}
