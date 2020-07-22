#include "stdafx.h"
#include "iniDataManager.h"


iniDataManager::iniDataManager()
{
}


iniDataManager::~iniDataManager()
{
}

HRESULT iniDataManager::init(void)
{
	return S_OK;
}

//저장 함수
void iniDataManager::addData(const char* subject, const char* title, const char* body)
{
	tagIniData iniData;
	iniData.subject = subject;
	iniData.title = title;
	iniData.body = body;

	//벡터에 데이터를 담아준다
	arrIniData vIniData;
	vIniData.push_back(iniData);

	_vIniData.push_back(vIniData);

}
void iniDataManager::iniSave(const char* fileName)
{
	char str[256];	//데이터 저장할 문자변수
	char dir[128];	//파일 저장할 디렉토리를 담을 문자변수

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	//현재 파일 경로를 저장
	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	for (int i = 0; i < _vIniData.size(); i++)
	{
		arrIniData vData = _vIniData[i];
		WritePrivateProfileString(vData[0].subject, vData[0].title,
			vData[0].body, str);
		vData.clear();
	}

	_vIniData.clear();
}

//로드(읽기)함수
//파일에서 문자열 가져오는 함수
string iniDataManager::loadDataString(const char* fileName, const char* subject, const char* title)
{
	char str[256];
	char dir[128];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	char data[200] = { NULL };
	GetPrivateProfileString(subject, title, "", data, 200, str);

	//변수명 마음에 안든다 슈발
	string strr = data;

	return strr;
}
//파일에서 정수 가져오는 함수
int iniDataManager::loadDataInteger(const char* fileName, const char* subject, const char* title)
{
	char str[256];
	char dir[128];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	return 	GetPrivateProfileInt(subject, title, 0, str);
}