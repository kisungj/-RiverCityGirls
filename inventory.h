#pragma once
#include "gameNode.h"
#include <vector>

class inventory : public gameNode
{
private:
	image		_inImage;				//아이템 이미지
	string		_inItemName;			//아이템 이름
	string		_inItemDiscription;		//아이템 설명
	int		_inHpPortion;				//HP 증가 수치
	int		_inPowerPortion;			//공격력 증가 수치

public:
	inventory();
	~inventory();

	virtual HRESULT init();
	virtual void release();
	virtual void updatea();
	virtual void render();

	string getInItemName() { return _inItemName; }											//아이템 이름 넘겨주기
	void setInItemName(string name) { _inItemName = name; }									//아이템 이름 설정
	string getInItemDiscription() { return _inItemDiscription; }							//아이템 설명 넘겨주기
	void setInItemDiscription(string discription) { _inItemDiscription = discription; }		//아이템 설명 설정
	int getInHpPortion() { return  _inHpPortion; }											//HP 아이템 넘겨주기
	void setInHpPortion(int hp) { _inHpPortion = hp; }										//HP 아이템 설정
	int getInPowerPortion() { return _inPowerPortion; }										//POWER 아이템 넘겨주기
	void setInPowerPortion(int power) { _inPowerPortion = power; }							//POWER 아이템 설정
};


