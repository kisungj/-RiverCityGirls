#pragma once
#include "gameNode.h"
#include "obstacleManager.h"
#include "itemManager.h"
#include "inventory.h"

class testObstcle : public gameNode
{
private:
	obstacleManager* _om;
	itemManager*     _im;
	inventory*		 _in;

	RECT		_testRc;		//�׽�Ʈ�� rc
	RECT		_testAttackRc;	//�׽�Ʈ����
	bool		_attackbool;	//�׽�Ʈ
	int			_attackCount;	//�׽�Ʈ
	float		_x, _y;			//�׽�Ʈ�� x, y 
	int			_moneyCount;	//�׽�Ʈ ��
public:
	testObstcle() {}
	~testObstcle() {}

	HRESULT init();
	void render();
	void update();
	void release();
public:
	void imageLoad();
	void collision();
};

