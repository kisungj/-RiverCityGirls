#pragma once
#include "gameNode.h"
class titleStage : public gameNode
{
private:
	bool _isStart;
	image* _selectArrow;

	float _arrowX, _arrowY;

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

