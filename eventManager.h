#pragma once
#include "singletonBase.h"
#include "iEvent.h"

class eventManager : public singletonBase<eventManager>
{
public:
	eventManager() {}
	~eventManager() {}

public:
	HRESULT init();
	void release();

	// 이벤트 담을 변수
	vector<iEvent*> mEventQueue;

	void update();
	// 이벤트 추가
	void addEvent(iEvent* pEvent);
};

