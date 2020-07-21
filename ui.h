#pragma once
#include "gameNode.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

class ui : public gameNode
{
private:
	image* _hpUI;
	image* _selectArrow;
	image* _loading;
	RECT _hpRC;

	float _timer;
	float _arrowX, _arrowY;
	bool _isStart;

	float _hpWidth;
	float _testHp;
	

public:
	ui() {}
	~ui() {}
public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();

	void setHpGauge(float curHp, float maxHp);
};

