#pragma once
#include "gameNode.h"
class titleStage : public gameNode
{
private:

public:
	titleStage() {}
	~titleStage() {}

public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
public:
};

