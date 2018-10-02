#pragma once

void DrawSaveScreenShotLog(const char* file_name, int* change_flag = FALSE);

// ˆø” : B‰e‚·‚é”ÍˆÍ
// •`‰æŒã‚Ìˆê”ÔÅŒã‚ÉŒÄ‚Ô
bool SaveScreenShotToPng(int x1, int y1, int x2, int y2, char* name = NULL, int* change_flag = FALSE);

// ˆø” : B‰e‚·‚é”ÍˆÍ
// •`‰æŒã‚Ìˆê”ÔÅŒã‚ÉŒÄ‚Ô
bool SaveScreenShotToJpg(int x1, int y1, int x2, int y2, char* name = NULL, int* change_flag = FALSE);
