#include "DXUT.h"
#include "TitlePage.h"
#include"global.h"

TitlePage::TitlePage()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);

	titleTex = new LPDIRECT3DTEXTURE9();

	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device(),
		"background.png",
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
		titleTex
	);


}

TitlePage::~TitlePage()
{
	(*titleTex)->Release();
	sprite->Release();
}

void TitlePage::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);

	//버튼 x,y설정
}

void TitlePage::Render()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXVECTOR3 pos(START_X, START_Y, 0);
	sprite->Draw(*titleTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	sprite->End();
}