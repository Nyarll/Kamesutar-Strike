#include "ScreenShot.h"

#include <direct.h>
#include <string>
#include <shlwapi.h>
#pragma comment( lib , "shlwapi.lib" )

static bool CheckExistenceOfFolder(const std::string folder_name);	// その名前のフォルダが存在するかどうか / 存在したならFALSEを返す

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

	if (CheckExistenceOfFolder("ScreenShot"))	// ScreenShot というフォルダがあるか確認
	{
		_mkdir("ScreenShot");	// 無ければ作る
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

	if (CheckExistenceOfFolder("ScreenShot"))	// ScreenShot というフォルダがあるか確認
	{
		_mkdir("ScreenShot");	// 無ければ作る
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