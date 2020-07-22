#pragma once
#include "gameNode.h"
#include "obstacle.h"
#include <vector>

class obstacleManager : public gameNode
{
private:
	typedef vector<obstacle*>			vObstacle;
	typedef vector<obstacle*>::iterator viObstacle;

private:
	vObstacle	_vObstacle;

public:
	obstacleManager();
	~obstacleManager();

	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

	vector<obstacle*> getVObstacle() { return _vObstacle; }

	void setObstacle(OBSTACLESTATE obstacleState);				//장애물 생성함수

};

