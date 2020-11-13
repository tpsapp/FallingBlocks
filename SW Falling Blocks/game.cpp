// SW Falling Blocks
// game.cpp

#include "game.h"

Game::Game()
{
}

Game::~Game()
{
	Done();
}

void Game::Cheat()
{
	cheat = !cheat;
}

int Game::CollisionTest(int nx, int ny)
{
	int newx = sPiece.x + nx;
	int newy = sPiece.y + ny;
	int x, y;

	for (x = 0; x < 4; x++)
	{
		for (y = 0; y < 4; y++)
		{
			if (sPiece.size[x][y] != TILENODRAW)
			{
				if (newx + x < 0 || newx + x > MAPWIDTH - 1 || newy + y < 0 || newy + y > MAPHEIGHT - 1)
				{
					return 1;
				}
			}
		}
	}

	for (x = 0; x < MAPWIDTH; x++)
	{
		for (y = 0; y < MAPHEIGHT; y++)
		{
			if (x >= newx && x < newx + 4)
			{
				if (y >= newy && y < newy + 4)
				{
					if (Map[x][y] != TILEBLACK)
					{
						if (sPiece.size[x - newx][y - newy] != TILENODRAW)
						{
							return 1;
						}
					}
				}
			}
		}
	}

	return 0;
}

void Game::Debug()
{
	debug = !debug;
}

void Game::DecLevel()
{
	if (level > 1)
	{
		level--;
	}
}

void Game::DecRows()
{
	if (rows > 0)
	{
		rows--;
	}
}

void Game::Done()
{
	bmoMap.Destroy();
	bmoBlocks.Destroy();
	bmoScore.Destroy();
}

void Game::DrawLevel()
{
	int tmpLevel = level;
	int x;

	BitBlt(bmoMap, 11 * TILESIZE, 25 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILEL * TILESIZE, 0, SRCPAINT);
	BitBlt(bmoMap, 12 * TILESIZE, 25 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILEE * TILESIZE, 0, SRCPAINT);
	BitBlt(bmoMap, 13 * TILESIZE, 25 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILEV * TILESIZE, 0, SRCPAINT);
	BitBlt(bmoMap, 14 * TILESIZE, 25 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILEE * TILESIZE, 0, SRCPAINT);
	BitBlt(bmoMap, 15 * TILESIZE, 25 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILEL * TILESIZE, 0, SRCPAINT);

	for (x = 6; x > 0; x--)
	{
		int temp = tmpLevel % 10;

		BitBlt(bmoMap, (x + 10) * TILESIZE, 26 * TILESIZE, TILESIZE, TILESIZE, bmoScore, temp * TILESIZE, 0, SRCPAINT);

		tmpLevel = tmpLevel / 10;
		if (tmpLevel <= 0)
		{
			break;
		}
	}
}

void Game::DrawMap()
{
	int xmy, ymx;

	for (xmy = MAPWIDTH; xmy < MAPWIDTH + GREY; xmy++)
	{
		for (ymx = 0; ymx < MAPHEIGHT; ymx++)
		{
			DrawTile(xmy, ymx, TILEGREY);
		}
	}

	for (xmy = 0; xmy < 4; xmy++)
	{
		for (ymx = 0; ymx < 4; ymx++)
		{
			if (sPrePiece.size[xmy][ymx] != TILENODRAW)
			{
				DrawTile(sPrePiece.x + xmy, sPrePiece.y + ymx, sPrePiece.size[xmy][ymx]);
			}
		}
	}

	for (xmy = 0; xmy < MAPWIDTH; xmy++)
	{
		for (ymx = 0; ymx < MAPHEIGHT; ymx++)
		{
			DrawTile(xmy, ymx, Map[xmy][ymx]);
		}
	}

	for (xmy = 0; xmy < 4; xmy++)
	{
		for (ymx = 0; ymx < 4; ymx++)
		{
			if (sPiece.size[xmy][ymx] != TILENODRAW)
			{
				DrawTile(sPiece.x + xmy, sPiece.y + ymx, sPiece.size[xmy][ymx]);
			}
		}
	}

	InvalidateRect(hWndMain, nullptr, FALSE);

	DrawRows();
	DrawLevel();
	DrawScore();
	DrawStatus();
}

