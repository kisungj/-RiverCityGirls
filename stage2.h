#pragma once
#include "gameNode.h"
class stage2 : public gameNode
{
private:
	class obstacleManager* _obstacleManager;
	class itemManager*     _itemManager;
	class enemyManager*    _enemyManager;
	class player*          _player;

	RECT				   _stage2DoorRc;
	RECT				   _bossDoorRc;

public:
	stage2() {}
	~stage2() {}
public:
	virtual HRESULT init(obstacleManager* obstacleManager, itemManager* itemManager, enemyManager* enemyManager, player* player);
	virtual void render();
	virtual void update();
	virtual void release();
public:
	RECT getStage2Door() { return _stage2DoorRc; }
	RECT getBossDoor() { return _bossDoorRc; }

};

