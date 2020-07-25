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

	// ��Ʈ���� ���� �߰� ( ���� Ÿ��, �̹���, ���� x, ���� y)
	void addRender(HDC hdc, renderType rendertype, image* img, float x, float y, float z);
	// ��Ʈ���� ���� �߰� ( ���� Ÿ��, �̹���, ���� x, ���� y, ������ x, ������ y)
	void addFrameRender(HDC hdc, renderType rendertype, image* img, float x, float y, float z, float frmaeX, float frameY);
	// ��Ʈ���� ���� �߰� ( ���� Ÿ��, �̹���, ���� x, ���� y, ����)
	void addAlphaRender(HDC hdc, renderType rendertype, image* img, float x, float y, float z, BYTE alpha);
	// ��Ʈ���� ���� �߰� ( ���� Ÿ��, �̹���, ���� x, ���� y, �ִϸ��̼�)
	void addAniRender(HDC hdc, renderType rendertype, image* img, float x, float y, float z, animation* ani);

	// �� ���� ��� Z-Order �����Լ� (�������� �Ŵ��� or �� �������� ������Ʈ �κп� ���� ��)
	void zOrderSort(int i, int j);

	// ���� �Լ� (���� �κп� ���� ��)
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