void Game::DrawRows()
{
	int tmpRows = rows;
	int x;

	BitBlt(bmoMap, 11 * TILESIZE, 23 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILER * TILESIZE, 0, SRCPAINT);
	BitBlt(bmoMap, 12 * TILESIZE, 23 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILEO * TILESIZE, 0, SRCPAINT);
	BitBlt(bmoMap, 13 * TILESIZE, 23 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILEW * TILESIZE, 0, SRCPAINT);
	BitBlt(bmoMap, 14 * TILESIZE, 23 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILES * TILESIZE, 0, SRCPAINT);

	for (x = 6; x > 0; x--)
	{
		int temp = tmpRows % 10;
		BitBlt(bmoMap, (x + 10) * TILESIZE, 24 * TILESIZE, TILESIZE, TILESIZE, bmoScore, temp * TILESIZE, 0, SRCPAINT);
		tmpRows = tmpRows / 10;
		if (tmpRows <= 0)
		{
			break;
		}
	}
}

void Game::DrawScore()
{
	int tmpScore = score;
	int x;

	BitBlt(bmoMap, 11 * TILESIZE, 27 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILES * TILESIZE, 0, SRCPAINT);
	BitBlt(bmoMap, 12 * TILESIZE, 27 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILEC * TILESIZE, 0, SRCPAINT);
	BitBlt(bmoMap, 13 * TILESIZE, 27 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILEO * TILESIZE, 0, SRCPAINT);
	BitBlt(bmoMap, 14 * TILESIZE, 27 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILER * TILESIZE, 0, SRCPAINT);
	BitBlt(bmoMap, 15 * TILESIZE, 27 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILEE * TILESIZE, 0, SRCPAINT);

	for (x = 6; x > 0; x--)
	{
		int temp = tmpScore % 10;
		BitBlt(bmoMap, (x + 10) * TILESIZE, 28 * TILESIZE, TILESIZE, TILESIZE, bmoScore, temp * TILESIZE, 0, SRCPAINT);
		tmpScore = tmpScore / 10;
		if (tmpScore <= 0)
		{
			break;
		}
	}
}

void Game::DrawStatus()
{
	int tile;
	if (cheat)
	{
		tile = TILEORANGE;
	}
	else
	{
		tile = TILEGREY;
	}

	BitBlt(bmoMap, 16 * TILESIZE, 0, TILESIZE, TILESIZE, bmoBlocks, tile * TILESIZE, 0, SRCPAINT);

	if (debug)
	{
		tile = TILERED;
	}
	else
	{
		tile = TILEGREY;
	}

	BitBlt(bmoMap, 17 * TILESIZE, 0, TILESIZE, TILESIZE, bmoBlocks, tile * TILESIZE, 0, SRCPAINT);
}

void Game::DrawTile(int x, int y, int tile)
{
	BitBlt(bmoMap, x * TILESIZE, y * TILESIZE, TILESIZE, TILESIZE, bmoBlocks, tile * TILESIZE, TILESIZE, SRCAND);
	BitBlt(bmoMap, x * TILESIZE, y * TILESIZE, TILESIZE, TILESIZE, bmoBlocks, tile * TILESIZE, 0, SRCPAINT);
}

bool Game::GameOver()
{
	int msgBoxID = MessageBox(hWndMain, "Play Again?", "Game Over", MB_ICONERROR | MB_YESNO);

	switch (msgBoxID)
	{
	case IDYES:
		{
			return true;
		}
		break;
	case IDNO:
		{
			return false;
		}
		break;
	default:
		{
			return false;
		}
		break;
	}
}

bool Game::GetCheat()
{
	return cheat;
}

bool Game::GetDebug()
{
	return debug;
}

