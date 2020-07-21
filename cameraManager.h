#pragma once
#include "singletonBase.h"
#include "image.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	float _left, _top;                // 카메라의 Left, Top 절대좌표
	float _x, _y;					  // 카메라의 중점 좌표
	float _width, _height;			  // 카메라의 너비, 높이 값

	float _minLeft, _maxLeft;         // 카메라의 Left 가능한 범위
	float _minTop,  _maxTop;		  // 카메라의 Top  가능한 범위
	float _minX, _maxX;				  // 카메라의 X    가능한 범위
	float _minY, _maxY;				  // 카메라의 Y    가능한 범위
	
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

