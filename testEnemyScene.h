#pragma once
#include "gameNode.h"
#include "enemyManager.h"

class testEnemyScene : public gameNode
{
private:
	enemyManager* _em;

	RECT _testPlayer;
	RECT _punch;
	float _x, _y;

	bool _right;

public:
	testEnemyScene() {}
	~testEnemyScene() {}

public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
};

