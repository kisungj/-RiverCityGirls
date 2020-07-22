#pragma once
#include "singletonBase.h"
#include <vector>

using namespace std;

struct tagIniData
{
	const char* subject; //항목
	const char* title;	 //제목
	const char* body;	 //값
};

class iniDataManager : public singletonBase <iniDataManager>
{
private:
	typedef vector<tagIniData> arrIniData;
	typedef vector<tagIniData>::iterator arrIniDataIter;

	typedef vector<arrIniData> arrIniDatas;
	typedef vector<arrIniData>::iterator arrIniDatasIter;


private:
	arrIniDatas _vIniData;

public:
	HRESULT init(void);

	//저장 함수
	void addData(const char* subject, const char* title, const char* body);
	void iniSave(const char* fileName);

	//로드(읽기)함수
	//파일에서 문자열 가져오는 함수
	string loadDataString(const char* fileName, const char* subject, const char* title);
	//파일에서 정수 가져오는 함수
	int loadDataInteger(const char* fileName, const char* subject, const char* title);

	iniDataManager();
	~iniDataManager();
};

