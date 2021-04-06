#include "DXUT.h"
#include "FirstGamePage.h"
#include <atlconv.h>

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

	D3DXCreateFont(DXUTGetD3D9Device(), 30, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"Arial", &font);
}

FirstGamePage::~FirstGamePage()
{
	sprite->Release();
	(*background)->Release();
	font->Release();
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

	char text[] = "firstGaem";
	float score = 1234.567;
	char cscore[256];
	sprintf(cscore, "%.2f", score);

	USES_CONVERSION;

	WCHAR* w = A2W(text);
	WCHAR* w1 = A2W(cscore);

	RECT rc;
	rc.left = 10;
	rc.top = 200;
	rc.right = 300;
	rc.bottom = 500;
	font->DrawText(NULL, w, -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
	rc.left = 300;
	rc.top = 200;
	rc.right = 300;
	rc.bottom = 500;
	font->DrawText(NULL, w1, -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));



}
