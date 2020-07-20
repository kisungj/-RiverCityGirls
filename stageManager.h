#pragma once
#include "gameNode.h"
#include "testPlayerScene.h"
#include "testEnemyScene.h"
#include "testBossScene.h"
class stageManager : public gameNode
{
private:
	testPlayerScene* _playerScene;
	testEnemyScene* _enemyScene;
	testBossScene*  _bossScene;
public:
	stageManager() {}
	~stageManager() {}
public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
public:

};

