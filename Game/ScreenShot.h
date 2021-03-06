#pragma once

void DrawSaveScreenShotLog(const char* file_name, int* change_flag = FALSE);

// 引数 : 撮影する範囲
// 描画後の一番最後に呼ぶ
bool SaveScreenShotToPng(int x1, int y1, int x2, int y2, char* name = NULL, int* change_flag = FALSE);

// 引数 : 撮影する範囲
// 描画後の一番最後に呼ぶ
bool SaveScreenShotToJpg(int x1, int y1, int x2, int y2, char* name = NULL, int* change_flag = FALSE);
