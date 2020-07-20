#pragma once
#include "gameNode.h"
#include "enemy.h"

class testEnemyScene : public gameNode
{
private:
	enemy* _enemy;

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

