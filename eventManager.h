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

	// �̺�Ʈ ���� ����
	vector<iEvent*> mEventQueue;

	void update();
	// �̺�Ʈ �߰�
	void addEvent(iEvent* pEvent);

	bool isEvnet()
	{
		if (mEventQueue.size() > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