int Game::GetMapHeight()
{
	return TILESIZE * MAPHEIGHT;
}

int Game::GetMapWidth()
{
	return TILESIZE * MAPWIDTH + TILESIZE * GREY;
}

bool Game::GetPaused()
{
	return paused;
}

bool Game::Init(HWND wnd)
{
	GAMESTARTED = false;
	cheat = false;
	debug = false;
	paused = false;

	hWndMain = wnd;

	HDC hdc = GetDC(wnd);
	bmoMap.Create(hdc, GetMapWidth(), GetMapHeight());

	ReleaseDC(wnd, hdc);

	bmoBlocks.Load(nullptr, "blocks.bmp");
	bmoScore.Load(nullptr, "numbers.bmp");
	bmoLetters.Load(nullptr, "letters.bmp");

	return true;
}

void Game::IncLevel()
{
	level++;
}

void Game::IncRows()
{
	rows++;
}

void Game::Loop()
{
	speed = level / 3;

	if (paused)
	{
		return;
	}

	if (speed > 5)
	{
		speed = 5;
	}

	if ((GetTickCount() - start_time) > 1000)
	{
		if (cheat)
		{
			Move(0, 0);
		}
		else
		{
			if (speed == 0)
			{
				Move(0, 1);
			}
			else
			{
				Move(0, speed);
			}
		}

		start_time = GetTickCount();
	}

	DrawMap();
}

void Game::Move(int x, int y)
{
	if (CollisionTest(x, y))
	{
		if (y >= 1)
		{
			if (y > 1)
			{
				Move(x, y - 1);
			}
			else if (sPiece.y < 1)
			{
				if (GameOver())
				{
					NewGame();
				}
				else
				{
					DestroyWindow(hWndMain);
				}
			}
			else
			{
				int i, j;

				for (i = 0; i < 4; i++)
				{
					for (j = 0; j < 4; j++)
					{
						if (sPiece.size[i][j] != TILENODRAW)
						{
							Map[sPiece.x + i][sPiece.y + j] = sPiece.size[i][j];
						}
					}
				}

				for (j = 0; j < MAPHEIGHT; j++)
				{
					bool filled = true;

					for (i = 0; i < MAPWIDTH; i++)
					{
						if (Map[i][j] == TILEBLACK)
						{
							filled = false;
							fourrows = 0;
						}
					}

					if (filled)
					{
						RemoveRow(j);
					}
				}

				NewBlock(8);
			}
		}
	}
	else
	{
		sPiece.x += x;
		sPiece.y += y;
	}
}

void Game::NewBlock(int block)
{
	srand(GetTickCount());

	sPrePiece.x = MAPWIDTH + GREY / 4;
	sPrePiece.y = GREY / 4;

	if (!GAMESTARTED)
	{
		GAMESTARTED = true;

		sPiece.x = MAPWIDTH / 2 - 2;
		sPiece.y = -1;

		SetBlock(&sPiece, rand() % 8);
		SetBlock(&sPrePiece, rand() % 8);
	}
	else
	{
		if (block > 7)
		{
			sPiece = sPrePiece;
			sPiece.x = MAPWIDTH / 2 - 2;
			sPiece.y = -1;

			SetBlock(&sPrePiece, rand() % 8);
		}
		else
		{
			SetBlock(&sPiece, block);
		}
	}
}

void Game::NewGame()
{
	score = 0;
	level = 1;
	rows = 0;
	fourrows = 0;
	speed = 0;

	start_time = GetTickCount();
	GAMESTARTED = false;

	for (int x = 0; x < MAPWIDTH; x++)
	{
		for (int y = 0; y < MAPHEIGHT + 1; y++)
		{
			if (y == MAPHEIGHT)
			{
				Map[x][y] = TILEGREY;
			}
			else
			{
				Map[x][y] = TILEBLACK;
			}
		}
	}

	NewBlock(8);
}

void Game::Pause()
{
	paused = !paused;
}

