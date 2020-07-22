#pragma once
#include "gameNode.h"
class stage2 : public gameNode
{
private:
	class obstacleManager* _obstacleManager;
	class itemManager*     _itemManager;
	class enemyManager*    _enemyManager;
public:
	stage2() {}
	~stage2() {}
public:
	virtual HRESULT init(obstacleManager* obstacleManager, itemManager* itemManager, enemyManager* enemyManager);
	virtual void render();
	virtual void update();
	virtual void release();
public:

};

