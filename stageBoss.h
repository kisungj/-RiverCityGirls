#pragma once
#include "gameNode.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

class stageBoss : public gameNode
{
private:
	class boss*   _boss;
	class player* _player;

	int  _shakeTime;
	bool _isTemp;
	bool _isDialog;
public:
	stageBoss() {}
	~stageBoss() {}
public:
	virtual HRESULT init(player* player, boss* boss);
	virtual void render();
	virtual void update();
	virtual void release();
public:
	bool getIsDialog() { return _isDialog; }
	void setIsDialog(bool arg) { _isDialog = arg; }
};

