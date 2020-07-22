#pragma once
#include "gameNode.h"
#include "stage1.h"
#include "stage2.h"
#include "stageBoss.h"

#include "testPlayerScene.h"
#include "testEnemyScene.h"
#include "testBossScene.h"
#include "testUIScene.h"
#include "testObstcle.h"
#include "obstacleManager.h"
#include "itemManager.h"
#include "enemyManager.h"
#include "boss.h"
#include "player.h"
enum GAMETYPE 
{
	GAMETITLE,
	GAMELOADING,
	GAMESTART,
	GAMEOVER,
};


class stageManager : public gameNode
{
private:
	testPlayerScene* _playerScene;
	testEnemyScene*  _enemyScene;
	testBossScene*   _bossScene;
	testUIScene*	 _uiScene;
	testObstcle*     _obstacleScene;

	obstacleManager* _obstacleManager;
	itemManager*     _itemManager;
	enemyManager*    _enemyManager;
	boss*            _boss;
	stage1*          _stage1;
	stage2*          _stage2;
	stageBoss*       _stageBoss;
	player*          _player;
public:
	stageManager() {}
	~stageManager() {}
public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
public:

};

