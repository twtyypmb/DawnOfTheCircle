#include "CommonResource.h"
#include "string.h"

extern HWND _window;
extern PIMAGE _renderer;
extern PIMAGE _total_image;
extern PIMAGE _total_image_back;
extern PIMAGE _shock_wave[4];
extern PIMAGE _doors;
extern PIMAGE _game_log;
extern PIMAGE _game_over;
extern PIMAGE _the_end;
extern PIMAGE _description;
PIMAGE total_surface;
PIMAGE total_back_surface;
PIMAGE  single_total_surface[SINGLE_TOTAL_SURFACE_MAX_LENGTH];


void FreeSDLSurface(PIMAGE p) { if (p != NULL)delimage(p); }
void FreeSDLTexture(PIMAGE p) { if (p != NULL)delimage(p); }


bool InitResource(void)
{
	memset(single_total_surface, 0, SINGLE_TOTAL_SURFACE_MAX_LENGTH);
	initgraph(640, 480);
	randomize();
	setrendermode(RENDER_MANUAL);
	SetWindowText(GetWindow(), TEXT("CASTALVANIA---DAWN OF THE CIRCLE"));
	return true;
}

HWND GetWindow(void)
{
	if (_window == NULL)
	{
		_window = getHWnd();
	}

	return _window;
}

PIMAGE GetRenderer(void)
{


	return _renderer;
}






// 初始化公共资源
PIMAGE GetTotalSurface()
{
	if (NULL == total_surface)
	{
		total_surface = newimage();
		getimage(total_surface, "resource/image/total.bmp", 0, 0);
	}
	return total_surface;
}

PIMAGE GetTotalBackSurface()
{
	if (NULL == total_back_surface)
	{
		total_back_surface = newimage();
		getimage(total_back_surface, "resource/image/total_back.bmp", 0, 0);

	}
	return total_back_surface;
}





PIMAGE* GetShockWave()
{
	/*if(NULL==_shock_wave[0])
	{
	   _shock_wave[0] = LoadImage("resource/image/shock_wave_0.jpg");
	   _shock_wave[1] = LoadImage("resource/image/shock_wave_1.jpg");
	   _shock_wave[2] = LoadImage("resource/image/shock_wave_2.jpg");
	   _shock_wave[3] = LoadImage("resource/image/shock_wave_3.jpg");
	}*/
	return _shock_wave;
}

PIMAGE GetDescription()
{
	if (NULL == _description)
	{
		//_description = LoadImage("resource/image/description.jpg");
	}
	return _description;
}

PIMAGE GetDoors()
{
	if (NULL == _doors)
	{
		//_doors = LoadImage("resource/image/doors.jpg");
	}
	return _doors;
}

PIMAGE GetGameLogo()
{
	if (NULL == _game_log)
	{
		//_game_log = LoadImage("resource/image/game_logo.jpg");
	}
	return _game_log;
}

PIMAGE GetTheEnd()
{
	if (NULL == _the_end)
	{
		//_the_end = LoadImage("resource/image/the_end.jpg");
	}
	return _the_end;
}


PIMAGE GetGameOver()
{
	if (NULL == _game_over)
	{
		//_game_over = LoadImage("resource/image/game_over.jpg");
	}
	return _game_over;
}


// 释放公共资源
void FreeAllCommonResource(void)
{
	delimage(_total_image);
	//SDL_free(_total_image_back);

	if (NULL != _renderer)
	{
		delimage(_renderer);
		_renderer = NULL;
	}

	if (NULL != _window)
	{
		/*delimage(_window);
		_window= NULL;*/
	}
}
PIMAGE GetSingleImage(int number)
{
	PIMAGE result = single_total_surface[number];
	if (result == NULL)
	{
		result = newimage(OBJECT_WIDTH, OBJECT_HEIGHT);
		PIMAGE total_img1, total_img2, img1, img2;
		total_img1 = newimage();
		total_img2 = newimage();
		img1 = newimage();
		img2 = newimage();

		getimage(total_img1, "resource/image/total_back.bmp", 0, 0);
		getimage(total_img2, "resource/image/total_back.bmp", 0, 0);
		getimage(img1, total_img1, number % 11 * 32, number / 11 * 32, 32, 32);
		getimage(img2, total_img2, (number % 11) * 32, number / 11 * 32, 32, 32);
		putimage_transparent(img2, img1, 0, 0, 0x000000, 0, 0, 32, 32);//图像重合

		getimage(img2, total_img2, 1 * 32, 17 * 32, 32, 32);
	}

	return result;
}

