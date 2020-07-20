#include "stdafx.h"
#include "eventManager.h"

HRESULT eventManager::init()
{
	return S_OK;
}

void eventManager::release()
{
}

void eventManager::update()
{
	if (mEventQueue.size() == 0)
		return;

	bool isEventEnd = mEventQueue[0]->eventUpdate();

	if (isEventEnd)
	{
		//�������ְ�
		SAFE_DELETE(mEventQueue[0]);
		mEventQueue.erase(mEventQueue.begin());
		//��������µ� ������ ����Ǿ� �ִ� �̺�Ʈ�� �ִٸ�
		if (mEventQueue.size() != 0)
		{
			mEventQueue[0]->eventStart();
		}
	}
}

void eventManager::addEvent(iEvent* pEvent)
{
	if (mEventQueue.size() == 0)
	{
		pEvent->eventStart();
	}

	mEventQueue.push_back(pEvent);
}
