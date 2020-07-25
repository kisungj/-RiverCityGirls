#pragma once
#include "singletonBase.h"
#include <algorithm>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

enum class renderType
{
	RENDER,
	FRAME_RENDER,
	ALPHA_RENDER,
	ANI_RENDER,
};

struct tagZoder
{
	HDC		   hdc;
	image*     img;
	RECT	   rc;
	renderType rendertype;
	POINTFLOAT pt;
	float	   z;
	POINTFLOAT frame;
	animation* ani;
	BYTE	   alpha;
};

class zOrderManager : public singletonBase<zOrderManager>
{
private:
	vector<tagZoder> _vZorder;
	bool			 _isRect;
public:
	zOrderManager() {}
	~zOrderManager() {}

public:
	HRESULT init();
	void release();


	void zOrderClear();

	// 제트오더 랜더 추가 ( 렌더 타입, 이미지, 중점 x, 중점 y)
	void addRender(HDC hdc, renderType rendertype, image* img, float x, float y, float z);
	// 제트오더 랜더 추가 ( 렌더 타입, 이미지, 중점 x, 중점 y, 프레임 x, 프레임 y)
	void addFrameRender(HDC hdc, renderType rendertype, image* img, float x, float y, float z, float frmaeX, float frameY);
	// 제트오더 랜더 추가 ( 렌더 타입, 이미지, 중점 x, 중점 y, 알파)
	void addAlphaRender(HDC hdc, renderType rendertype, image* img, float x, float y, float z, BYTE alpha);
	// 제트오더 랜더 추가 ( 렌더 타입, 이미지, 중점 x, 중점 y, 애니메이션)
	void addAniRender(HDC hdc, renderType rendertype, image* img, float x, float y, float z, animation* ani);

	// 퀵 정렬 기반 Z-Order 정렬함수 (스테이지 매니저 or 각 스테이지 업데이트 부분에 넣을 것)
	void zOrderSort(int i, int j);

	// 랜더 함수 (랜더 부분에 넣을 것)
	void zOrderRender();

	int zOrderSize() { return _vZorder.size(); }

	void DebugMod() 
	{
		if (_isRect)
		{
			_isRect = false;
		}
		else
		{
			_isRect = true;
		}
	}
};

