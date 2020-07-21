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
}

void obstacleManager::render()
{
	for (int i = 0; i < _vObstacle.size(); i++)
	{
		_vObstacle[i]->render();
	}
}

//��ֹ� ����
void obstacleManager::setObstacle(OBSTACLESTATE obstacleState)
{
	//���Ǳ�
	if (obstacleState == VENDING)
	{
		obstacle* _obstacle = new obstacle;
		_obstacle->init(VENDING, PointMake(WINSIZEX + 150, WINSIZEY / 2 - 70));
		_vObstacle.push_back(_obstacle);
	}

	//���
	if (obstacleState == PILLAR)
	{
		obstacle* _obstacle = new obstacle;
		_obstacle->init(PILLAR, PointMake(2220, WINSIZEY / 2 + 100));
		_vObstacle.push_back(_obstacle);
	}
}