void Game::RemoveRow(int row)
{
	int x, y;
	int counter = 0;

	for (x = 0; x < MAPWIDTH; x++)
	{
		for (y = row; y > 0; y--)
		{
			Map[x][y] = Map[x][y - 1];
		}
	}

	score++;
	rows++;
	fourrows++;

	if (rows > 10 * level)
	{
		level++;
		rows = 0;
	}

	if (fourrows == 4)
	{
		score++;
		fourrows = 0;
	}
}

void Game::RotateBlock(bool direction)
{
	int i, j, temp[4][4];

	if (direction)
	{
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				temp[3 - j][i] = sPiece.size[i][j];
			}
		}
	}
	else
	{
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				temp[j][3 - i] = sPiece.size[i][j];
			}
		}
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (temp[i][j] != TILENODRAW)
			{
				if (sPiece.x + i < 0 || sPiece.x + i > MAPWIDTH - 1 || sPiece.y + j < 0 || sPiece.y + j > MAPHEIGHT - 1)
				{
					return;
				}
			}
		}
	}

	for (int x = 0; x < MAPWIDTH; x++)
	{
		for (int y = 0; y < MAPHEIGHT; y++)
		{
			if (x >= sPiece.x && x < sPiece.x + 4)
			{
				if (y >= sPiece.y && y < sPiece.y + 4)
				{
					if (Map[x][y] != TILEBLACK)
					{
						if (temp[x - sPiece.x][y - sPiece.y] != TILENODRAW)
						{
							return;
						}
					}
				}
			}
		}
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			sPiece.size[i][j] = temp[i][j];
		}
	}
}

void Game::SetBlock(Piece* piece, int block)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			piece->size[i][j] = TILENODRAW;
		}
	}

	//   Block Configurations
	//   0   1   2   3   4    5   6   7
	//   X                            
	//   X   XX   X  XX   XX  XX  XX  X
	//   X   XX  XXX  XX XX    X  X  XXX
	//   X                     X  X   X

	switch (block)
	{
	case 0:
		{
			piece->size[1][0] = TILERED;
			piece->size[1][1] = TILERED;
			piece->size[1][2] = TILERED;
			piece->size[1][3] = TILERED;
			if (block > 7) piece->y = 0;
		}
		break;
	case 1:
		{
			piece->size[1][1] = TILEBLUE;
			piece->size[1][2] = TILEBLUE;
			piece->size[2][1] = TILEBLUE;
			piece->size[2][2] = TILEBLUE;
		}
		break;
	case 2:
		{
			piece->size[1][1] = TILESTEEL;
			piece->size[0][2] = TILESTEEL;
			piece->size[1][2] = TILESTEEL;
			piece->size[2][2] = TILESTEEL;
		}
		break;
	case 3:
		{
			piece->size[0][1] = TILEYELLOW;
			piece->size[1][1] = TILEYELLOW;
			piece->size[1][2] = TILEYELLOW;
			piece->size[2][2] = TILEYELLOW;
		}
		break;
	case 4:
		{
			piece->size[2][1] = TILEGREEN;
			piece->size[1][1] = TILEGREEN;
			piece->size[1][2] = TILEGREEN;
			piece->size[0][2] = TILEGREEN;
		}
		break;
	case 5:
		{
			piece->size[1][1] = TILEWHITE;
			piece->size[2][1] = TILEWHITE;
			piece->size[2][2] = TILEWHITE;
			piece->size[2][3] = TILEWHITE;
		}
		break;
	case 6:
		{
			piece->size[2][1] = TILEPURPLE;
			piece->size[1][1] = TILEPURPLE;
			piece->size[1][2] = TILEPURPLE;
			piece->size[1][3] = TILEPURPLE;
		}
		break;
	case 7:
		{
			piece->size[1][1] = TILEORANGE;
			piece->size[2][0] = TILEORANGE;
			piece->size[2][1] = TILEORANGE;
			piece->size[2][2] = TILEORANGE;
			piece->size[3][1] = TILEORANGE;
		}
		break;
	}
}
