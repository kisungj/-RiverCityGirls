#pragma once
#include "gameNode.h"
class stage1 : public gameNode
{
private:
	class obstacleManager* _obstacleManager;
	class itemManager*     _itemManager;
	class enemyManager*    _enemyManager;
	class player*          _player;
public:
	stage1() {}
	~stage1() {}

public:
	virtual HRESULT init(obstacleManager* obstacleManager, itemManager* itemManager, enemyManager* enemyManager, player* player);
	virtual void render();
	virtual void update();
	virtual void release();
public:

};

