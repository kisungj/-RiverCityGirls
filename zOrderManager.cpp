#include "stdafx.h"
#include "zOrderManager.h"

HRESULT zOrderManager::init()
{
	return S_OK;
}

void zOrderManager::release()
{

}

void zOrderManager::zOrderClear()
{
	_vZorder.clear();
}

void zOrderManager::addRender(HDC hdc, renderType rendertype, image * img, float x, float y)
{
	tagZoder tempZorder;

	tempZorder.hdc = hdc;
	tempZorder.rendertype = rendertype;
	tempZorder.img = img;
	tempZorder.pt.x = x;
	tempZorder.pt.y = y;
	tempZorder.frame.x = NULL;
	tempZorder.frame.y = NULL;
	tempZorder.ani = NULL;
	tempZorder.alpha = NULL;

	_vZorder.push_back(tempZorder);
}

void zOrderManager::addFrameRender(HDC hdc, renderType rendertype, image * img, float x, float y, float frmaeX, float frameY)
{
	tagZoder tempZorder;

	tempZorder.hdc = hdc;
	tempZorder.rendertype = rendertype;
	tempZorder.img = img;
	tempZorder.pt.x = x;
	tempZorder.pt.y = y;
	tempZorder.frame.x = frmaeX;
	tempZorder.frame.y = frameY;
	tempZorder.ani = NULL;
	tempZorder.alpha = NULL;

	_vZorder.push_back(tempZorder);
}

void zOrderManager::addAlphaRender(HDC hdc, renderType rendertype, image * img, float x, float y, BYTE alpha)
{
	tagZoder tempZorder;

	tempZorder.hdc = hdc;
	tempZorder.rendertype = rendertype;
	tempZorder.img = img;
	tempZorder.pt.x = x;
	tempZorder.pt.y = y;
	tempZorder.frame.x = NULL;
	tempZorder.frame.y = NULL;
	tempZorder.ani = NULL;
	tempZorder.alpha = alpha;

	_vZorder.push_back(tempZorder);
}

void zOrderManager::addAniRender(HDC hdc, renderType rendertype, image * img, float x, float y, animation * ani)
{
	tagZoder tempZorder;

	tempZorder.hdc = hdc;
	tempZorder.rendertype = rendertype;
	tempZorder.img = img;
	tempZorder.pt.x = x;
	tempZorder.pt.y = y;
	tempZorder.frame.x = NULL;
	tempZorder.frame.y = NULL;
	tempZorder.ani = ani;
	tempZorder.alpha = NULL;

	_vZorder.push_back(tempZorder);
}

void zOrderManager::zOrderSort(int i, int j)
{
	if (i >= j) return;
	int pivot = _vZorder[(i + j) / 2].pt.y;
	int left = i;
	int right = j;

	while (left <= right)
	{
		while (_vZorder[left].pt.y < pivot) left++;
		while (_vZorder[right].pt.y > pivot) right--;
		if (left <= right)
		{
			swap(_vZorder[left], _vZorder[right]);
			left++; right--;
		}
	}
	zOrderSort(i, right);
	zOrderSort(left, j);
}

void zOrderManager::zOrderRender()
{
	for (int i = 0; i < _vZorder.size(); i++)
	{
		switch (_vZorder[i].rendertype)
		{
		case renderType::RENDER:
			CAMERAMANAGER->render(_vZorder[i].hdc, _vZorder[i].img, _vZorder[i].pt.x, _vZorder[i].pt.y);
			break;
		case renderType::FRAME_RENDER:
			CAMERAMANAGER->frameRender(_vZorder[i].hdc, _vZorder[i].img, _vZorder[i].pt.x, _vZorder[i].pt.y, _vZorder[i].frame.x, _vZorder[i].frame.y);
			break;
		case renderType::ALPHA_RENDER:
			CAMERAMANAGER->alphaRender(_vZorder[i].hdc, _vZorder[i].img, _vZorder[i].pt.x, _vZorder[i].pt.y, _vZorder[i].alpha);
			break;
		case renderType::ANI_RENDER:
			CAMERAMANAGER->aniRender(_vZorder[i].hdc, _vZorder[i].img, _vZorder[i].pt.x, _vZorder[i].pt.y, _vZorder[i].ani);
			break;
		}
	}
}
