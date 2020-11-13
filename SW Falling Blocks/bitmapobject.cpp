// SW Falling Blocks
// bitmapobject.cpp

#include "bitmapobject.h"

BitMapObject::BitMapObject()
{
	hdcMemory = nullptr;
	hbmNewBitMap = nullptr;
	hbmOldBitMap = nullptr;
	iWidth = 0;
	iHeight = 0;
}

BitMapObject::~BitMapObject()
{
	if (hdcMemory)
	{
		Destroy();
	}
}

void BitMapObject::Load(HDC hdcCompatible, LPCTSTR lpszFilename)
{
	if (hdcMemory)
	{
		Destroy();
	}

	hdcMemory = CreateCompatibleDC(hdcCompatible);
	hbmNewBitMap = (HBITMAP)LoadImage(nullptr, lpszFilename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbmOldBitMap = (HBITMAP)SelectObject(hdcMemory, hbmNewBitMap);
	BITMAP bmp;
	GetObject(hbmNewBitMap, sizeof(BITMAP), (LPVOID)&bmp);
	iWidth = bmp.bmWidth;
	iHeight = bmp.bmHeight;
}

void BitMapObject::Create(HDC hdcCompatible, int width, int height)
{
	if (hdcMemory)
	{
		Destroy();
	}

	hdcMemory = CreateCompatibleDC(hdcCompatible);
	hbmNewBitMap = CreateCompatibleBitmap(hdcCompatible, width, height);
	hbmOldBitMap = (HBITMAP)SelectObject(hdcMemory, hbmNewBitMap);
	iWidth = width;
	iHeight = height;
}

void BitMapObject::Destroy()
{
	SelectObject(hdcMemory, hbmOldBitMap);
	DeleteObject(hbmNewBitMap);
	DeleteDC(hdcMemory);
	hdcMemory = nullptr;
	hbmNewBitMap = nullptr;
	hbmOldBitMap = nullptr;
	iWidth = 0;
	iHeight = 0;
}

BitMapObject::operator HDC()
{
	return hdcMemory;
}

int BitMapObject::GetWidth()
{
	return iWidth;
}

int BitMapObject::GetHeight()
{
	return iHeight;
}
