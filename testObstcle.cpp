#include "stdafx.h"
#include "testObstcle.h"

HRESULT testObstcle::init()
{
	_om = new obstacleManager;
	_om->init();
	_im = new itemManager;
	_im->init();
	return S_OK;
}

void testObstcle::render()
{
	_om->render();
	_im->render();
}

void testObstcle::update()
{
	_om->update();
	_im->update();
}

void testObstcle::release()
{
	_om->release();
	_im->release();
}
