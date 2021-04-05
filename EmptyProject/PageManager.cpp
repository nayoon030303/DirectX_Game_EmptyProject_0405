#include "DXUT.h"
#include "PageManager.h"
#include "TitlePage.h"
#include "FirstGamePage.h"
#include "Page.h"


PageManager::PageManager()
{

}
PageManager::~PageManager()
{

}

void PageManager::MakeTitlePage()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
	TitlePage* newPage = new TitlePage();
	currentPage = newPage;
}

void PageManager::MakeFirstGamePage()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
	FirstGamePage* newPage = new FirstGamePage();
	currentPage = newPage;
}

void PageManager::Render()
{
	if (currentPage != nullptr)
	{
		currentPage->Render();
	}
}

void PageManager::Update()
{
	if (currentPage != nullptr)
	{
		currentPage->Update();
	}
}


void PageManager::deleteData()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
}
