#pragma once
class GameSystem
{
public:
	GameSystem();
	virtual ~GameSystem();

	void Render();
	void Update();
	void FloodFill();
	void SetProperty();
	void Load();


};

