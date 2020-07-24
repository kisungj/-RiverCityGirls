#pragma once
#include "gameNode.h"
#include "titleStage.h"
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
#include "inventory.h"
#include "enemyManager.h"
#include "boss.h"
#include "player.h"
#include "ui.h"

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
	inventory*		 _inventory;
	enemyManager*    _enemyManager;
	boss*            _boss;
	ui*              _ui;
	image*			 _loading;

	titleStage*		 _title;
	stage1*          _stage1;
	stage2*          _stage2;
	stageBoss*       _stageBoss;
	player*          _player;

	string			 _curStageName;

	string			 _dialogTempStr;
	string			 _dialogTypeStr;
	string			 _dialogTalkStr;
	char			 _dialogIndexStr[255];
	float			 _dialogPlayerX;
	float		     _dialogBossX;
	float			 _dialogChatCount;
	int				 _dialogIndex;

	float			 _loadingTimer;
	float			 _loadingFrameTimer;
	int				 _changeStageNum;

	bool			 _isLoading;
public:
	stageManager() {}
	~stageManager() {}
public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
public:
	void collision();
	void doorCol();
};

