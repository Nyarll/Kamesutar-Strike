#include "ScreenShot.h"

#include <direct.h>
#include <string>
#include <shlwapi.h>
#pragma comment( lib , "shlwapi.lib" )

static bool CheckExistenceOfFolder(const std::string folder_name);	// ���̖��O�̃t�H���_�����݂��邩�ǂ��� / ���݂����Ȃ�FALSE��Ԃ�

static bool CheckExistenceOfFolder(const std::string folder_name)
{
	if (_mkdir(folder_name.c_str()) == 0) {
		return true;
	}
	else {
		return false;
	}
}

void SaveScreenShotToPng(int x1, int y1, int x2, int y2)
{
	int i;

	if (CheckExistenceOfFolder("ScreenShot"))	// ScreenShot �Ƃ����t�H���_�����邩�m�F
	{
		_mkdir("ScreenShot");	// ������΍��
	}
	for (i = 0; i < 1000; i++)
	{
		char str[64];
		sprintf(str, "ScreenShot/shot%03d.png", i);
		if (PathFileExists(str) == 0) 
		{
			SaveDrawScreenToPNG(x1, y1, x2, y2, str);
			break;
		}
	}
}

void SaveScreenShotToJpg(int x1, int y1, int x2, int y2)
{

	int i;

	if (CheckExistenceOfFolder("ScreenShot"))	// ScreenShot �Ƃ����t�H���_�����邩�m�F
	{
		_mkdir("ScreenShot");	// ������΍��
	}
	for (i = 0; i < 1000; i++)
	{
		char str[64];
		sprintf(str, "ScreenShot/shot%03d.jpg", i);
		if (PathFileExists(str) == 0)
		{
			SaveDrawScreenToPNG(x1, y1, x2, y2, str);
			break;
		}
	}
}