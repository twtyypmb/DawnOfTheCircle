// DawnOfTheCircle.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "game_system.h"
#include "CommonResource.h"

using namespace std;
char file[255];
bool mainloop(void)
{
	game_config gameconfig;
	vector<int > key(2);//定义按键对象

	/*************定义框架****************/
	window_area role_property, game_scene, key_detail, help_scene, dialog_scene;
	gameconfig.pgame_scene = &game_scene;
	gameconfig.prole_property = &role_property;
	gameconfig.pkey_detail = &key_detail;
	gameconfig.phelp_scene = &help_scene;
	gameconfig.pdialog_scene = &dialog_scene;

	/***********初始化子窗口区域***********/
	role_property.init_area(2 * 32, 1 * 32, 4 * 32, 7 * 32, 0);//参数：左上角坐标，宽度，高度，区域编号
	key_detail.init_area(2 * 32, 8 * 32 + 5, 4 * 32, 3 * 32, 1);
	help_scene.init_area(2 * 32, 11 * 32 + 10, 4 * 32, 3 * 32, 2);
	game_scene.init_area(7 * 32, 2 * 32, 11 * 32, 11 * 32, 3);
	dialog_scene.init_area(3 * 32, 3 * 32, 5 * 32, 4 * 32, 4);

	/***********定义角色信息***********/
	role protagonist;
	gameconfig.prole = &protagonist;

	/*************定义楼层*****************/
	my_floor allfloor[23];
	init_allfloor(allfloor);
	gameconfig.pall_floor = allfloor;


	while (1)
	{
		main_menu(gameconfig, key);

		gameconfig.game_control.reset();
		protagonist.init_role();
		reset_allfloor(allfloor);
		update_gameconfig(gameconfig);
		protagonist.set_role_position(gameconfig.pall_floor[gameconfig.current_floor_number].role_init_position[0]);

		switch (key[0])
		{
		case 0:
			play_prelude(gameconfig);
			gameconfig.event_number = 18;
			gameconfig.game_control[0] = 1;
			break;
		case 1:load_data(gameconfig);break;
		case 2:break;
		case 3:return true;
		}

		game_core(gameconfig, key);

		if (gameconfig.game_control[3])
		{
			gameover_cartoon(gameconfig);
		}

		if (gameconfig.game_control[2])
		{
			play_finale(gameconfig);
		}
	}

	return true;
}

int main(int argc, char *argv[])
{
	//setinitmode(INIT_DEFAULT&0x0ff);//隐藏EGELOGO
	InitResource();
	mainloop();
	closegraph();
	return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
