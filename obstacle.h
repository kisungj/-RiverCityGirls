#pragma once
#include "gameNode.h"
class obstacle : public gameNode
{
private:	

public:
	obstacle() {}
	~obstacle() {}
public:
	virtual HRESULT init();
	virtual void    render();
	virtual void    update();
	virtual void    release();
public:
};

