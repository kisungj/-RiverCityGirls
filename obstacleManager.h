#pragma once
#include "gameNode.h"
class obstacleManager : public gameNode
{
private:

public:
	obstacleManager() {}
	~obstacleManager() {}
public:
	HRESULT init();
	void render();
	void update();
	void release();
};

