#include "DXUT.h"
#include "TitlePage.h"
#include"global.h"

#define TEX_POS_X 1335
#define TEX_POS_Y 350
#define TEX_WIDTH 470
#define TEX_HEIGHT 130

TitlePage::TitlePage()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);

	titleTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device(),
		"img/title.png",
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

	gameStartTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device(),
		"img/gamestart.png",
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
		gameStartTex
	);

	gameIntroductionTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device(),
		"img/gameintroduction.png",
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
		gameIntroductionTex
	);

	rankingTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device(),
		"img/ranking.png",
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
		rankingTex
	);

	creditTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device(),
		"img/credit.png",
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
		creditTex
	);
	
	exitTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device(),
		"img/exit.png",
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
		exitTex
	);
	

}

TitlePage::~TitlePage()
{
	(*titleTex)->Release();
	(*gameStartTex)->Release();
	(*gameIntroductionTex)->Release();
	(*rankingTex)->Release();
	(*creditTex)->Release();
	(*exitTex)->Release();
	sprite->Release();
}

void TitlePage::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);

	if (pt.x > TEX_POS_X && pt.x < TEX_POS_X + TEX_WIDTH && 
		pt.y>TEX_POS_Y && pt.y<TEX_POS_Y+TEX_HEIGHT)
	{
		if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0)
		{
			pageManager.MakeFirstGamePage();
		}
	}

	//버튼 x,y설정
}

void TitlePage::Render()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(*titleTex, nullptr, nullptr, &(D3DXVECTOR3(0, 0, 0)) , D3DCOLOR_ARGB(255, 255, 255, 255));
	sprite->End();

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(*gameStartTex, nullptr, nullptr, &(D3DXVECTOR3(TEX_POS_X, TEX_POS_Y, 0)), D3DCOLOR_ARGB(255, 255, 255, 255));
	sprite->End();

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(*gameIntroductionTex, nullptr, nullptr, &(D3DXVECTOR3(TEX_POS_X, TEX_POS_Y+TEX_HEIGHT, 0)), D3DCOLOR_ARGB(255, 255, 255, 255));
	sprite->End();

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(*rankingTex, nullptr, nullptr, &(D3DXVECTOR3(TEX_POS_X, TEX_POS_Y + TEX_HEIGHT*2, 0)), D3DCOLOR_ARGB(255, 255, 255, 255));
	sprite->End();

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(*creditTex, nullptr, nullptr, &(D3DXVECTOR3(TEX_POS_X, TEX_POS_Y + TEX_HEIGHT*3, 0)), D3DCOLOR_ARGB(255, 255, 255, 255));
	sprite->End();

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(*exitTex, nullptr, nullptr, &(D3DXVECTOR3(TEX_POS_X, TEX_POS_Y + TEX_HEIGHT*4, 0)), D3DCOLOR_ARGB(255, 255, 255, 255));
	sprite->End();
}