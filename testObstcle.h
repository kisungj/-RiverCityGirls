#pragma once
#include "gameNode.h"
#include "obstacleManager.h"
#include "itemManager.h"

class testObstcle : public gameNode
{
private:
	obstacleManager* _om;
	itemManager*     _im;

	RECT		_testRc;		//�׽�Ʈ�� rc
	RECT		_testAttack;	//�׽�Ʈ����
	bool		_attackbool;	//�׽�Ʈ
	int			_attackCount;	//�׽�Ʈ
	float		_x, _y;			//�׽�Ʈ�� x, y 
public:
	testObstcle() {}
	~testObstcle() {}

	HRESULT init();
	void render();
	void update();
	void release();
public:
	void imageLoad();
};

