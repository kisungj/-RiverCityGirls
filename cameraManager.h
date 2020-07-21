#pragma once
#include "singletonBase.h"
#include "image.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	float _left, _top;                // ī�޶��� Left, Top ������ǥ
	float _x, _y;					  // ī�޶��� ���� ��ǥ
	float _width, _height;			  // ī�޶��� �ʺ�, ���� ��

	float _minLeft, _maxLeft;         // ī�޶��� Left ������ ����
	float _minTop,  _maxTop;		  // ī�޶��� Top  ������ ����
	float _minX, _maxX;				  // ī�޶��� X    ������ ����
	float _minY, _maxY;				  // ī�޶��� Y    ������ ����
	
public:
	cameraManager() {}
	~cameraManager() {}
public:
	HRESULT init();
	void release();
	void settingCamera(float left, float top, float width, float height, float minLeft, float minTop, float maxLeft, float maxTop);
public:
	void renderRectangle(HDC hdc, RECT rect);
	void renderEllipse(HDC hdc, RECT rect);
	void render(HDC hdc, image* img, float destX, float destY);
	void frameRender(HDC hdc, image* img, float destX, float destY);
	void frameRender(HDC hdc, image* img, float destX, float destY, int frameX, int frameY);
	void loopRender(HDC hdc, image* img, RECT lpRect, int offsetX, int offsetY);
	void aniRender(HDC hdc, image* img, int destX, int destY, animation* ani);
public:
	float getLeft() { return _left; }
	float getTop()  { return _top; }
	float getX()    { return _x; }
	float getY()    { return _y; }
	void  setLeft(float relativeLeft);
	void  setTop(float relativeTop);
	void  setX(float relativeX);
	void  setY(float relativeY);

	float calcRelativeLeft(float left);
	float calcRelativeTop(float top); 
};

