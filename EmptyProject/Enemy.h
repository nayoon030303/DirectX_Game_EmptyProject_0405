#pragma once
class Enemy
{
public:
	virtual ~Enemy() {}
	virtual void Render();
	virtual void Update();
};

