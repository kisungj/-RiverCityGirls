#pragma once
#include "gameNode.h"

enum titleState
{
	TITLE_FIRST,
	TITLE_SECOND,
	TITLE_THIRD
};

class titleStage : public gameNode
{
private:
	titleState _titleState;
	image* _selectArrow;
	string _stage1Str;
	string _stage2Str;
	string _stage3Str;

	float _arrowX, _arrowY;
	float _kyokoX;
	float _misakoX;
	float _titleY;
	float _secondX;
	float _stage1X;
	float _stage2X;
	float _stage3X;
	float _effectAlpha;

	int _stage1Alpha;
	int _stage2Alpha;
	int _stage3Alpha;
	int _selectCount;
	int _stageCount;

	bool _isStart;
	bool _nextScene;
	bool _stage1Start;
	bool _stage2Start;
	bool _stage3Start;
	bool _fade;
	bool _isFade;
	bool _selectPlayer;

public:
	titleStage() {}
	~titleStage() {}

public:
	virtual HRESULT init();
	virtual void render();
	virtual void update();
	virtual void release();
public:
	bool getNextScene() { return _nextScene; }
	void setNextScene(bool arg) { _nextScene = arg; }
	bool getStage1() { return _stage1Start; }
	bool getStage2() { return _stage2Start; }
	bool getStage3() { return _stage3Start; }
};

