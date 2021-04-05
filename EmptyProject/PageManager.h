#pragma once
#include "DXUT.h"

class Page;

class PageManager
{
public:
	PageManager();
	virtual ~PageManager();

	void Render();
	void Update();
	void deleteData();

	void MakeTitlePage();

	Page* currentPage;
};

