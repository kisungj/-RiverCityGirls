#include "stdafx.h"
#include "obstacleManager.h"

obstacleManager::obstacleManager()
{
}

obstacleManager::~obstacleManager()
{
}

HRESULT obstacleManager::init()
{

	return S_OK;
}

void obstacleManager::update()
{
	for (int i = 0; i < _vObstacle.size(); i++)
	{
		_vObstacle[i]->update();
	}
}

void obstacleManager::release()
{
	for (int i = 0; i < _vObstacle.size(); i++)
	{
		SAFE_DELETE(_vObstacle[i]);
	}
	_vObstacle.clear();
}


void obstacleManager::render()
{
	for (int i = 0; i < _vObstacle.size(); i++)
	{
		_vObstacle[i]->render();
	}
}

//장애물 생성
void obstacleManager::setObstacle(OBSTACLESTATE obstacleState)
{
	//자판기
	if (obstacleState == VENDING)
	{
		obstacle* _obstacle = new obstacle;
		_obstacle->init(VENDING, PointMake(1980, 550));
		_vObstacle.push_back(_obstacle);
	}

	//책상
	if (obstacleState == DESK)
	{
		obstacle* _obstacle = new obstacle;
		_obstacle->init(DESK, PointMake(100, 100));
		_vObstacle.push_back(_obstacle);
	}

	//기둥왼쪽
	if (obstacleState == PILLARLEFT)
	{
		obstacle* _obstacle = new obstacle;
		_obstacle->init(PILLARLEFT, PointMake(917, 405));
		_vObstacle.push_back(_obstacle);
	}

	//기둥오른쪽
	if (obstacleState == PILLARRIGHT)
	{
		obstacle* _obstacle = new obstacle;
		_obstacle->init(PILLARRIGHT, PointMake(2700, 405));
		_vObstacle.push_back(_obstacle);
	}
}
