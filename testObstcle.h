#pragma once
#include "gameNode.h"
#include "obstacleManager.h"
#include "itemManager.h"
class testObstcle : public gameNode
{
private:
	obstacleManager* _om;
	itemManager*     _im;
public:
	testObstcle() {}
	~testObstcle() {}

	HRESULT init();
	void render();
	void update();
	void release();
};

