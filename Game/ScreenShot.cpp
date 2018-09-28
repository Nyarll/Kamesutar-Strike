#include "ScreenShot.h"

#include <time.h>
#include <direct.h>
#include <string>
#include <shlwapi.h>
#pragma comment( lib , "shlwapi.lib" )

// #define DISPLAY_LOG

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

void DrawSaveScreenShotLog(const char* file_name, int* change_flag)
{
	static short flag = FALSE;
	static int bright = 0;
	static const char* str = NULL;

	if (flag)
	{

		flag = FALSE;
		*change_flag = FALSE;
	}
	else
	{
		if (*change_flag == TRUE)
		{
			str = file_name;
			bright = 255;
			flag = TRUE;
		}
	}
	bright -= 1;
	if (bright <= 0)bright = 0;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, bright);
	SetFontSize(12);
	DrawFormatString(0, 0, COLOR_WHITE, "FILE NAME : %s でスクリーンショットを保存しました", str);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

bool SaveScreenShotToPng(int x1, int y1, int x2, int y2, char* name, int* change_flag)
{
	time_t timer;
	struct tm *t_st;

	time(&timer);

	if (CheckExistenceOfFolder("ScreenShot"))	// ScreenShot というフォルダがあるか確認
	{
		_mkdir("ScreenShot");	// 無ければ作る
	}

	t_st = localtime(&timer);

	{
		char str[256];

		sprintf(str, "ScreenShot/%d-%2d-%2d-%2d-%2d-%2d.png", t_st->tm_year, t_st->tm_mon + 1, t_st->tm_mday, t_st->tm_hour, t_st->tm_min, t_st->tm_sec);

		if (PathFileExists(str) == 0)
		{
			SaveDrawScreenToPNG(x1, y1, x2, y2, str);

			if (name != NULL)strcpy(name, str);
			*change_flag = TRUE;
			return true;
		}
	}
	return false;
}

bool SaveScreenShotToJpg(int x1, int y1, int x2, int y2, char* name, int* change_flag)
{
	time_t timer;
	struct tm *t_st;

	time(&timer);

	if (CheckExistenceOfFolder("ScreenShot"))	// ScreenShot というフォルダがあるか確認
	{
		_mkdir("ScreenShot");	// 無ければ作る
	}

	t_st = localtime(&timer);

	{
		char str[256];

		sprintf(str, "ScreenShot/%d-%d-%d-%d-%d-%d.jpg", t_st->tm_year, t_st->tm_mon + 1, t_st->tm_mday, t_st->tm_hour, t_st->tm_min, t_st->tm_sec);

		if (PathFileExists(str) == 0)
		{
			SaveDrawScreenToPNG(x1, y1, x2, y2, str);

			if (name != NULL)strcpy(name, str);
			*change_flag = TRUE;
			return true;
		}
	}
	return false;
}