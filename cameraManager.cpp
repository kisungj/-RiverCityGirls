#include "stdafx.h"
#include "cameraManager.h"

HRESULT cameraManager::init()
{
	return S_OK;
}

void cameraManager::release()
{
}

void cameraManager::settingCamera(float left, float top, float width, float height, float minLeft, float minTop, float maxLeft, float maxTop)
{
	_left   = left;
	_top    = top;
	_width  = width;
	_height = height;

	_minLeft = minLeft;
	_minTop  = minTop;
	_maxLeft = maxLeft;
	_maxTop  = maxTop;

	_x = _left + (_width  * 0.5f);
	_y = _top  + (_height * 0.5f);

	_minX = _minLeft + (_width  * 0.5f);
	_maxX = _maxLeft + (_width  * 0.5f);
	_minY = _minTop  + (_height * 0.5f);
	_maxY = _maxTop  + (_height * 0.5f);
}

void cameraManager::renderRectangle(HDC hdc, RECT rect)
{
	RECT rc = rect;
	rc.left = calcRelativeLeft(rc.left);
	rc.right = calcRelativeLeft(rc.right);
	rc.top = calcRelativeTop(rc.top);
	rc.bottom = calcRelativeTop(rc.bottom);

	Rectangle(hdc, rc);
}

void cameraManager::renderEllipse(HDC hdc, RECT rect)
{
	RECT rc = rect;
	rc.left = calcRelativeLeft(rc.left);
	rc.right = calcRelativeLeft(rc.right);
	rc.top = calcRelativeTop(rc.top);
	rc.bottom = calcRelativeTop(rc.bottom);

	Ellipse(hdc, rc);
}


void cameraManager::render(HDC hdc, image * img, float destX, float destY)
{
	float relativeLeft;
	float relativeTop;
	relativeLeft = calcRelativeLeft(destX);
	relativeTop = calcRelativeTop(destY);

	if (img) img->render(hdc, relativeLeft - img->getWidth() /2 , relativeTop - img->getHeight() / 2);
}

void cameraManager::frameRender(HDC hdc, image * img, float destX, float destY)
{
	float relativeLeft;
	float relativeTop;
	relativeLeft = calcRelativeLeft(destX);
	relativeTop = calcRelativeTop(destY);

	if (img) img->frameRender(hdc, relativeLeft - img->getFrameWidth() / 2, relativeTop - img->getFrameHeight() / 2);
}

void cameraManager::frameRender(HDC hdc, image * img, float destX, float destY, int frameX, int frameY)
{
	float relativeLeft;
	float relativeTop;
	relativeLeft = calcRelativeLeft(destX);
	relativeTop = calcRelativeTop(destY);

	if (img) img->frameRender(hdc, relativeLeft - img->getFrameWidth() / 2, relativeTop - img->getFrameHeight() / 2, frameX, frameY);
}

void cameraManager::loopRender(HDC hdc, image * img, RECT lpRect, int offsetX, int offsetY)
{
	RECT rc;
	rc.left = calcRelativeLeft(lpRect.left);
	rc.right = calcRelativeLeft(lpRect.right);
	rc.top = calcRelativeTop(lpRect.top);
	rc.bottom = calcRelativeTop(lpRect.bottom);

	if (img) img->loopRender(hdc, rc, offsetX, offsetY);
}

void cameraManager::aniRender(HDC hdc, image * img, int destX, int destY, animation * ani)
{
	float relativeLeft;
	float relativeTop;
	relativeLeft = calcRelativeLeft(destX);
	relativeTop = calcRelativeTop(destY);

	if (img) img->render(hdc, relativeLeft - img->getFrameWidth() /2, relativeTop - img->getFrameHeight() / 2, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}

void cameraManager::alphaRender(HDC hdc, image * img, int destX, int destY, BYTE alpha)
{
	float relativeLeft;
	float relativeTop;
	relativeLeft = calcRelativeLeft(destX);
	relativeTop = calcRelativeTop(destY);


	if (img) img->alphaRender(hdc, relativeLeft - img->getWidth() / 2, relativeTop - img->getHeight() / 2, alpha);
}

void cameraManager::setLeft(float relativeLeft)
{
	relativeLeft = min(_maxLeft, relativeLeft);
	relativeLeft = max(_minLeft, relativeLeft);

	_left = floor(relativeLeft);
	_x = _left + (_width * 0.5f);
}

void cameraManager::setTop(float relativeTop)
{
	relativeTop = min(_maxTop, relativeTop);
	relativeTop = max(_minTop, relativeTop);

	_top = floor(relativeTop);
	_y = _top + (_height * 0.5f);
}

void cameraManager::setX(float relativeX)
{
	relativeX = min(_maxX, relativeX);
	relativeX = max(_minX, relativeX);

	_x = floor(relativeX);
	_left = _x - (_width * 0.5f);
}

void cameraManager::setY(float relativeY)
{
	relativeY = min(_maxY, relativeY);
	relativeY = max(_minY, relativeY);

	_y = floor(relativeY);
	_top = _y - (_height * 0.5f);
}

float cameraManager::calcRelativeLeft(float left)
{
	float relativeLeft = left - _left;
	return relativeLeft;
}

float cameraManager::calcRelativeTop(float top)
{
	float relativeTop = top - _top;
	return relativeTop;
} 
