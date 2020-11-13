// SW Falling Blocks
// bitmapobject.h

#ifndef BITMAPOBJECT_H
#define BITMAPOBJECT_H
#pragma once

#include <windows.h>

class BitMapObject
{
private:
	HDC hdcMemory;
	HBITMAP hbmNewBitMap;
	HBITMAP hbmOldBitMap;
	int iWidth;
	int iHeight;

public:
	BitMapObject();
	~BitMapObject();
	void Load(HDC hdcCompatible, LPCTSTR lpszFilename);
	void Create(HDC hdcCompatible, int width, int height);
	void Destroy();
	int GetWidth();
	int GetHeight();
	operator HDC();
};

#endif
