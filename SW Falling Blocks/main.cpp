// SW Falling Blocks
// main.cpp

#include "main.h"

LRESULT CALLBACK TheWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	RECT rc;

	switch (uMsg)
	{
	case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE)
			{
				DestroyWindow(hwnd);
				return 0;
			}
			if (wParam == VK_PAUSE)
			{
				gFB.Pause();
				return 0;
			}
			if (gFB.GetPaused())
			{
				return 0;
			}
			if (wParam == VK_DOWN)
			{
				gFB.Move(0, 1);
				return 0;
			}
			if (wParam == VK_UP)
			{
				gFB.RotateBlock(true);
				return 0;
			}
			if (wParam == VK_SPACE)
			{
				gFB.RotateBlock(false);
				return 0;
			}
			if (wParam == VK_LEFT)
			{
				gFB.Move(-1, 0);
				return 0;
			}
			if (wParam == VK_RIGHT)
			{
				gFB.Move(1, 0);
				return 0;
			}
			if (wParam == VK_TAB)
			{
				gFB.Cheat();
				return 0;
			}
			else
			{
				if (wParam == VK_SHIFT)
				{
					if (gFB.GetCheat() || gFB.GetDebug())
					{
						gFB.Move(0, -1);
					}
					return 0;
				}
				if (wParam == VK_F1)
				{
					if (gFB.GetCheat() || gFB.GetDebug())
					{
						gFB.NewBlock(8);
					}
					return 0;
				}
				if (wParam == VK_F12)
				{
					gFB.Debug();
					return 0;
				}
				else
				{
					if (wParam == VK_F2)
					{
						if (gFB.GetDebug())
						{
							gFB.NewBlock(0);
						}
						return 0;
					}
					if (wParam == VK_F3)
					{
						if (gFB.GetDebug())
						{
							gFB.NewBlock(1);
						}
						return 0;
					}
					if (wParam == VK_F4)
					{
						if (gFB.GetDebug())
						{
							gFB.NewBlock(2);
						}
						return 0;
					}
					if (wParam == VK_F5)
					{
						if (gFB.GetDebug())
						{
							gFB.NewBlock(3);
						}
						return 0;
					}
					if (wParam == VK_F6)
					{
						if (gFB.GetDebug())
						{
							gFB.NewBlock(4);
						}
						return 0;
					}
					else
					{
						if (wParam == VK_F7)
						{
							if (gFB.GetDebug())
							{
								gFB.NewBlock(5);
							}
							return 0;
						}
						if (wParam == VK_F8)
						{
							if (gFB.GetDebug())
							{
								gFB.NewBlock(6);
							}
							return 0;
						}
						else if (wParam == VK_F9)
						{
							if (gFB.GetDebug())
							{
								gFB.NewBlock(7);
							}
							return 0;
						}
						else
						{
							if (wParam == VK_PRIOR)
							{
								if (gFB.GetDebug())
								{
									gFB.IncLevel();
								}
								return 0;
							}
							if (wParam == VK_NEXT)
							{
								if (gFB.GetDebug())
								{
									gFB.DecLevel();
								}
								return 0;
							}
							else
							{
								if (wParam == VK_HOME)
								{
									if (gFB.GetDebug())
									{
										gFB.IncRows();
									}
									return 0;
								}
								if (wParam == VK_END)
								{
									if (gFB.GetDebug())
									{
										gFB.DecRows();
									}
									return 0;
								}
							}
						}
					}
				}
			}
		}
		break;
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;

			HDC hdc = BeginPaint(hwnd, &ps);
			BitBlt(hdc, 0, 0, gFB.GetMapWidth(), gFB.GetMapHeight(), gFB.bmoMap, 0, 0, SRCCOPY);
			EndPaint(hwnd, &ps);

			return 0;
		}
		break;
	case WM_CREATE:
		{
			SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);

			MoveWindow(hwnd, ((rc.right - rc.left) - 320) / 2, ((rc.bottom - rc.top) - 240) / 2, 320, 240, false);

			return 0;
		}
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX wcx;
	wcx.cbSize = sizeof(WNDCLASSEX);
	wcx.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcx.lpfnWndProc = TheWindowProc;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = hInstance;
	wcx.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcx.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcx.lpszMenuName = nullptr;
	wcx.lpszClassName = WINDOWCLASS;
	wcx.hIconSm = nullptr;

	if (!RegisterClassEx(&wcx))
	{
		return 0;
	}

	HWND hWndMain = CreateWindowEx(0, WINDOWCLASS, WINDOWTITLE, WS_BORDER | WS_SYSMENU | WS_CAPTION | WS_VISIBLE, 0, 0,
	                               gFB.GetMapWidth(), gFB.GetMapHeight(), nullptr, nullptr, hInstance, nullptr);

	if (!hWndMain)
	{
		return 0;
	}

	RECT rcTemp;
	SetRect(&rcTemp, 0, 0, gFB.GetMapWidth(), gFB.GetMapHeight());
	AdjustWindowRect(&rcTemp, WS_BORDER | WS_SYSMENU | WS_CAPTION | WS_VISIBLE, FALSE);
	SetWindowPos(hWndMain, nullptr, 0, 0, rcTemp.right - rcTemp.left, rcTemp.bottom - rcTemp.top, SWP_NOMOVE);

	if (!gFB.Init(hWndMain))
	{
		return 0;
	}
	FillRect(gFB.bmoMap, &rcTemp, (HBRUSH)GetStockObject(BLACK_BRUSH));
	gFB.NewGame();

	MSG msg;
	for (; ;)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		gFB.Loop();
	}

	gFB.Done();
	return msg.wParam;
}
