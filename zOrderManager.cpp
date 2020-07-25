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

void zOrderManager::addRender(HDC hdc, renderType rendertype, image * img, float x, float y, float z)
{
	tagZoder tempZorder;

	tempZorder.hdc = hdc;
	tempZorder.rendertype = rendertype;
	tempZorder.rc = RectMakeCenter(x, y, img->getWidth(), img->getHeight());
	tempZorder.img = img;
	tempZorder.pt.x = x;
	tempZorder.pt.y = y;
	tempZorder.z    = z;
	tempZorder.frame.x = NULL;
	tempZorder.frame.y = NULL;
	tempZorder.ani = NULL;
	tempZorder.alpha = NULL;

	_vZorder.push_back(tempZorder);
}

void zOrderManager::addFrameRender(HDC hdc, renderType rendertype, image * img, float x, float y, float z, float frmaeX, float frameY)
{
	tagZoder tempZorder;

	tempZorder.hdc = hdc;
	tempZorder.rendertype = rendertype;
	tempZorder.rc = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());
	tempZorder.img = img;
	tempZorder.pt.x = x;
	tempZorder.pt.y = y;
	tempZorder.z    = z;
	tempZorder.frame.x = frmaeX;
	tempZorder.frame.y = frameY;
	tempZorder.ani = NULL;
	tempZorder.alpha = NULL;

	_vZorder.push_back(tempZorder);
}

void zOrderManager::addAlphaRender(HDC hdc, renderType rendertype, image * img, float x, float y, float z, BYTE alpha)
{
	tagZoder tempZorder;

	tempZorder.hdc = hdc;
	tempZorder.rendertype = rendertype;
	tempZorder.rc = RectMakeCenter(x, y, img->getWidth(), img->getHeight());
	tempZorder.img = img;
	tempZorder.pt.x = x;
	tempZorder.pt.y = y;
	tempZorder.z    = z;
	tempZorder.frame.x = NULL;
	tempZorder.frame.y = NULL;
	tempZorder.ani = NULL;
	tempZorder.alpha = alpha;

	_vZorder.push_back(tempZorder);
}

void zOrderManager::addAniRender(HDC hdc, renderType rendertype, image * img, float x, float y, float z, animation * ani)
{
	tagZoder tempZorder;

	tempZorder.hdc = hdc;
	tempZorder.rendertype = rendertype;
	tempZorder.rc = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());
	tempZorder.img = img;
	tempZorder.pt.x = x;
	tempZorder.pt.y = y;
	tempZorder.z = z;
	tempZorder.frame.x = NULL;
	tempZorder.frame.y = NULL;
	tempZorder.ani = ani;
	tempZorder.alpha = NULL;

	_vZorder.push_back(tempZorder);
}

void zOrderManager::zOrderSort(int i, int j)
{
	if (i >= j) return;

	float pivot = _vZorder[(i + j) / 2].z;
	int left = i;
	int right = j;

	while (left <= right)
	{
		while (_vZorder[left].z < pivot) left++;
		while (_vZorder[right].z > pivot) right--;
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
	zOrderSort(0, _vZorder.size() - 1);

	for (int i = 0; i < _vZorder.size(); i++)
	{
		switch (_vZorder[i].rendertype)
		{
		case renderType::RENDER:
			CAMERAMANAGER->render(_vZorder[i].hdc, _vZorder[i].img, _vZorder[i].pt.x, _vZorder[i].pt.y);
			if (_isRect)
				CAMERAMANAGER->renderRectangle(_vZorder[i].hdc, _vZorder[i].rc);
			break;
		case renderType::FRAME_RENDER:
			CAMERAMANAGER->frameRender(_vZorder[i].hdc, _vZorder[i].img, _vZorder[i].pt.x, _vZorder[i].pt.y, _vZorder[i].frame.x, _vZorder[i].frame.y);
			if (_isRect)
				CAMERAMANAGER->renderRectangle(_vZorder[i].hdc, _vZorder[i].rc);
			break;
		case renderType::ALPHA_RENDER:
			CAMERAMANAGER->alphaRender(_vZorder[i].hdc, _vZorder[i].img, _vZorder[i].pt.x, _vZorder[i].pt.y, _vZorder[i].alpha);
			if (_isRect)
				CAMERAMANAGER->renderRectangle(_vZorder[i].hdc, _vZorder[i].rc);
			break;
		case renderType::ANI_RENDER:
			CAMERAMANAGER->aniRender(_vZorder[i].hdc, _vZorder[i].img, _vZorder[i].pt.x, _vZorder[i].pt.y, _vZorder[i].ani);
			if (_isRect)
				CAMERAMANAGER->renderRectangle(_vZorder[i].hdc, _vZorder[i].rc);
			break;
		}

	}

	//cout << _vZorder.capacity() << endl;
	zOrderClear();
}
