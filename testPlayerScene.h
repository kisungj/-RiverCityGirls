#pragma once
#include "gameNode.h"
#include "player.h"
#include "ui.h"

class testPlayerScene : public gameNode
{
private:
	player* _player;
	ui* _ui;

public:
	testPlayerScene() {}
	~testPlayerScene() {}

public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
};

