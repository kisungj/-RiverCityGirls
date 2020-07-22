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

	RECT		_testRc;		//테스트용 rc
	RECT		_testAttackRc;	//테스트공격
	bool		_attackbool;	//테스트
	int			_attackCount;	//테스트
	float		_x, _y;			//테스트용 x, y 
	int			_moneyCount;	//테스트 돈
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

