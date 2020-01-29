#include "game_system.h"


using namespace std;

bool receive_key(vector<int> &direction)
{
	int key_flag = 0;
	int key = 0;
	if (kbhit())//当有键按下
	{
		key = getch();
		if (224 == key)//如果是方向键
		{
			key = getch();
			switch (key)
			{
			case 72:key = 119;key_flag = 1;break;
			case 80:key = 115;key_flag = 1;break;
			case 75:key = 97;key_flag = 1;break;
			case 77:key = 100;key_flag = 1;break;//up,down,left,right
			}
		}
		else
		{
			switch (key)
			{
			case 49:break;//number:1
			case 50:break;//number 2
			case 87:
			case 119:key = 119;key_flag = 1;break;//'W'
			case 83:
			case 115:key = 115;key_flag = 1;break;//'S'
			case 65:
			case 97:key = 97;key_flag = 1;break;//'A'
			case 68:
			case 100:key = 100;key_flag = 1;break;//'D'
			case 32:key_flag = 4;break;//空格键
			case 74:
			case 106:key = 106;key_flag = 2;break;//'j'
			case 75:
			case 107:key = 107;key_flag = 2;break;//'k'
			case 76:
			case 108:key = 108;key_flag = 2;break;//'L'
			case 80:
			case 112:key = 112;key_flag = 2;break;//'P'
			case 85:
			case 117:key = 117;key_flag = 2;break;//'U'
			case 13:key_flag = 6;break;//回车
			default:return false;
			}
		}
		direction[0] = key_flag;//key_flag为0时代表非法按键，1为角色操作，2为系统操作
		direction[1] = key;
		return true;
	}
	return false;
}



bool battle_process(game_config &gameconfig, monster &current_monster)
{
	gameconfig.pdialog_scene->clear_area();

	static int monster_lif(1);
	//static int role_lif(1);
	int monster_damage, role_damage;

	monster_damage = current_monster.monster_info["attack"] - gameconfig.prole->role_info["defence"];
	role_damage = gameconfig.prole->role_info["attack"] - current_monster.monster_info["defence"];
	if (monster_damage < 0)
	{
		monster_damage = 0;
		if (role_damage < 0)
		{
			monster_damage = 100;
		}
	}
	if (role_damage < 0)
	{
		role_damage = 0;
	}

	if (!monster_lif)
	{
		gameconfig.game_control[0] = 0;
	}
	if (!gameconfig.prole->role_info["life"])
	{
		gameconfig.game_control[0] = 0;
		gameconfig.game_control[3] = 1;
	}


	if (monster_lif > 0 && gameconfig.prole->role_info["life"] > 0)
	{
		if (gameconfig.event_clock / 20 * 20 == gameconfig.event_clock)//回合时间：20倍事件时钟
		{
			gameconfig.prole->role_info["life"] -= monster_damage;
			if (gameconfig.prole->role_info["life"] <= 0)
			{
				gameconfig.prole->role_info["life"] = 0;
			}
		}
		if ((gameconfig.event_clock + 10) / 20 * 20 == gameconfig.event_clock + 10)
		{
			monster_lif -= role_damage;
			if (monster_lif <= 0)
			{
				monster_lif = 0;
			}
		}
	}

	if (!gameconfig.event_clock)
	{
		monster_lif = current_monster.monster_info["life"];

	}

	//打印战斗数值
	setcolor(EGERGB(0xff, 0xff, 0xff), gameconfig.pdialog_scene->area);
	setfont(25, 0, "宋体", gameconfig.pdialog_scene->area);
	setbkmode(TRANSPARENT, gameconfig.pdialog_scene->area);//字体底色透明
	string tempstr[3];
	PIMAGE total_img1, total_img2, img1, img2;
	total_img1 = newimage();
	total_img2 = newimage();
	img1 = newimage();
	img2 = newimage();

	getimage(total_img1, "resource\\image\\total_back.bmp", 0, 0);
	getimage(total_img2, "resource\\image\\total_back.bmp", 0, 0);
	getimage(img1, total_img1, (current_monster.monster_img_number[gameconfig.event_clock / 10 % 2][0] % 11) * 32, current_monster.monster_img_number[gameconfig.event_clock / 10 % 2][0] / 11 * 32, 32, 32);
	getimage(img2, total_img2, ((current_monster.monster_img_number[gameconfig.event_clock / 10 % 2][1] + 1) % 11) * 32, (current_monster.monster_img_number[gameconfig.event_clock / 10 % 2][1] + 1) / 11 * 32, 32, 32);
	putimage_transparent(img2, img1, 0, 0, 0x000000, 0, 0, 32, 32);//图像重合
	putimage_transparent(gameconfig.pdialog_scene->area, img2, 6, 6, 0x80ffff);
	getimage(img2, total_img2, 1 * 32, 17 * 32, 32, 32);
	putimage_transparent(gameconfig.pdialog_scene->area, img2, 4 * 32 - 6, 6, 0x80ffff);

	print_frame(*(gameconfig.pdialog_scene), *(gameconfig.pgame_scene));

	setfont(26, 0, "宋体", gameconfig.pdialog_scene->area);
	outtextxy(getwidth(gameconfig.pdialog_scene->area) / 2 - 13, 0 * 20 + 10, "VS", gameconfig.pdialog_scene->area);
	setfont(16, 0, "宋体", gameconfig.pdialog_scene->area);

	tempstr[0] = "生命:";
	outtextxy(5, 1 * 20 + 25, tempstr[0].c_str(), gameconfig.pdialog_scene->area);
	tempstr[0] = ":生命";
	outtextxy(getwidth(gameconfig.pdialog_scene->area) - tempstr[0].size() * 8 - 5, 1 * 20 + 25, tempstr[0].c_str(), gameconfig.pdialog_scene->area);

	tempstr[0] = int2str(monster_lif);
	tempstr[1] = "攻击:" + int2str(current_monster.monster_info["attack"]);
	tempstr[2] = "防御:" + int2str(current_monster.monster_info["defence"]);
	for (int i = 0; i < 3; ++i)
	{
		outtextxy(5, (i + 2) * 20 + 25, tempstr[i].c_str(), gameconfig.pdialog_scene->area);
	}

	tempstr[0] = int2str(gameconfig.prole->role_info["life"]);
	tempstr[1] = int2str(gameconfig.prole->role_info["attack"]) + ":攻击";
	tempstr[2] = int2str(gameconfig.prole->role_info["defence"]) + ":防御";
	for (int i = 0; i < 3; ++i)
	{
		outtextxy(getwidth(gameconfig.pdialog_scene->area) - tempstr[i].size() * 8 - 5, (i + 2) * 20 + 25, tempstr[i].c_str(), gameconfig.pdialog_scene->area);
	}

	putimage(gameconfig.pgame_scene->area, gameconfig.pdialog_scene->position[0], gameconfig.pdialog_scene->position[1], gameconfig.pdialog_scene->area);

	if (!gameconfig.game_control[0])
	{
		monster_lif = 1;
	}

	delimage(total_img1);
	delimage(total_img2);
	delimage(img1);
	delimage(img2);
	return true;
}


bool update_floor_data(game_config &gameconfig)
{
	update_gameconfig(gameconfig);
	PIMAGE total_img1, total_img2, img1, img2;
	total_img1 = newimage();
	getimage(total_img1, "resource\\image\\total_back.bmp", 0, 0);
	total_img2 = newimage();
	getimage(total_img2, "resource\\image\\total.bmp", 0, 0);
	img1 = newimage();
	img2 = newimage();
	getimage(img1, total_img2, 5 * 32, 0, 32, 32);

	int x, y;
	for (y = 0; y < 11; ++y)
	{
		for (x = 0; x < 11; ++x)
		{
			putimage(gameconfig.pgame_scene->area, x * 32, y * 32, img1);//画地板
		}
	}
	x = y = 0;

	monster current_monster;
	int monster_img1, monster_img2;
	monster_img1 = monster_img2 = 0;

	for (x = 0; x < 11; ++x)
	{
		for (y = 0; y < 11; ++y)
		{
			if (gameconfig.pall_floor[gameconfig.current_floor_number].floor_info[x][y] == 5)
			{
				continue;//地板不用画
			}
			current_monster.init_monster(gameconfig.pall_floor[gameconfig.current_floor_number].floor_info[x][y]);
			monster_img1 = current_monster.monster_img_number[gameconfig.floor_clock / 10 % 2][0];
			monster_img2 = current_monster.monster_img_number[gameconfig.floor_clock / 10 % 2][1];

			getimage(img1, total_img1, (monster_img1 % 11) * 32, monster_img1 / 11 * 32, 32, 32);
			getimage(img2, total_img2, (monster_img2 % 11) * 32, monster_img2 / 11 * 32, 32, 32);

			putimage_transparent(img2, img1, 0, 0, 0x000000, 0, 0, 32, 32);//图像重合
			putimage_transparent(gameconfig.pgame_scene->area, img2, y * 32, x * 32, 0x80ffff);

		}
	}

	delimage(img1);
	delimage(total_img1);
	delimage(total_img2);
	delimage(img2);
	return true;
}

bool print_role(string control_command, game_config &gameconfig)
{

	PIMAGE img1, img2, total_img;
	total_img = newimage();
	img1 = newimage();
	img2 = newimage();

	getimage(total_img, "resource\\image\\total.bmp", 0, 0);


	if (control_command == "clear")
	{
		getimage(img2, total_img, 5 * 32, 0 * 32, 32, 32);
		putimage(gameconfig.pgame_scene->area, gameconfig.prole->coord[0] * 32, gameconfig.prole->coord[1] * 32, img2);
	}


	if (control_command == "stand")
	{
		int img_kind = gameconfig.prole->role_info["face_direction"];

		getimage(img1, total_img, (gameconfig.prole->role_img[img_kind][6] % 11) * 32, gameconfig.prole->role_img[img_kind][6] / 11 * 32, 32, 32);
		getimage(img2, total_img, (gameconfig.prole->role_img[img_kind][7] % 11) * 32, gameconfig.prole->role_img[img_kind][7] / 11 * 32, 32, 32);

		putimage_transparent(img2, img1, 0, 0, 0x000000, 0, 0, 32, 32);//图像重合
		putimage_transparent(gameconfig.pgame_scene->area, img2, gameconfig.prole->coord[0] * 32, gameconfig.prole->coord[1] * 32, 0x80ffff);
	}

	if (control_command == "run")
	{
		int img_kind = gameconfig.prole->role_info["face_direction"];
		getimage(img1, total_img, (gameconfig.prole->role_img[img_kind][2 * gameconfig.event_clock] % 11) * 32, gameconfig.prole->role_img[img_kind][2 * gameconfig.event_clock] / 11 * 32, 32, 32);
		getimage(img2, total_img, (gameconfig.prole->role_img[img_kind][2 * gameconfig.event_clock + 1] % 11) * 32, gameconfig.prole->role_img[img_kind][2 * gameconfig.event_clock + 1] / 11 * 32, 32, 32);

		putimage_transparent(img2, img1, 0, 0, 0x000000, 0, 0, 32, 32);//图像重合
		putimage_transparent(gameconfig.pgame_scene->area, img2, gameconfig.prole->coord[0] * 32, gameconfig.prole->coord[1] * 32, 0x80ffff);
	}

	if (control_command == "battle")
	{
		int img_kind = gameconfig.prole->role_info["face_direction"];
		getimage(img1, total_img, (gameconfig.prole->battle_img[img_kind][gameconfig.event_clock % 4 * 2] % 11) * 32, gameconfig.prole->battle_img[img_kind][gameconfig.event_clock % 4 * 2] / 11 * 32, 32, 32);
		getimage(img2, total_img, (gameconfig.prole->battle_img[img_kind][gameconfig.event_clock % 4 * 2 + 1] % 11) * 32, gameconfig.prole->battle_img[img_kind][gameconfig.event_clock % 4 * 2 + 1] / 11 * 32, 32, 32);

		putimage_transparent(img2, img1, 0, 0, 0x000000, 0, 0, 32, 32);//图像重合
		putimage_transparent(gameconfig.pgame_scene->area, img2, gameconfig.prole->coord[0] * 32, gameconfig.prole->coord[1] * 32, 0x80ffff);

	}

	delimage(img1);
	delimage(total_img);
	delimage(img2);
	return true;
}


bool init_allfloor(my_floor allfloor[])
{
	for (int i = 0;i != 23;++i)
	{
		allfloor[i].init_floor(i);
	}

	return true;
}

bool reset_allfloor(my_floor allfloor[])
{
	for (int i = 0;i != 23;++i)
	{
		allfloor[i].reset_floor(i);
	}

	return true;
}

bool print_bkgd(void)
{
	PIMAGE img, total_img;
	total_img = newimage();
	getimage(total_img, "resource\\image\\total.bmp", 0, 0);
	img = newimage();
	//int img_kind=gameconfig.prole->role_info["face_direction"];
	getimage(img, total_img, 9 * 32, 14 * 32, 32, 32);
	//getch();
	int x, y;
	for (y = 0; y < 12; ++y)
	{
		for (x = 0; x < 16; ++x)
		{
			putimage(x * 40, y * 40, 40, 40, img, 0, 0, 32, 32);//画背景
		}
	}
	delimage(img);
	delimage(total_img);
	return true;
}

bool print_scene(game_config &gameconfig, int control)
{
	window_area *pwinarea = 0;
	switch (control)
	{
	case 0:pwinarea = gameconfig.prole_property;break;
	case 1:pwinarea = gameconfig.pkey_detail;break;
	case 2:pwinarea = gameconfig.phelp_scene;break;
	case 3:pwinarea = gameconfig.pgame_scene;break;
	}
	if (!pwinarea)
	{
		return false;
	}
	char s[20] = " ";
	setcolor(EGERGB(0xff, 0xff, 0xff), pwinarea->area);
	setfont(20, 0, "宋体", pwinarea->area);
	setbkmode(TRANSPARENT, pwinarea->area);//字体底色透明
	//setviewport(winarea.position[0],winarea.position[1],winarea.position[0]+winarea.width_height[0],winarea.position[0]+winarea.width_height[1],1);
	PIMAGE img, total_img;
	switch (control)
	{
	case 0:
		print_frame(*pwinarea);
		img = newimage();
		total_img = newimage();
		getimage(total_img, "resource\\image\\total.bmp", 0, 0);
		getimage(img, total_img, 5 * 32, 0 * 32, 32, 32);

		//擦除原有数字
		putimage(pwinarea->area, 2 * 32, 16, img);//等级

		for (int i = 2;i < 7;++i)
		{
			putimage(pwinarea->area, 2 * 32, i * 32, img);//生命、攻击、防御、金币、经验
			putimage(pwinarea->area, 3 * 32, i * 32, img);//
		}

		//重新输出
		sprintf_s(s, "%d", gameconfig.prole->role_info["level"]);
		outtextxy(2.5 * 32 - (strlen(s) - 1) * 5, 32 - 10, s, pwinarea->area);//
		sprintf_s(s, "%d", gameconfig.prole->role_info["life"]);
		outtextxy(2.8 * 32 - (strlen(s) - 1) * 5, 32 * 2, s, pwinarea->area);//
		sprintf_s(s, "%d", gameconfig.prole->role_info["attack"]);
		outtextxy(2.8 * 32 - (strlen(s) - 1) * 5, 32 * 3, s, pwinarea->area);//
		sprintf_s(s, "%d", gameconfig.prole->role_info["defence"]);
		outtextxy(2.8 * 32 - (strlen(s) - 1) * 5, 32 * 4, s, pwinarea->area);//
		sprintf_s(s, "%d", gameconfig.prole->role_info["gold"]);
		outtextxy(2.8 * 32 - (strlen(s) - 1) * 5, 32 * 5, s, pwinarea->area);//
		sprintf_s(s, "%d", gameconfig.prole->role_info["exp"]);
		outtextxy(2.8 * 32 - (strlen(s) - 1) * 5, 32 * 6, s, pwinarea->area);//

		delimage(img);
		delimage(total_img);
		break;
	case 1:
		//PIMAGE img,total_img;
		print_frame(*pwinarea);
		img = newimage();
		total_img = newimage();
		getimage(total_img, "resource\\image\\total.bmp", 0, 0);
		getimage(img, total_img, 5 * 32, 0 * 32, 32, 32);

		//擦除原有数字
		putimage(pwinarea->area, 2 * 32, 0, img);
		putimage(pwinarea->area, 2 * 32, 32, img);
		putimage(pwinarea->area, 2 * 32, 2 * 32, img);

		sprintf_s(s, "%d", gameconfig.prole->role_info["yellow_key"]);
		outtextxy(2.3 * 32 - (strlen(s) - 1) * 5, 5, s, pwinarea->area);
		sprintf_s(s, "%d", gameconfig.prole->role_info["blue_key"]);
		outtextxy(2.3 * 32 - (strlen(s) - 1) * 5, 1 * 32 + 5, s, pwinarea->area);
		sprintf_s(s, "%d", gameconfig.prole->role_info["red_key"]);
		outtextxy(2.3 * 32 - (strlen(s) - 1) * 5, 2 * 32 + 5, s, pwinarea->area);

		delimage(img);
		delimage(total_img);
		break;
	case 2:
		print_frame(*pwinarea);
		img = newimage();
		total_img = newimage();
		getimage(total_img, "resource\\image\\total.bmp", 0, 0);
		getimage(img, total_img, 5 * 32, 0 * 32, 32, 32);

		//擦除原有数字
		for (int i = 0;i < 4;++i)
		{
			putimage(pwinarea->area, i * 32, 0, img);
		}

		outtextxy(2 * 32 - gameconfig.pall_floor[gameconfig.current_floor_number].floor_name.size() * 5, 5, gameconfig.pall_floor[gameconfig.current_floor_number].floor_name.c_str(), pwinarea->area);

		delimage(img);
		delimage(total_img);
		break;
	case 3:
		break;
	}
	putimage(pwinarea->position[0], pwinarea->position[1], pwinarea->area);

	return true;
}

int get_face_to_monster_number(game_config &gameconfig)
{
	//判断事件类型
	int monster_number, tempx, tempy;
	monster_number = tempx = tempy = 1;
	vector< int > role_property, monster_property;
	gameconfig.prole->role_property_output(role_property);
	switch (gameconfig.prole->role_info["face_direction"])
	{
	case 0:tempx = gameconfig.prole->coord[1] - 1;tempy = gameconfig.prole->coord[0];break;
	case 1:tempx = gameconfig.prole->coord[1];tempy = gameconfig.prole->coord[0] - 1;break;
	case 2:tempx = gameconfig.prole->coord[1] + 1;tempy = gameconfig.prole->coord[0];break;
	case 3:tempx = gameconfig.prole->coord[1];tempy = gameconfig.prole->coord[0] + 1;break;
	}
	if (tempx > 10 || tempy > 10 || tempx < 0 || tempy < 0)
	{
		return -2;//越界了
	}
	monster_number = gameconfig.pall_floor[gameconfig.current_floor_number].floor_info[tempx][tempy];
	return monster_number;
}

int event_sensor(game_config &gameconfig)
{
	int monster_number = get_face_to_monster_number(gameconfig);
	if (-2 == monster_number)
	{
		return -1;
	}
	monster current_monster;
	current_monster.init_monster(monster_number);
	return current_monster.monster_info["event"];

}

bool event_trigger(game_config &gameconfig)//事件触发
{
	//提取当前地图信息
	int monster_number, tempx, tempy, tempkey;
	monster_number = tempx = tempy = tempkey = 1;

	vector< int > role_property, monster_property;
	monster current_monster;

	if (gameconfig.game_control[1])
	{
		current_monster.init_monster(gameconfig.event_monster_number);
		gameconfig.event_number = current_monster.monster_info["event"];
	}
	else
	{
		switch (gameconfig.event_number)
		{
		case 7://查看怪物
			if (!gameconfig.prole->role_info["fruit"])
			{
				gameconfig.game_control[0] = 0;
				return false;
			}
			break;
		case 10://四灵归位
		case 11://四灵护体
		case 13://四灵封印
		case 14://能量聚集
		case 15://死神传送
		case 16://神圣冲击
		case 17://净化德古拉
		case 18://苏醒
		case 19://超级霸王电影弹
		case 20://传送出城
		case 21://黑幕
		case 22://保存游戏
		case 23://读取游戏
			break;
		default:
			gameconfig.prole->role_property_output(role_property);
			switch (gameconfig.prole->role_info["face_direction"])
			{
			case 0:tempx = gameconfig.prole->coord[1] - 1;tempy = gameconfig.prole->coord[0];break;
			case 1:tempx = gameconfig.prole->coord[1];tempy = gameconfig.prole->coord[0] - 1;break;
			case 2:tempx = gameconfig.prole->coord[1] + 1;tempy = gameconfig.prole->coord[0];break;
			case 3:tempx = gameconfig.prole->coord[1];tempy = gameconfig.prole->coord[0] + 1;break;
			}
			if (tempx > 10 || tempy > 10 || tempx < 0 || tempy < 0)
			{
				return false;
			}
			monster_number = gameconfig.pall_floor[gameconfig.current_floor_number].floor_info[tempx][tempy];

			if (monster_number < 0)
			{
				return false;
			}

			current_monster.init_monster(monster_number);
			gameconfig.event_number = current_monster.monster_info["event"];

			break;
		}
	}


	switch (gameconfig.event_number)
	{
	case 0:
		print_role("clear", gameconfig);
		if (gameconfig.event_clock == 2)
		{
			gameconfig.prole->role_position_change(gameconfig.prole->role_info["face_direction"]);

		}
		print_role("run", gameconfig);
		if (gameconfig.event_clock == 2)
		{
			gameconfig.game_control[0] = 0;
			break;
		}
		break;

	case 1://静默战斗
		print_role("clear", gameconfig);
		print_role("battle", gameconfig);

		if (gameconfig.event_clock == 3)
		{
			quick_battle(1, gameconfig, current_monster);
			gameconfig.game_control[0] = 0;
			if (!gameconfig.game_control[3])
			{
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				gameconfig.prole->role_info["gold"] += current_monster.monster_info["gold"];
				gameconfig.prole->role_info["exp"] += current_monster.monster_info["exp"];
			}
		}
		break;
	case 2://open door
		open_door_cartoon(gameconfig, current_monster, tempx, tempy);
		if (gameconfig.event_clock == 2)
		{
			gameconfig.game_control[0] = 0;
			gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);

			//副作用
			switch (current_monster.monster_number)
			{
			case 0:--gameconfig.prole->role_info["yellow_key"];break;
			case 1:--gameconfig.prole->role_info["blue_key"];break;
			case 2:--gameconfig.prole->role_info["red_key"];break;
			}

		}
		break;
	case 3://上下楼梯
		switch (current_monster.monster_number)
		{
		case 10:
			if (gameconfig.prole->role_info["floor"] == 21)
			{
				break;
			}
			++gameconfig.prole->role_info["floor"];
			gameconfig.prole->floor_reached[gameconfig.prole->role_info["floor"]] = 1;
			gameconfig.current_floor_number = gameconfig.prole->role_info["floor"];
			gameconfig.prole->set_role_position(gameconfig.pall_floor[gameconfig.current_floor_number].role_init_position[0]);
			break;
		case 11:
			if (!gameconfig.prole->role_info["floor"])
			{
				break;
			}
			--gameconfig.prole->role_info["floor"];
			gameconfig.current_floor_number = gameconfig.prole->role_info["floor"];
			gameconfig.prole->set_role_position(gameconfig.pall_floor[gameconfig.current_floor_number].role_init_position[1]);
			break;
		default:break;
		}
		update_BGM(gameconfig);
		gameconfig.game_control[0] = 0;
		break;
	case 4://吃到钥匙、宝石、药水
		gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
		switch (current_monster.monster_number)
		{
		case 28:++gameconfig.prole->role_info["yellow_key"];break;
		case 29:++gameconfig.prole->role_info["red_key"];break;
		case 30:++gameconfig.prole->role_info["blue_key"];break;
		case 31:gameconfig.prole->role_info["life"] += 200;break;
		case 32:gameconfig.prole->role_info["life"] += 500;break;
		case 33:gameconfig.prole->role_info["attack"] += 3;break;
		case 34:gameconfig.prole->role_info["defence"] += 3;break;
		}
		gameconfig.game_control[0] = 0;
		break;
	case 5://触发对话，及副作用
		print_dialog(gameconfig, current_monster.monster_info["dialog"], gameconfig.dialog_clock);//打印对话
		while (kbhit())
		{
			getch();
			++gameconfig.dialog_clock;
		}
		if (gameconfig.dialog_clock < 0)//副作用
		{
			gameconfig.game_control[0] = 0;
			gameconfig.dialog_clock = 0;
			switch (current_monster.monster_number)
			{
			case 20://林克1
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 21);
				gameconfig.pall_floor[2].set_floor_info(67, 5);
				break;
			case 21://林克2
				break;
			case 22://仙子1
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(93, 5);
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(92, 165);
				++gameconfig.prole->role_info["yellow_key"];
				++gameconfig.prole->role_info["blue_key"];
				++gameconfig.prole->role_info["red_key"];
				gameconfig.pall_floor[gameconfig.current_floor_number].music_number = 2;
				break;
			case 26://凯瑟琳
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 27);
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(120, 10);
				break;
			case 38://十字架
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				gameconfig.pall_floor[0].set_floor_info(92, 166);
				break;
			case 39://圣水
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				gameconfig.prole->role_info["life"] *= 2;
				break;
			case 41://仙果
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				gameconfig.prole->role_info["fruit"] = 1;
				break;
			case 42://鹰之翼
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				++gameconfig.prole->role_info["level"];
				gameconfig.prole->role_info["life"] += 1000;
				gameconfig.prole->role_info["attack"] += 5;
				gameconfig.prole->role_info["defence"] += 5;
				break;
			case 43://天使之翼
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				gameconfig.prole->role_info["level"] += 3;
				gameconfig.prole->role_info["life"] += 3600;
				gameconfig.prole->role_info["attack"] += 17;
				gameconfig.prole->role_info["defence"] += 17;
				break;
			case 45://阿鲁卡多之剑
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				gameconfig.prole->role_info["attack"] += 150;
				break;
			case 46://星光罗盘1
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				gameconfig.prole->role_info["compass"] = 1;
				break;
			case 47://钥匙盒
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				++gameconfig.prole->role_info["yellow_key"];
				++gameconfig.prole->role_info["blue_key"];
				++gameconfig.prole->role_info["red_key"];
				break;
			case 48://镐
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				gameconfig.pall_floor[4].set_floor_info(5, 71);
				break;
			case 49://幸运金币
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				gameconfig.prole->role_info["gold"] += 300;
				break;
			case 50://钢剑
				gameconfig.prole->role_info["attack"] += 10;
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				break;
			case 52://镶金宝剑
				gameconfig.prole->role_info["attack"] += 70;
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				break;
			case 55://铁盾
				gameconfig.prole->role_info["defence"] += 10;
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				break;
			case 57://黄金宝甲
				gameconfig.prole->role_info["defence"] += 85;
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				break;
			case 59://阿鲁卡多之盾
				gameconfig.prole->role_info["defence"] += 190;
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				break;
			case 63://隐形人
				++gameconfig.prole->role_info["gold"];
				++gameconfig.prole->role_info["exp"];
				break;
			case 65://星光法阵
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 10);
				gameconfig.prole->role_info["compass"] = 0;
				break;
			case 67://星光罗盘2
				gameconfig.pall_floor[0].set_floor_info(92, 171);
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				gameconfig.prole->role_info["compass"] = 1;
				break;
			case 71://林克3
				gameconfig.pall_floor[2].set_floor_info(67, 5);
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				gameconfig.pall_floor[18].set_floor_info(93, 5);
				gameconfig.pall_floor[18].set_floor_info(104, 5);
				break;
			case 97://德古拉无敌形态对话
				gameconfig.game_control[2] = 1;
				break;
			case 100://2层神秘老人
				gameconfig.prole->role_info["attack"] += 30;
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				break;
			case 101://2层奸商
				gameconfig.prole->role_info["defence"] += 30;
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				break;
			case 102://15层神秘老人
				if (gameconfig.prole->role_info["exp"] >= 500)
				{
					gameconfig.event_monster_number = 104;
					gameconfig.game_control[1] = 1;
					gameconfig.game_control[0] = 1;
				}
				break;
			case 103://15层奸商
				if (gameconfig.prole->role_info["gold"] >= 800)
				{
					gameconfig.event_monster_number = 105;
					gameconfig.game_control[1] = 1;
					gameconfig.game_control[0] = 1;
				}
				break;
			case 104://15层神秘老人
				gameconfig.prole->role_info["attack"] += 120;
				gameconfig.prole->role_info["exp"] -= 500;
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(37, 5);
				//gameconfig.game_control[0] = 0;
				break;
			case 105://15层奸商
				gameconfig.prole->role_info["defence"] += 120;
				gameconfig.prole->role_info["gold"] -= 800;
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(39, 5);
				break;
			case 165://仙子2对话
				break;
			case 166://仙子3对话
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 167);
				gameconfig.prole->role_info["life"] *= 1.3;
				gameconfig.prole->role_info["attack"] *= 1.3;
				gameconfig.prole->role_info["defence"] *= 1.3;
				break;
			case 167://仙子4对话
				break;
			case 168://仙子3对话
				gameconfig.pall_floor[20].set_floor_info(82, 65);
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 172);
				break;
			case 169://仙子3对话
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 170);
				break;
			case 170://仙子3对话
				break;
			case 171://仙子3对话
				gameconfig.pall_floor[20].set_floor_info(82, 65);
				gameconfig.pall_floor[7].set_floor_info(48, 4);
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 172);
				break;
			case 172://仙子3对话
				break;
			case 173://夜店1对话
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 15);
				break;
			case 174://夜店2对话
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 192);
				break;
			case 175://神秘老人1
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 24);
				break;
			case 176://神秘老人2
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 61);
				break;
			case 177://奸商1
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 18);
				break;
			case 178://奸商2
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 19);
				break;
			case 179://死神1对话
				gameconfig.prole->role_info["life"] = 860;
				gameconfig.prole->role_info["attack"] = 10;
				gameconfig.prole->role_info["defence"] = 10;
				gameconfig.event_clock = 0;
				gameconfig.event_number = 15;
				gameconfig.game_control[0] = 1;
				break;
			case 180://死神2对话
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 99);
				break;
			case 181://死神3对话
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(60, 5);
				break;
			case 182://德古拉1对话
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 94);
				break;
			case 183://德古拉2对话
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(49, 5);
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(97, 63);//释放隐形人
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(38, 10);
				if (gameconfig.prole->role_info["compass"])//分支剧情，根据是否得到罗盘
				{
					gameconfig.pall_floor[0].set_floor_info(92, 168);
				}
				else
				{
					gameconfig.pall_floor[9].set_floor_info(0, 67);
					gameconfig.pall_floor[7].set_floor_info(48, 6);
					gameconfig.pall_floor[0].set_floor_info(92, 169);
				}
				break;
			case 184://王座对话1
			case 194:
				gameconfig.prole->role_info["face_direction"] = 0;
				gameconfig.game_control[0] = 1;
				gameconfig.event_number = 14;
				break;
			case 185://王座对话2
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(59, 186);
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(69, 5);
				gameconfig.game_control[0] = 1;
				gameconfig.game_control[1] = 0;
				gameconfig.event_number = 19;
				gameconfig.event_clock = 0;
				break;
			case 186:
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 196);
				break;
			case 187:
				break;
			case 188:
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(61, 5);
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(60, 189);
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(49, 172);
				gameconfig.prole->set_role_position(6, 5);
				gameconfig.event_number = 10;
				gameconfig.game_control[0] = 1;
				gameconfig.game_control[1] = 0;
				gameconfig.event_clock = 0;
				//四灵护体动画
				break;
			case 189:
				//四芒星动画
				gameconfig.event_monster_number = 190;
				gameconfig.game_control[1] = 1;
				gameconfig.game_control[0] = 1;
				break;
			case 190:
				gameconfig.game_control[1] = 0;
				gameconfig.event_number = 20;
				gameconfig.game_control[0] = 1;
				gameconfig.event_clock = 0;
				//送出城外
				break;
			case 191://最终对话
				gameconfig.event_number = 21;
				gameconfig.game_control[1] = 0;
				gameconfig.game_control[0] = 1;
				gameconfig.event_clock = 0;
				break;
			case 193://隐形人
				++gameconfig.prole->role_info["gold"];
				++gameconfig.prole->role_info["exp"];
				break;
			}
		}
		break;
	case 6://商店
		//print_role("stand", gameconfig, winarea);
		print_dialog(gameconfig, current_monster.monster_info["dialog"], gameconfig.dialog_clock);

		while (kbhit())
		{
			tempkey = getch();
		}

		if (gameconfig.prole->role_info["gold"] < current_monster.monster_info["gold"])
		{
			gameconfig.game_control[4] = 1;
		}
		switch (tempkey)
		{
		case 49:
			if (!gameconfig.game_control[4])
			{
				gameconfig.prole->role_info["life"] += current_monster.monster_info["life"];
			}
			break;
		case 50:
			if (!gameconfig.game_control[4])
			{
				gameconfig.prole->role_info["attack"] += current_monster.monster_info["attack"];
			}
			break;
		case 51:
			if (!gameconfig.game_control[4])
			{
				gameconfig.prole->role_info["defence"] += current_monster.monster_info["defence"];
			}
			break;
		case 52:
			gameconfig.game_control[0] = 0;
			break;
		}
		switch (tempkey * !gameconfig.game_control[4])
		{
		case 49:
		case 50:
		case 51:
			gameconfig.prole->role_info["gold"] -= current_monster.monster_info["gold"];
			break;
		}
		tempkey = 0;
		break;
	case 7://怪物列表
		//gameconfig.game_control[6] = 0;
		monster_list(gameconfig);
		while (kbhit())
		{
			getch();
			gameconfig.game_control[0] = 0;
			//gameconfig.game_control[6] = 1;
		}

		break;
	case 8://神秘老人
		print_dialog(gameconfig, current_monster.monster_info["dialog"], gameconfig.dialog_clock);
		while (kbhit())
		{
			tempkey = getch();
		}

		switch (tempkey)
		{
		case 49:
			if (gameconfig.prole->role_info["exp"] < 2.9*current_monster.monster_info["exp"])
			{
				break;
			}
			gameconfig.prole->role_info["life"] += current_monster.monster_info["life"];
			gameconfig.prole->role_info["attack"] += current_monster.monster_info["attack"];
			gameconfig.prole->role_info["defence"] += current_monster.monster_info["defence"];
			gameconfig.prole->role_info["level"] += current_monster.monster_info["gold"];
			gameconfig.prole->role_info["exp"] -= 3 * current_monster.monster_info["exp"];
			break;
		case 50:
			if (gameconfig.prole->role_info["exp"] < current_monster.monster_info["exp"])
			{
				break;
			}
			gameconfig.prole->role_info["attack"] += current_monster.monster_info["attack"];
			gameconfig.prole->role_info["exp"] -= current_monster.monster_info["exp"];
			break;
		case 51:
			if (gameconfig.prole->role_info["exp"] < current_monster.monster_info["exp"])
			{
				break;
			}
			gameconfig.prole->role_info["defence"] += current_monster.monster_info["defence"];
			gameconfig.prole->role_info["exp"] -= current_monster.monster_info["exp"];
			break;
		case 52:
			gameconfig.game_control[0] = 0;
			break;
		}
		tempkey = 0;
		break;
	case 9://BOSS战
		update_BGM(gameconfig, current_monster.monster_info["music"]);
		if (gameconfig.event_clock / 2 * 2 == gameconfig.event_clock)
		{
			print_role("battle", gameconfig);
		}
		else
		{
			print_role("stand", gameconfig);
		}
		battle_process(gameconfig, current_monster);
		if (!gameconfig.game_control[0])
		{
			//quick_battle(1,gameconfig, current_monster);
			gameconfig.prole->role_info["gold"] += current_monster.monster_info["gold"];
			gameconfig.prole->role_info["exp"] += current_monster.monster_info["exp"];
			switch (current_monster.monster_number)
			{
			case 94://德古拉分身
				gameconfig.game_control[1] = 1;
				gameconfig.event_monster_number = 183;
				gameconfig.game_control[0] = 1;
				break;
			case 95://德古拉无敌形态
				gameconfig.game_control[0] = 1;
				gameconfig.game_control[1] = 1;
				gameconfig.event_monster_number = 97;
				break;
			case 96://德古拉真身
				gameconfig.game_control[1] = 1;
				gameconfig.event_monster_number = 188;
				gameconfig.game_control[0] = 1;
				break;
			case 99:
				gameconfig.game_control[1] = 1;
				gameconfig.event_monster_number = 181;
				gameconfig.game_control[0] = 1;
				update_BGM(gameconfig);
				break;
			case 143:
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(18, 145);
				break;
			case 145:
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(59, 187);
				gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(16, 96);
				//gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(27,94);
				break;
			default:gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(tempy + tempx * 11, 5);break;
			}
			update_BGM(gameconfig);
		}
		break;
	case 10://四灵归位
		if (200 - 2 * gameconfig.event_clock <= 32)
		{
			gameconfig.event_clock = 0;
			gameconfig.event_number = 11;
			break;
		}
		quadruple_summon_cartoon(gameconfig);
		break;
	case 11://四灵附体
		quadruple_guard_cartoon(gameconfig);
		if (kbhit())
		{
			getch();
			gameconfig.event_number = 13;
			//gameconfig.game_control[1]=1;
			gameconfig.event_clock = 0;
			gameconfig.game_control[0] = 1;
		}
		break;
	case 12://奸商
		print_dialog(gameconfig, current_monster.monster_info["dialog"], gameconfig.dialog_clock);
		while (kbhit())
		{
			tempkey = getch();
		}

		switch (tempkey)
		{
		case 49:
			if (current_monster.monster_info["gold"] > 0)
			{
				if (gameconfig.prole->role_info["gold"] < current_monster.monster_info["life"])
				{
					break;
				}
			}
			else
			{
				if (!gameconfig.prole->role_info["yellow_key"])
				{
					break;
				}
			}
			gameconfig.prole->role_info["yellow_key"] += current_monster.monster_info["gold"];
			gameconfig.prole->role_info["gold"] -= current_monster.monster_info["life"];
			break;
		case 50:
			if (current_monster.monster_info["gold"] > 0)
			{
				if (gameconfig.prole->role_info["gold"] < current_monster.monster_info["attack"])
				{
					break;
				}
			}
			else
			{
				if (!gameconfig.prole->role_info["blue_key"])
				{
					break;
				}
			}
			gameconfig.prole->role_info["blue_key"] += current_monster.monster_info["gold"];
			gameconfig.prole->role_info["gold"] -= current_monster.monster_info["attack"];
			break;
		case 51:
			if (current_monster.monster_info["gold"] > 0)
			{
				if (gameconfig.prole->role_info["gold"] < current_monster.monster_info["defence"])
				{
					break;
				}
			}
			else
			{
				if (!gameconfig.prole->role_info["red_key"])
				{
					break;
				}
			}
			gameconfig.prole->role_info["red_key"] += current_monster.monster_info["gold"];
			gameconfig.prole->role_info["gold"] -= current_monster.monster_info["defence"];
			break;
		case 52:
			gameconfig.game_control[0] = 0;
			break;
		}
		tempkey = 0;
		break;
	case 13://四灵封印
		if (gameconfig.event_clock > 4 * 32)
		{
			gameconfig.game_control[4] = 1;
			quadruple_seal_cartoon(5 * 32 + 16, 32 + 16, 60, 0.4*gameconfig.event_clock, *(gameconfig.pgame_scene));
		}
		else
		{
			quadruple_seal_cartoon(5 * 32 + 16, 5 * 32 + 16 - gameconfig.event_clock, 60, 0.4*gameconfig.event_clock, *(gameconfig.pgame_scene));

		}

		if (gameconfig.game_control[4] && kbhit())
		{
			getch();
			gameconfig.game_control[0] = 1;
			gameconfig.event_number = 17;
			gameconfig.event_clock = 0;
		}

		break;
	case 14://能量聚集
		power_gather_cartoon(gameconfig);
		if (gameconfig.event_clock > 250)
		{
			gameconfig.game_control[0] = 1;
			gameconfig.event_number = 16;
			gameconfig.event_clock = 0;
		}
		break;
	case 15://死神传送
		death_transport_cartoon(gameconfig);
		if (gameconfig.event_clock > 40)
		{
			//被死神带走了。。。
			gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(99 + 3, 5);
			gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(99 + 4, 5);
			gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(80, 5);
			gameconfig.pall_floor[16].set_floor_info(60, 180);
			gameconfig.pall_floor[18].set_floor_info(49, 26);
		}
		if (gameconfig.event_clock > 120)
		{
			gameconfig.game_control[0] = 0;
		}
		break;
	case 16://神圣冲击
		holy_blast_cartoon(gameconfig);
		if (gameconfig.event_clock > 72)
		{
			gameconfig.game_control[0] = 1;
			gameconfig.event_number = 5;
			gameconfig.event_monster_number = 185;
			gameconfig.game_control[1] = 1;
			gameconfig.event_clock = 0;
		}
		break;
	case 17://净化德古拉
		dracula_purification_cartoon(gameconfig);
		if (gameconfig.event_clock > 80)
		{
			gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(16, 5);
		}
		if (gameconfig.event_clock > 250)
		{
			gameconfig.game_control[0] = 1;
			gameconfig.game_control[1] = 1;
			gameconfig.event_monster_number = 189;
		}
		break;
	case 18://苏醒
		revive(0xffffff, 5, gameconfig);
		if (gameconfig.event_clock * 5 >= 255)
		{
			gameconfig.game_control[0] = 1;
			gameconfig.game_control[1] = 1;
			gameconfig.event_monster_number = 22;
		}
		break;
	case 19://超级霸王电影弹
		super_overlord_wave_cartoon(gameconfig);
		if (gameconfig.event_clock > 100)
		{
			gameconfig.game_control[0] = 0;
			gameconfig.prole->role_info["life"] *= 0.75;
		}
		break;
	case 20://传送出城
		holy_transport_cartoon(gameconfig);
		if (gameconfig.event_clock > 50)
		{
			gameconfig.pall_floor[gameconfig.current_floor_number].set_floor_info(59, 5);
			gameconfig.prole->set_role_position(13, 0);
		}
		if (gameconfig.event_clock > 120)
		{
			++gameconfig.prole->role_info["floor"];
			gameconfig.current_floor_number = gameconfig.prole->role_info["floor"];
			gameconfig.prole->set_role_position(gameconfig.pall_floor[gameconfig.current_floor_number].role_init_position[0]);
			gameconfig.game_control[1] = 1;
			gameconfig.event_monster_number = 191;
			gameconfig.game_control[0] = 1;
			update_BGM(gameconfig);
		}
		break;
	case 21://黑幕
		if (gameconfig.game_control[6])
		{
			print_scene(gameconfig, 3);//最后画一次
			gameconfig.game_control[6] = 0;
		}
		anti_revive(0x0, 0.5, gameconfig);
		if (gameconfig.event_clock * 0.5 >= 200)
		{
			gameconfig.game_control[0] = 0;
			gameconfig.game_control[2] = 1;
		}
		break;
	case 22://保存游戏
		if (save_data(gameconfig))
		{
			print_dialog(gameconfig, 199, gameconfig.dialog_clock);
			while (kbhit())
			{
				getch();
				gameconfig.game_control[0] = 0;
			}
		}
		break;
	case 23://读取游戏
		if (load_data(gameconfig))
		{
			update_BGM(gameconfig);
			print_dialog(gameconfig, 200, gameconfig.dialog_clock);//打印对话
			while (kbhit())
			{
				getch();
				gameconfig.game_control[0] = 0;
				update_floor_data(gameconfig);
			}
		}
		break;
	default:break;
	}
	return true;
}

int quick_battle(int control_int, game_config &gameconfig, monster &current_monster)
{
	int role_att, role_def, mon_att, mon_def, mon_lif, round;
	role_att = gameconfig.prole->role_info["attack"];
	role_def = gameconfig.prole->role_info["defence"];
	//role_lif=gameconfig.prole->role_info["life"];
	mon_att = current_monster.monster_info["attack"];
	mon_def = current_monster.monster_info["defence"];
	mon_lif = current_monster.monster_info["life"];

	if (role_att <= mon_def)
	{
		if (control_int)
		{
			gameconfig.prole->role_info["life"] = 0;
			gameconfig.game_control[3] = 1;
		}
		return -1;
	}

	if (mon_att <= role_def)
	{
		return 0;
	}

	round = round_count(mon_lif, role_att - mon_def);

	if (control_int)
	{
		gameconfig.prole->role_info["life"] -= (round - 1)*(mon_att - role_def);
		if (gameconfig.prole->role_info["life"] <= 0)
		{
			gameconfig.prole->role_info["life"] = 0;
			gameconfig.game_control[3] = 1;
		}
	}

	return (round - 1)*(mon_att - role_def);
}

int round_count(int a, int b)
{
	if (a / b * b == a)
	{
		return a / b;
	}
	else
	{
		return a / b + 1;
	}
}

bool my_flush(void)
{
	while (kbhit())getch();
	return true;
}

bool print_dialog(game_config &gameconfig, int dialog_number, int &dialog_clock)
{
	gameconfig.pdialog_scene->clear_area();
	my_dialog current_dialog;
	current_dialog.init_dlg(dialog_number);
	if (dialog_clock >= (int)current_dialog.dialog_words.size())
	{
		dialog_clock = -100;
		return false;
	}
	print_frame(*(gameconfig.pdialog_scene), *(gameconfig.pgame_scene));

	//const char *s=current_dialog.dialog_words[dialog_clock].c_str();
	PIMAGE img1, img2, total_img;
	total_img = newimage();
	img1 = newimage();
	img2 = newimage();

	setcolor(EGERGB(0xff, 0xff, 0xff), gameconfig.pdialog_scene->area);
	setfont(20, 0, "宋体", gameconfig.pdialog_scene->area);
	setbkmode(TRANSPARENT, gameconfig.pdialog_scene->area);//字体底色透明

	string tempstring(current_dialog.dialog_words[dialog_clock].begin() + 1, current_dialog.dialog_words[dialog_clock].end());//去掉string最前面的制表符
	tempstring = "   " + tempstring;

	outtextrect(0, 10, gameconfig.pdialog_scene->width_height[0], gameconfig.pdialog_scene->width_height[1], tempstring.c_str(), gameconfig.pdialog_scene->area);

	getimage(total_img, "resource\\image\\total.bmp", 0, 0);
	if (current_dialog.speaker_number[dialog_clock] == 188)
	{
		getimage(img2, total_img, current_dialog.speaker_number[dialog_clock] % 11 * 32, current_dialog.speaker_number[dialog_clock] / 11 * 32, 32, 32);
		getimage(img1, total_img, 5 * 32, 0 * 32, 32, 32);
		putimage_transparent(img1, img2, 0, 0, 0x80ffff);
	}
	else
	{
		getimage(img1, total_img, current_dialog.speaker_number[dialog_clock] % 11 * 32, current_dialog.speaker_number[dialog_clock] / 11 * 32, 32, 32);
	}

	putimage(gameconfig.pdialog_scene->area, 0, 0, img1);
	putimage(gameconfig.pgame_scene->area, gameconfig.pdialog_scene->position[0], gameconfig.pdialog_scene->position[1], gameconfig.pdialog_scene->area);

	delimage(img1);
	delimage(total_img);
	delimage(img2);
	return true;
}

bool print_frame(window_area &winarea)
{
	setfillcolor(0xB86A20);
	bar(winarea.position[0] - 3, winarea.position[1] - 3, winarea.position[0] + winarea.width_height[0], winarea.position[1]);
	bar(winarea.position[0] + winarea.width_height[0], winarea.position[1] - 3, winarea.position[0] + winarea.width_height[0] + 3, winarea.position[1] + winarea.width_height[1]);
	bar(winarea.position[0], winarea.position[1] + winarea.width_height[1], winarea.position[0] + winarea.width_height[0] + 3, winarea.position[1] + winarea.width_height[1] + 3);
	bar(winarea.position[0] - 3, winarea.position[1], winarea.position[0], winarea.position[1] + winarea.width_height[1] + 3);

	return true;
}

bool print_frame(window_area &winarea, window_area &gamescene)
{
	setfillcolor(0xB86A20, gamescene.area);
	bar(winarea.position[0] - 3, winarea.position[1] - 3, winarea.position[0] + winarea.width_height[0], winarea.position[1], gamescene.area);
	bar(winarea.position[0] + winarea.width_height[0], winarea.position[1] - 3, winarea.position[0] + winarea.width_height[0] + 3, winarea.position[1] + winarea.width_height[1], gamescene.area);
	bar(winarea.position[0], winarea.position[1] + winarea.width_height[1], winarea.position[0] + winarea.width_height[0] + 3, winarea.position[1] + winarea.width_height[1] + 3, gamescene.area);
	bar(winarea.position[0] - 3, winarea.position[1], winarea.position[0], winarea.position[1] + winarea.width_height[1] + 3, gamescene.area);
	return true;
}

bool monster_list(game_config &gameconfig)
{
	cleardevice(gameconfig.pgame_scene->area);
	map< int, int > monster_map;
	monster current_monster;
	PIMAGE img, total_img;
	int monster_number(0), role_damage(0);
	char temps[20] = " ";
	string tempstr;

	for (vector< vector< int > >::size_type i = 0;i < 11;++i)
	{
		for (vector< int >::size_type j = 0;j < 11;++j)
		{
			monster_number = gameconfig.pall_floor[gameconfig.current_floor_number].floor_info[i][j];
			current_monster.init_monster(monster_number);
			if (1 == current_monster.monster_info["event"] || 9 == current_monster.monster_info["event"])
			{
				monster_map[monster_number] = monster_number;
			}
		}
	}

	total_img = newimage();
	img = newimage();
	int i = 0;
	setcolor(EGERGB(0xff, 0xff, 0xff), gameconfig.pgame_scene->area);
	setfont(15, 0, "宋体", gameconfig.pgame_scene->area);
	setbkmode(TRANSPARENT, gameconfig.pgame_scene->area);//字体底色透明

	getimage(total_img, "resource\\image\\total.bmp", 0, 0);

	for (map< int, int >::iterator iimap_ite = monster_map.begin();iimap_ite != monster_map.end();++iimap_ite, ++i)
	{
		tempstr = "";//清空
		current_monster.init_monster(iimap_ite->second);
		getimage(img, total_img, current_monster.monster_img_number[gameconfig.event_clock / 5 % 2][1] % 11 * 32, current_monster.monster_img_number[gameconfig.event_clock / 5 % 2][1] / 11 * 32, 32, 32);
		putimage(gameconfig.pgame_scene->area, 5, i * 37 + 5, img);

		outtextxy(42, i * 37 + 10 - 3, "名称", gameconfig.pgame_scene->area);
		outtextxy(42, i * 37 + 25 - 3, "生命", gameconfig.pgame_scene->area);
		outtextxy(4 * 32 + 30, i * 37 + 10 - 3, "攻击", gameconfig.pgame_scene->area);
		outtextxy(4 * 32 + 30, i * 37 + 25 - 3, "防御", gameconfig.pgame_scene->area);
		outtextxy(7 * 32 + 10, i * 37 + 10 - 3, "金·经", gameconfig.pgame_scene->area);
		outtextxy(7 * 32 + 17, i * 37 + 25 - 3, "损失", gameconfig.pgame_scene->area);

		sprintf_s(temps, "%s", current_monster.monster_name.c_str());
		outtextxy(3 * 32 - strlen(temps) * 3 + 13, i * 37 + 10 - 3, temps, gameconfig.pgame_scene->area);
		sprintf_s(temps, "%d", current_monster.monster_info["life"]);
		outtextxy(3 * 32 - strlen(temps) * 3 + 13, i * 37 + 25 - 3, temps, gameconfig.pgame_scene->area);
		sprintf_s(temps, "%d", current_monster.monster_info["attack"]);
		outtextxy(6 * 32 - strlen(temps) * 3 + 13, i * 37 + 10 - 3, temps, gameconfig.pgame_scene->area);
		sprintf_s(temps, "%d", current_monster.monster_info["defence"]);
		outtextxy(6 * 32 - strlen(temps) * 3 + 13, i * 37 + 25 - 3, temps, gameconfig.pgame_scene->area);

		tempstr += int2str(current_monster.monster_info["gold"]) + "·" + int2str(current_monster.monster_info["exp"]);
		//sprintf(temps,"%s",current_monster.monster_name);
		outtextxy(9 * 32 - tempstr.size() * 3 + 17, i * 37 + 10 - 3, tempstr.c_str(), gameconfig.pgame_scene->area);

		role_damage = quick_battle(0, gameconfig, current_monster);
		if (-1 == role_damage)
		{
			sprintf_s(temps, "%s", "???");//攻击不够，显示？
		}
		else
		{
			sprintf_s(temps, "%d", role_damage);
		}
		outtextxy(9 * 32 - strlen(temps) * 3 + 17, i * 37 + 25 - 3, temps, gameconfig.pgame_scene->area);
	}


	putimage(gameconfig.pgame_scene->position[0], gameconfig.pgame_scene->position[1], gameconfig.pgame_scene->area);
	delimage(img);
	delimage(total_img);
	return true;
}

bool open_door_cartoon(game_config &gameconfig, monster &current_monster, int tempx, int tempy)
{
	print_role("stand", gameconfig);
	switch (current_monster.monster_number)//钥匙判断
	{
	case 0:
		if (!gameconfig.prole->role_info["yellow_key"])
		{
			gameconfig.game_control[0] = 0;
		}
		break;
	case 1:
		if (!gameconfig.prole->role_info["blue_key"])
		{
			gameconfig.game_control[0] = 0;
		}
		break;
	case 2:
		if (!gameconfig.prole->role_info["red_key"])
		{
			gameconfig.game_control[0] = 0;
		}
		break;
	case 4:break;
	default:gameconfig.game_control[0] = 0;break;
	}
	if (!gameconfig.game_control[0])
	{
		return false;
	}

	PIMAGE img, total_img, space;
	total_img = newimage();
	img = newimage();
	space = newimage();

	//提取空地
	getimage(total_img, "resource\\image\\total.bmp", 0, 0);
	getimage(space, total_img, 5 * 32, 0, 32, 32);
	delimage(total_img);

	//提取门
	total_img = newimage();
	getimage(total_img, "resource\\image\\doors.bmp", 0, 0);
	if (current_monster.monster_number != 4)
	{
		getimage(img, total_img, (current_monster.monster_number) * 32, (gameconfig.event_clock + 1) * 32, 32, 32);
	}
	else
	{
		getimage(img, total_img, 5 * 32, (gameconfig.event_clock + 5) * 32, 32, 32);
	}


	putimage(gameconfig.pgame_scene->area, tempy * 32, tempx * 32, space);//清除原有图像
	putimage_transparent(gameconfig.pgame_scene->area, img, tempy * 32, tempx * 32, 0x2f2f2f, 0, 0, 0, 0);//画上新图像

	delimage(img);
	delimage(total_img);
	delimage(space);
}

void print_power_circle(power_circle &powercirle, window_area &winarea)
{
	PIMAGE img;
	img = newimage(2 * powercirle.radius, 2 * powercirle.radius);
	setbkcolor(0x0, img);
	setfillcolor(powercirle.color1, img);
	fillellipse(powercirle.radius, powercirle.radius, powercirle.radius, powercirle.radius, img);
	setfillcolor(powercirle.color2, img);
	fillellipse(powercirle.radius, powercirle.radius, 0.7*powercirle.radius, 0.7*powercirle.radius, img);
	imagefilter_blurring(img, 0xfe, 0x100, 0, 0, 0, 0);
	putimage_alphatransparent(winarea.area, img, powercirle.positionx - powercirle.radius, powercirle.positiony - powercirle.radius, 0x000000, powercirle.blr_alpha, 0, 0, 0);
	delimage(img);
}

void quadruple_summon_cartoon(game_config &gameconfig)//小球轨迹为阿基米德螺线
{
	power_circle powercircle[4];
	for (int i = 0;i < 4;++i)
	{
		powercircle[i].radius = 10;
	}
	powercircle[0].positionx = (200 - 2 * gameconfig.event_clock)*cos(0.2*gameconfig.event_clock) + 176;
	powercircle[0].positiony = (200 - 2 * gameconfig.event_clock)*sin(0.2*gameconfig.event_clock) + 176;
	powercircle[1].positionx = (200 - 2 * gameconfig.event_clock)*cos(0.2*gameconfig.event_clock + PI / 2) + 176;
	powercircle[1].positiony = (200 - 2 * gameconfig.event_clock)*sin(0.2*gameconfig.event_clock + PI / 2) + 176;
	powercircle[2].positionx = (200 - 2 * gameconfig.event_clock)*cos(0.2*gameconfig.event_clock + PI) + 176;
	powercircle[2].positiony = (200 - 2 * gameconfig.event_clock)*sin(0.2*gameconfig.event_clock + PI) + 176;
	powercircle[3].positionx = (200 - 2 * gameconfig.event_clock)*cos(0.2*gameconfig.event_clock + PI / 2 * 3) + 176;
	powercircle[3].positiony = (200 - 2 * gameconfig.event_clock)*sin(0.2*gameconfig.event_clock + PI / 2 * 3) + 176;

	for (int i = 0;i < 4;++i)
	{
		print_power_circle(powercircle[i], *(gameconfig.pgame_scene));
	}

}

void quadruple_guard_cartoon(game_config &gameconfig)//小球的轨迹为笛卡尔心形线
{
	power_circle powercircle[4];
	for (int i = 0;i < 4;++i)
	{
		powercircle[i].radius = 10;
	}
	powercircle[0].positionx = 32 * (2 * cos(0.2*gameconfig.event_clock) - cos(2 * 0.2*gameconfig.event_clock)) + 176;
	powercircle[0].positiony = 32 * (2 * sin(0.2*gameconfig.event_clock) - sin(2 * 0.2*gameconfig.event_clock)) + 176;
	powercircle[1].positionx = 32 * (2 * sin(0.2*gameconfig.event_clock) - sin(2 * 0.2*gameconfig.event_clock)) + 176;
	powercircle[1].positiony = -32 * (2 * cos(0.2*gameconfig.event_clock) - cos(2 * 0.2*gameconfig.event_clock)) + 176;
	powercircle[2].positionx = 32 * (2 * sin(-0.2*gameconfig.event_clock) - sin(-2 * 0.2*gameconfig.event_clock)) + 176;
	powercircle[2].positiony = 32 * (2 * cos(-0.2*gameconfig.event_clock) - cos(-2 * 0.2*gameconfig.event_clock)) + 176;
	powercircle[3].positionx = -32 * (2 * cos(-0.2*gameconfig.event_clock) - cos(-2 * 0.2*gameconfig.event_clock)) + 176;
	powercircle[3].positiony = 32 * (2 * sin(-0.2*gameconfig.event_clock) - sin(-2 * 0.2*gameconfig.event_clock)) + 176;

	for (int i = 0;i < 4;++i)
	{
		print_power_circle(powercircle[i], *(gameconfig.pgame_scene));
	}
}


int is_game_over(game_config &gameconfig)
{
	if (gameconfig.game_control[3])
	{
		return -1;
	}
	if (gameconfig.game_control[2])
	{
		return 1;
	}
	return 0;
}

void quadruple_seal_cartoon(int positionx, int positiony, int randius, float angle, window_area &winarea)
{
	unsigned int fill_color = (unsigned int)(randomf() * 0xffffff);
	PIMAGE img;
	img = newimage(2 * randius, 2 * randius);
	int a = sin(PI / 8) / cos(PI / 8)*randius;
	//int b=sin(PI/4)*a;
	if (angle > 2 * PI)
	{
		angle -= 2 * PI;
	}
	int pt1[] = {
		randius*cos(angle) + randius, randius*sin(angle) + randius,
		a*cos(angle + PI / 2) + randius, a*sin(angle + PI / 2) + randius,
		randius*cos(angle + PI) + randius, randius*sin(angle + PI) + randius,
		a*cos(angle + PI / 2 * 3) + randius, a*sin(angle + PI / 2 * 3) + randius
	};
	int pt2[] = {
		a*cos(angle) + randius, a*sin(angle) + randius,
		randius*cos(angle + PI / 2) + randius, randius*sin(angle + PI / 2) + randius,
		a*cos(angle + PI) + randius, a*sin(angle + PI) + randius,
		randius*cos(angle + PI / 2 * 3) + randius, randius*sin(angle + PI / 2 * 3) + randius
	};
	int pt3[16] = {
		0
	};
	for (int i = 0;i < 8;++i)
	{
		pt3[2 * i] = 0.9*a*cos(angle + i * PI / 4) + randius;
		pt3[2 * i + 1] = 0.9*a*sin(angle + i * PI / 4) + randius;
	}
	setfillcolor(fill_color, img);
	fillpoly(4, pt1, img);
	fillpoly(4, pt2, img);
	setfillcolor(0x0, img);
	fillpoly(8, pt3, img);

	imagefilter_blurring(img, 0xfe, 0x100, 0, 0, 0, 0);
	putimage_transparent(winarea.area, img, positionx - randius, positiony - randius, 0x0, 0, 0, 0, 0);
	delimage(img);
}

void power_gather_cartoon(game_config &gameconfig)
{
	const int max_number = 16;
	int dif_x, dif_y, dif_r, t;
	const int origin_position[2 * max_number] = {
	13, 56, 193, 49, 20, 315, 281, 321,
	87, 24, 340, 35, 145, 278, 200, 190,
	49, 159, 286, 134, 130, 248, 320, 240,
	165, 80, 250, 120, 65, 218, 226, 291
	};//16个小能量球

	power_circle powercircle[max_number];//四周汇集的能量
	power_circle powercircle1;//中间的能量

	for (int i = 0; i < 16; ++i)
	{
		//getch();
		t = gameconfig.event_clock * 4;//4倍速
		powercircle[i].radius = 10;
		powercircle[i].positionx = origin_position[2 * i];
		powercircle[i].positiony = origin_position[2 * i + 1];
		dif_x = powercircle[i].positionx - 176;
		dif_y = powercircle[i].positiony - 176;
		dif_r = sqrt(dif_x*dif_x + dif_y * dif_y);
		if (t > dif_r)//dif_r是经过计算得出的小球到中间所需要的时间的“值”
		{
			t = t % dif_r;

		}
		if (!gameconfig.power_gather_control[i])//如果没有停止信号
		{
			/**小能量球朝中间汇聚，位置的改变是根据event_clock%dif_r和dir_r的时钟比
			因为比例是0~1，结合透明度，所以看起来像消失了，实际上是让小球往返
			i是为了每个小球速度不同按时间比例设置位置**/
			powercircle[i].positionx = -1.0*(t + i)*dif_x / dif_r + origin_position[2 * i];
			powercircle[i].positiony = -1.0*(t + i)*dif_y / dif_r + origin_position[2 * i + 1];
			if (gameconfig.game_control[4] && (fabs(powercircle[i].positionx - 176) < 5))//如果到达了中间且有停止信号
			{
				gameconfig.power_gather_control[i] = 1;
			}
		}
		else
		{
			powercircle[i].positionx = 176;
			powercircle[i].positiony = 176;
		}
		//透明度越靠近中间越高
		powercircle[i].blr_alpha = (1 - sqrt((powercircle[i].positionx - 176) * (powercircle[i].positionx - 176) + (powercircle[i].positiony - 176) * (powercircle[i].positiony - 176)) / dif_r) * 0xff;
	}

	for (int i = 0; i < 16; ++i)
	{
		print_power_circle(powercircle[i], *(gameconfig.pgame_scene));
	}

	powercircle1.radius += gameconfig.event_clock*1.0 / 10;//中间能量球放大

	if (powercircle1.radius > 20)//能量球聚集完成
	{
		powercircle1.radius = 20;
		gameconfig.game_control[4] = 1;//放出停止聚集信号
	}
	powercircle1.positionx = 176;
	powercircle1.positiony = 176;

	print_power_circle(powercircle1, *(gameconfig.pgame_scene));

}

int my_sgn(int number)
{
	if (!number)
	{
		return 0;
	}
	else if (number > 0)
	{
		return 1;
	}
	return -1;
}

void print_light_pillar(light_pillar &lightpillar, window_area &winarea)//光柱：一个长方形+一个椭圆
{
	PIMAGE img;
	img = newimage(lightpillar.width, lightpillar.height + lightpillar.width / 2 * lightpillar.circle_rate);
	setfillcolor(lightpillar.color1, img);
	fillellipse(lightpillar.width / 2, lightpillar.height, lightpillar.width / 2, lightpillar.width / 2 * lightpillar.circle_rate, img);
	bar(0, 0, lightpillar.width, lightpillar.height, img);

	setfillcolor(lightpillar.color2, img);
	fillellipse(lightpillar.width / 2, lightpillar.height, 0.7*lightpillar.width / 2, 0.7*lightpillar.width / 2 * lightpillar.circle_rate, img);
	bar(0.15*lightpillar.width, 0, 0.85*lightpillar.width, lightpillar.height, img);

	imagefilter_blurring(img, 0xfe, 0x100, 0, 0, 0, 0);
	putimage_alphatransparent(winarea.area, img, lightpillar.positionx - lightpillar.width / 2, lightpillar.positiony - lightpillar.height, 0x0, lightpillar.blr_alpha, 0, 0, 0);
	delimage(img);
}

void death_transport_cartoon(game_config &gameconfig)
{
	light_pillar lightpillar;
	lightpillar.positionx = 4 * 32;
	lightpillar.positiony = 10 * 32;
	if (gameconfig.event_clock > 30)
	{
		lightpillar.width = 2 * 32;
		lightpillar.height = 10 * 32;
		if (gameconfig.event_clock > 50)//灰走了。。。
		{
			lightpillar.positiony = 10 * 32 - (gameconfig.event_clock - 50) * 6;
			lightpillar.height = 10 * 32 - (gameconfig.event_clock - 50) * 6;
		}

	}
	else//变粗
	{
		lightpillar.width = gameconfig.event_clock * 2;
		lightpillar.height = 320;
	}
	print_light_pillar(lightpillar, *(gameconfig.pgame_scene));
}

void super_overlord_wave_cartoon(game_config &gameconfig)
{
	int img_number = gameconfig.event_clock % 4;
	int img_positionx, img_positiony;
	img_positionx = 4 * 32;
	img_positiony = 0;
	PIMAGE img = newimage(3 * 32, 110);
	power_circle powercircle;
	powercircle.color1 = 0x111111;
	powercircle.color2 = (unsigned int)(randomf() * 0xffffff);
	powercircle.positionx = 5 * 32 + 16;
	powercircle.positiony = 2 * 32 + 16;
	powercircle.radius += gameconfig.event_clock*1.0;

	string file_name = "resource\\image\\" + int2str(img_number) + ".jpg";
	getimage(img, file_name.c_str(), 0, 0);
	if (gameconfig.event_clock < 80)//能量聚集
	{
		print_power_circle(powercircle, *(gameconfig.pgame_scene));
	}
	else if (gameconfig.event_clock >= 80 && gameconfig.event_clock < 93)//往前推进
	{
		img_positiony = (gameconfig.event_clock - 80) * 25 + 1 * 32;
		putimage_transparent(gameconfig.pgame_scene->area, img, 5 * 32 + 16 - 0.5*getwidth(img), img_positiony, 0x0, 0, 0, 0, 0);
	}
	else//越过画面后固定，防止又回来了
	{
		img_positiony = 18 * 32;
		putimage_transparent(gameconfig.pgame_scene->area, img, 5 * 32 + 16 - 0.5*getwidth(img), img_positiony, 0x0, 0, 0, 0, 0);
	}

	delimage(img);
}

void holy_blast_cartoon(game_config &gameconfig)
{
	light_pillar lightpillar;
	lightpillar.positionx = 5 * 32 + 16;
	lightpillar.positiony = 5 * 32;
	if (gameconfig.event_clock > 16)
	{
		lightpillar.width = 32;

		if (gameconfig.event_clock / 2 * 2 == gameconfig.event_clock&&gameconfig.event_clock < 50)
		{
			lightpillar.positionx = 5 * 32 + 16 - 3;//冲击波晃动
			lightpillar.positiony = 5 * 32 + 16 - 3;
		}
		if (gameconfig.event_clock > 50)//收缩
		{
			lightpillar.width = 32 - (gameconfig.event_clock - 50)*1.2;
		}

	}
	else//变粗
	{
		lightpillar.width = gameconfig.event_clock * 2;
	}
	lightpillar.height = 3 * 32 + 10;
	lightpillar.circle_rate = 1.5;
	lightpillar.color1 = 0x7777ff;
	lightpillar.color2 = 0xffffff;
	print_light_pillar(lightpillar, *(gameconfig.pgame_scene));
}

void dracula_purification_cartoon(game_config &gameconfig)
{
	int r = 60 - gameconfig.event_clock;
	PIMAGE img = newimage(2 * r, 2 * r);//等于四芒星直径
	light_pillar lightpillar;
	lightpillar.color1 = 0xffffff;
	lightpillar.color2 = (unsigned int)(randomf() * 0xffffff);
	lightpillar.positionx = 5 * 32 + 16;
	lightpillar.positiony = 2 * 32;

	setfillcolor(lightpillar.color2, img);
	fillellipse(r, r, r, r, img);

	if (gameconfig.event_clock < 60)
	{
		putimage_transparent(gameconfig.pgame_scene->area, img, 5 * 32 + 16 - r, 1 * 32 + 16 - r, 0x0, 0, 0, 0, 0);
	}
	else if (gameconfig.event_clock >= 60 && gameconfig.event_clock < 108)
	{
		lightpillar.width = (gameconfig.event_clock - 60) * 2;
		lightpillar.height = 2 * 32;
		print_light_pillar(lightpillar, *(gameconfig.pgame_scene));
	}
	else
	{
		lightpillar.width = 3 * 32;
		lightpillar.height = 2 * 32;
		if (gameconfig.event_clock > 167)//灰走了。。。
		{
			lightpillar.positiony = 2 * 32 - (gameconfig.event_clock - 167);
			lightpillar.height = 2 * 32 - (gameconfig.event_clock - 167);
		}
		print_light_pillar(lightpillar, *(gameconfig.pgame_scene));
	}
	delimage(img);
}

void holy_transport_cartoon(game_config &gameconfig)
{
	light_pillar lightpillar;
	lightpillar.color1 = 0x7777ff;
	lightpillar.color2 = 0xffffff;
	lightpillar.positionx = 5 * 32 + 16;
	lightpillar.positiony = 6 * 32;
	if (gameconfig.event_clock > 46)
	{
		lightpillar.width = 3 * 32;
		lightpillar.height = 6 * 32;
		if (gameconfig.event_clock > 70)//灰走了。。。
		{
			lightpillar.positiony = 6 * 32 - (gameconfig.event_clock - 70) * 6;
			lightpillar.height = 6 * 32 - (gameconfig.event_clock - 70) * 6;
		}

	}
	else//变粗
	{
		lightpillar.width = gameconfig.event_clock * 2;
		lightpillar.height = 6 * 32;
	}
	print_light_pillar(lightpillar, *(gameconfig.pgame_scene));
}

bool update_BGM(game_config &gameconfig)
{

	if (gameconfig.bgm.music_number == gameconfig.pall_floor[gameconfig.current_floor_number].music_number)
	{
		return false;
	}
	else
	{
		if (gameconfig.pall_floor[gameconfig.current_floor_number].music_number)
		{
			gameconfig.bgm.msc.Close();
			gameconfig.bgm.cycle_flag = 0;
			gameconfig.bgm.music_number = gameconfig.pall_floor[gameconfig.current_floor_number].music_number;
			string music_file = "resource\\music\\" + int2str(gameconfig.bgm.music_number) + ".mp3";
			string music_position = "resource\\music\\" + int2str(gameconfig.bgm.music_number) + ".mpt";
			fstream read_music_position(music_position.c_str(), fstream::in);
			for (int i = 0; i < 4; ++i)
			{
				read_music_position >> gameconfig.bgm.play_position[i];
			}
			read_music_position >> gameconfig.bgm.music_volume;
			gameconfig.bgm.msc.OpenFile(music_file.c_str()); // 打开文件
			gameconfig.bgm.msc.SetVolume(gameconfig.bgm.music_volume);
		}
	}
	return true;
}

bool update_BGM(game_config &gameconfig, int music_number)
{

	if (gameconfig.bgm.music_number == music_number)
	{
		return false;
	}
	else
	{
		if (music_number)
		{
			gameconfig.bgm.msc.Close();
			gameconfig.bgm.cycle_flag = 0;
			gameconfig.bgm.music_number = music_number;
			string music_file = "resource\\music\\" + int2str(gameconfig.bgm.music_number) + ".mp3";
			string music_position = "resource\\music\\" + int2str(gameconfig.bgm.music_number) + ".mpt";
			fstream read_music_position(music_position.c_str(), fstream::in);
			for (int i = 0; i < 4; ++i)
			{
				read_music_position >> gameconfig.bgm.play_position[i];
			}
			read_music_position >> gameconfig.bgm.music_volume;
			gameconfig.bgm.msc.OpenFile(music_file.c_str()); // 打开文件
			gameconfig.bgm.msc.SetVolume(gameconfig.bgm.music_volume);
		}
	}
	return true;
}

int play_BGM(game_config &gameconfig, int control)
{
	if (!control)
	{
		gameconfig.bgm.msc.Close();
		return 0;
	}

	if (!gameconfig.bgm.cycle_flag)
	{
		++gameconfig.bgm.cycle_flag;

		gameconfig.bgm.msc.Play(gameconfig.bgm.play_position[0], gameconfig.bgm.play_position[1]);
	}


	if ((gameconfig.bgm.msc.GetPlayStatus() == MUSIC_MODE_STOP) && control == 2)
	{
		gameconfig.bgm.msc.Play(gameconfig.bgm.play_position[2], gameconfig.bgm.play_position[3]);
	}
}

void revive(unsigned int col, int speed, game_config &gameconfig)
{
	PIMAGE img = newimage(640, 480);
	setbkcolor(col, img);
	if (0xff - gameconfig.event_clock*speed >= 0)
	{
		putimage_alphablend(NULL, img, 0, 0, 0xff - gameconfig.event_clock*speed, 0, 0, 0, 0);
		putimage_alphablend(gameconfig.pgame_scene->area, img, 0, 0, 0xff - gameconfig.event_clock*speed, 0, 0, 11 * 32, 11 * 32);
	}
	delimage(img);
}

void anti_revive(unsigned int col, int speed, game_config &gameconfig)
{
	PIMAGE img = newimage(640, 480);
	setbkcolor(col, img);
	if (gameconfig.event_clock * speed <= 0xff)
	{
		putimage_alphablend(NULL, img, 0, 0, gameconfig.event_clock * speed, 0, 0, 0, 0);
	}
	delimage(img);
}

void anti_revive(unsigned int col, int speed, game_config &gameconfig, window_area &winarea)
{
	PIMAGE img = newimage(640, 480);
	setbkcolor(col, img);
	if (gameconfig.event_clock * speed <= 0xff)
	{
		putimage_alphablend(NULL, img, 0, 0, gameconfig.event_clock * speed, 0, 0, 0, 0);
		putimage_alphablend(winarea.area, img, 0, 0, gameconfig.event_clock * speed, 0, 0, 11 * 32, 11 * 32);
	}
	delimage(img);
}

void play_prelude(game_config &gameconfig)
{

	my_dialog prelude;
	prelude.init_dlg(0);
	setfont(prelude.font_size, 0, "宋体");
	setbkmode(TRANSPARENT);//字体底色透明
	int max_size = prelude.start_time.size();
	update_BGM(gameconfig, 18);
	play_BGM(gameconfig, 1);

	double start_clock, current_clock;
	start_clock = fclock();

	for (int skipflag = 0; is_run(); delay_fps(60))
	{
		cleardevice();
		current_clock = fclock() - start_clock;
		for (int i = 0; !skipflag && i < max_size; ++i)
		{
			//xyprintf(100, 100, "%f", current_clock);
			if (current_clock >= prelude.start_time[i] && current_clock < prelude.end_time[i])
			{
				if (prelude.fontcol < 253)
				{
					prelude.fontcol += 2;
				}
			}
			if (current_clock >= prelude.end_time[i] && current_clock < prelude.end_time[i] + 2)
			{
				if (prelude.fontcol > 2)
				{
					prelude.fontcol -= 2;
				}
			}
			if (current_clock >= prelude.start_time[i] && current_clock < prelude.end_time[i] + 2)
			{
				setcolor(EGERGB(prelude.fontcol, prelude.fontcol, prelude.fontcol));
				//xyprintf(getwidth()/2-prelude.dialog_words[i].size()/2, getheight()/2,"%d", prelude.fontcol);
				//居中打印，算出总字符数/2*字体大小/2，因为是中文所以字体大小/2
				outtextxy(getwidth() / 2 - (prelude.dialog_words[i].size())*prelude.font_size / 4, getheight() / 2 - prelude.font_size, prelude.dialog_words[i].c_str());
			}
			while (kbhit())
			{
				getch();
				skipflag = 1;
			}

		}

		if (current_clock > 85 || skipflag)
		{
			//白幕
			play_BGM(gameconfig, 0);
			anti_revive(0xffffff, 1, gameconfig);
			++gameconfig.event_clock;
			if (gameconfig.event_clock >= 255)
			{
				break;
			}
		}
	}

	gameconfig.event_clock = 0;
}

void play_finale(game_config &gameconfig)
{
	const int LOGO_MAX_NUMBER = 2;
	PIMAGE scene = newimage(320, 240);
	PIMAGE logo[LOGO_MAX_NUMBER];
	PIMAGE last_logo = newimage();
	double logo_start_time[LOGO_MAX_NUMBER];
	for (int i = 0; i < LOGO_MAX_NUMBER; ++i)
	{
		logo[i] = newimage();
	}
	logo_start_time[0] = 1.0;
	getimage(logo[0], "resource\\image\\game_logo.jpg", 0, 0);
	logo_start_time[1] = 31.0;
	getimage(logo[1], "resource\\image\\EGE.jpg", 0, 0);

	double last_logo_time = 234.0;
	int last_logo_positiony = 260;
	getimage(last_logo, "resource\\image\\last.jpg", 0, 0);

	int logo_positiony[LOGO_MAX_NUMBER];
	for (int i = 0; i < LOGO_MAX_NUMBER; ++i)
	{
		logo_positiony[i] = 260;
	}

	my_dialog finale, music_lrc;
	finale.init_dlg(197);
	music_lrc.init_dlg(198);
	music_lrc.fontcol = 0xff;
	finale.fontcol = 0xff;
	setfont(finale.font_size, 0, "宋体", scene);
	setcolor(EGERGB(finale.fontcol, finale.fontcol, finale.fontcol), scene);
	setfont(music_lrc.font_size, 0, "宋体");
	setcolor(EGERGB(music_lrc.fontcol, music_lrc.fontcol, music_lrc.fontcol));
	setbkmode(TRANSPARENT, scene);//字体底色透明
	int max_size = finale.start_time.size();
	update_BGM(gameconfig, 19);
	play_BGM(gameconfig, 1);

	for (int i = 0; i < max_size; ++i)
	{
		finale.dialog_positiony[i] = 260;
	}

	double start_clock, current_clock;
	start_clock = fclock();

	for (; is_run(); delay_fps(60))
	{
		cleardevice();
		cleardevice(scene);
		current_clock = fclock() - start_clock;
		for (int i = 0; i < max_size; ++i)
		{
			if (current_clock >= finale.start_time[i] && (finale.dialog_positiony[i] > -20))
			{
				if (gameconfig.event_clock / 3 * 3 == gameconfig.event_clock)
				{
					--finale.dialog_positiony[i];
				}
				//居中打印，算出总字符数/2*字体大小/2，因为是中文所以字体大小/2
				outtextxy(getwidth(scene) / 2 - (finale.dialog_words[i].size())*finale.font_size / 4, finale.dialog_positiony[i], finale.dialog_words[i].c_str(), scene);
			}
		}

		//普通logo
		for (int i = 0; i < LOGO_MAX_NUMBER; ++i)
		{
			if (current_clock >= logo_start_time[i] && (logo_positiony[i] + getwidth(logo[i]) > 0))
			{
				if (gameconfig.event_clock / 3 * 3 == gameconfig.event_clock)
				{
					--logo_positiony[i];
				}
				putimage(scene, getwidth(scene) / 2 - getwidth(logo[i]) / 2, logo_positiony[i], logo[i]);
			}
		}

		//最终logo
		if (current_clock >= last_logo_time && (last_logo_positiony > (getheight(scene) - getheight(last_logo)) / 2))
		{
			if (gameconfig.event_clock / 3 * 3 == gameconfig.event_clock)
			{
				--last_logo_positiony;
			}
		}
		putimage(scene, (getwidth(scene) - getwidth(last_logo)) / 2, last_logo_positiony, last_logo);

		putimage(160, 120, scene);

		//歌词
		for (int i = 0; i < music_lrc.start_time.size(); ++i)
		{
			if (current_clock >= music_lrc.start_time[i] && current_clock < music_lrc.end_time[i])
			{
				outtextxy(getwidth() / 2 - (music_lrc.dialog_words[i].size())*music_lrc.font_size / 4, getheight() - 20, music_lrc.dialog_words[i].c_str());
			}

		}

		if (current_clock > 265)
		{
			break;
		}
		++gameconfig.event_clock;
	}

	delimage(scene);
	delimage(last_logo);
	for (int i = 0; i < LOGO_MAX_NUMBER; ++i)
	{
		delimage(logo[i]);
	}
	gameconfig.event_clock = 0;
	play_BGM(gameconfig, 0);
	getch();
	for (int i = 0; i < 300; delay_fps(60))
	{
		anti_revive(0x0, 1, gameconfig);
		++i;
	}
}

void update_gameconfig(game_config &gameconfig)
{
	gameconfig.current_floor_number = gameconfig.prole->role_info["floor"];
}

bool is_os_XP(void)
{
	//fstream write_data_file("C:\\Users\\ostest.dat",fstream::out);
	if (-1 == GetFileAttributes(L"C:\\Users"))//不存在users文件夹代表是XP
	{
		return true;
	}
	return false;
}

string get_save_path(void)
{
	string filepath;
	char filename[80];
	DWORD filename_number = 80;
	if (GetUserName((LPWSTR)filename, &filename_number))
	{
		if (is_os_XP())
		{
			filepath += "C:\\Documents and Settings\\";
			filepath += filename;
			filepath += "\\My Documents\\Castlevania";
		}
		else
		{
			filepath += "C:\\Users\\";
			filepath += filename;
			filepath += "\\Documents\\Castlevania";
		}
		return filepath;
	}
	else
	{
		return filepath = "resource\\role";
	}
}

bool save_data(game_config &gameconfig)
{
	string file_path = get_save_path();
	//string file_path = "C:\\Documents and Settings\\123\\My Documents\\Castlevania";
	string data_file = file_path + "\\Dawn_of_the_Circle.sav";
	fstream write_data_file(data_file.c_str(), fstream::out);
	if (!write_data_file)
	{
		write_data_file.close();
		CreateDirectory((LPWSTR)(file_path.c_str()), NULL);
		write_data_file.open(data_file.c_str(), fstream::out);
		if (!write_data_file)
		{
			return false;
		}
	}

	//保存角色信息
	write_data_file << gameconfig.prole->role_info["level"] << '\t';
	write_data_file << gameconfig.prole->role_info["life"] << '\t';
	write_data_file << gameconfig.prole->role_info["attack"] << '\t';
	write_data_file << gameconfig.prole->role_info["defence"] << '\t';
	write_data_file << gameconfig.prole->role_info["gold"] << '\t';
	write_data_file << gameconfig.prole->role_info["exp"] << '\t';
	write_data_file << gameconfig.prole->role_info["yellow_key"] << '\t';
	write_data_file << gameconfig.prole->role_info["blue_key"] << '\t';
	write_data_file << gameconfig.prole->role_info["red_key"] << '\t';
	write_data_file << gameconfig.prole->role_info["floor"] << '\t';
	write_data_file << gameconfig.prole->role_info["face_direction"] << '\t';
	write_data_file << gameconfig.prole->role_info["compass"] << '\t';
	write_data_file << gameconfig.prole->role_info["fruit"] << endl;
	write_data_file << gameconfig.prole->coord[0] << '\t';
	write_data_file << gameconfig.prole->coord[1] << endl << endl;

	for (int i = 0; i < 24; ++i)
	{
		write_data_file << gameconfig.prole->floor_reached[i] << '\t';
	}
	write_data_file << endl;

	//保存地图信息
	for (int i = 0; i < 22; ++i)
	{
		for (vector< vector< int > >::iterator ivecvec = gameconfig.pall_floor[i].floor_info.begin(); ivecvec != gameconfig.pall_floor[i].floor_info.end(); ++ivecvec)
		{
			for (vector< int >::iterator ivec = (*ivecvec).begin(); ivec != (*ivecvec).end(); ++ivec)
			{
				write_data_file << *ivec << '\t';
			}
			write_data_file << endl;
		}
		write_data_file << endl;
	}

	write_data_file.close();
	write_data_file.clear();
	return true;
}

bool load_data(game_config &gameconfig)
{
	unsigned int tempint(0);
	//string file_path = "C:\\Documents and Settings\\123\\My Documents\\Castlevania";
	//string data_file = file_path + "\\Dawn_of_the_Circle.sav";
	//string data_file = "resource\\role\\Dawn_of_the_Circle.sav";
	string data_file = get_save_path() + "\\Dawn_of_the_Circle.sav";
	fstream read_data_file(data_file.c_str(), fstream::in);
	if (!read_data_file)
	{
		return false;
	}

	//保存角色信息
	read_data_file >> gameconfig.prole->role_info["level"];
	read_data_file >> gameconfig.prole->role_info["life"];
	read_data_file >> gameconfig.prole->role_info["attack"];
	read_data_file >> gameconfig.prole->role_info["defence"];
	read_data_file >> gameconfig.prole->role_info["gold"];
	read_data_file >> gameconfig.prole->role_info["exp"];
	read_data_file >> gameconfig.prole->role_info["yellow_key"];
	read_data_file >> gameconfig.prole->role_info["blue_key"];
	read_data_file >> gameconfig.prole->role_info["red_key"];
	read_data_file >> gameconfig.prole->role_info["floor"];
	read_data_file >> gameconfig.prole->role_info["face_direction"];
	read_data_file >> gameconfig.prole->role_info["compass"];
	read_data_file >> gameconfig.prole->role_info["fruit"];
	read_data_file >> gameconfig.prole->coord[0];
	read_data_file >> gameconfig.prole->coord[1];

	for (int i = 0; i < 24; ++i)
	{
		read_data_file >> tempint;
		if (tempint)
		{
			gameconfig.prole->floor_reached.set(i);
		}
		else
		{
			gameconfig.prole->floor_reached.reset(i);
		}
	}

	//读取地图信息
	for (int i = 0; i < 22; ++i)
	{
		for (vector< vector< int > >::iterator ivecvec = gameconfig.pall_floor[i].floor_info.begin(); ivecvec != gameconfig.pall_floor[i].floor_info.end(); ++ivecvec)
		{
			for (vector< int >::iterator ivec = (*ivecvec).begin(); ivec != (*ivecvec).end(); ++ivec)
			{
				read_data_file >> *ivec;
			}
		}
	}

	read_data_file.close();
	read_data_file.clear();
	gameconfig.game_control.reset(2);
	gameconfig.game_control.reset(3);
	update_gameconfig(gameconfig);
	return true;
}

void main_menu(game_config &gameconfig, vector< int > &key)
{
	int is_save_exsit = 1;
	string savefilename = get_save_path() + "\\Dawn_of_the_Circle.sav";
	fstream file_save(savefilename.c_str(), fstream::in);
	if (!file_save)
	{
		is_save_exsit = 0;
	}
	file_save.close();
	file_save.clear();
	const char *s[] = { "开始游戏",  "读取游戏", "游戏说明", "退出游戏" };

	PIMAGE img = newimage(getwidth(), getheight() / 2);
	PIMAGE des_img = newimage(getwidth(), getheight());
	PIMAGE logo_temp1 = newimage();
	PIMAGE logo_img = newimage(getwidth(), getheight() / 2);

	getimage(logo_temp1, "resource\\image\\game_logo.jpg", 0, 0);
	PIMAGE logo_temp2 = newimage(getwidth(logo_temp1)*1.5, 1.5*getheight(logo_temp1));
	putimage(logo_temp2, 0, 0, getwidth(logo_temp2), getheight(logo_temp2), logo_temp1, 0, 0, getwidth(logo_temp1), getheight(logo_temp1));
	putimage_transparent(logo_img, logo_temp2, getwidth(logo_img) / 2 - getwidth(logo_temp2) / 2, getheight(logo_img) / 2 - getheight(logo_temp2) / 2, 0x80ffff, 0, 0, 0, 0);

	getimage(des_img, "resource\\image\\description.jpg", 0, 0);
	setcolor(0xffffff, img);
	setfontbkcolor(0x000000, img);
	int font_size = 25;
	int line_gap = 15;
	int origin_height = 30;
	setfont(font_size, 0, "宋体", img);
	int selection_img_positiony = getheight();
	int logo_img_positiony = 0 - getheight() / 2;
	int user_select = -1;
	update_BGM(gameconfig, 20);
	mouse_msg msg, msg1;
	do
	{
		for (int i = 0; i < 4; ++i)
		{
			outtextxy(getwidth(img) / 2 - 2 * font_size, origin_height + (font_size + line_gap)*i, s[i], img);
		}

		//logo和选项往中间移动
		for (; is_run(); delay_fps(60))
		{
			cleardevice();
			if (user_select == 2)
			{
				putimage(0, 0, des_img);
			}
			putimage(0, logo_img_positiony, logo_img);
			putimage(0, selection_img_positiony, img);
			if (selection_img_positiony > getheight() / 2)
			{
				selection_img_positiony -= 5;
				logo_img_positiony += 5;
			}
			else
			{
				break;
			}
		}
		user_select = -1;

		while (mousemsg())//清空多于鼠标消息缓存
		{
			msg = getmouse();
		}
		msg = { 0 };//清空msg

		for (; is_run(); delay_fps(60))
		{
			play_BGM(gameconfig, 2);
			cleardevice(img);
			//获取鼠标消息，这个函数会等待，等待到有消息为止
			while (mousemsg())
			{
				msg = getmouse();
			}
			//如果鼠标移到字上就重定义字体背景
			for (int i = 0; i < 4; ++i)
			{
				if (msg.x >= getwidth(img) / 2 - 2 * font_size && msg.x < getwidth(img) / 2 + 2 * font_size && msg.y >= origin_height + (font_size + line_gap)*i + selection_img_positiony && msg.y < origin_height + (font_size + line_gap)*i + font_size + selection_img_positiony)
				{
					if (is_save_exsit || i != 1)//当没有存档就不能被选中
					{
						setfontbkcolor(0xe60017, img);
						while (mousemsg())
						{
							msg = getmouse();
						}
						if ((int)msg.is_up() && (int)msg.is_left())
						{
							user_select = i;
							break;
						}
					}
				}
				else
				{
					setfontbkcolor(0x000000, img);
				}

				outtextxy(getwidth(img) / 2 - 2 * font_size, origin_height + (font_size + line_gap)*i, s[i], img);
			}

			putimage(0, selection_img_positiony, img);
			if (user_select >= 0)
			{
				break;
			}
		}


		setfontbkcolor(0x000000, img);
		for (int i = 0; i < 4; ++i)
		{
			outtextxy(getwidth(img) / 2 - 2 * font_size, origin_height + (font_size + line_gap)*i, s[i], img);
		}

		//logo和选项移出
		for (; is_run(); delay_fps(60))
		{
			cleardevice();
			if (user_select == 2)//如果是选择了游戏说明
			{
				putimage(0, 0, des_img);
			}
			putimage(0, selection_img_positiony, img);
			if (selection_img_positiony < getheight())
			{
				selection_img_positiony += 5;
				putimage(0, logo_img_positiony, logo_img);
				logo_img_positiony -= 5;
				while (mousemsg())//清空多于鼠标消息缓存
				{
					msg = getmouse();
				}
				msg = { 0 };//清空msg
			}
			else
			{
				if (user_select == 2)
				{
					do
					{
						play_BGM(gameconfig, 2);
						mousemsg();
						msg = getmouse();
					} while (!((int)msg.is_up() && (int)msg.is_left()));
				}
				break;
			}

		}
	} while (user_select == 2);

	key[0] = user_select;
	play_BGM(gameconfig, 0);

	delimage(img);
	delimage(des_img);
	delimage(logo_temp1);
	delimage(logo_img);
}

void gameover_cartoon(game_config &gameconfig)
{
	play_BGM(gameconfig, 0);
	print_scene(gameconfig, 0);
	print_role("clear", gameconfig);
	print_scene(gameconfig, 3);
	PIMAGE game_over_temp = newimage();
	PIMAGE game_over_img = newimage(getwidth(), getheight());
	getimage(game_over_temp, "resource\\image\\game_over.jpg", 0, 0);
	putimage(game_over_img, 0, 0, getwidth(game_over_img), getheight(game_over_img), game_over_temp, 0, 0, getwidth(game_over_temp), getheight(game_over_temp));
	for (int i = 0; i < 300; delay_fps(60))
	{
		anti_revive(0xf70000, 1, gameconfig);
		++i;
	}

	update_BGM(gameconfig, 21);
	play_BGM(gameconfig, 1);

	for (; gameconfig.event_clock < 255; delay_fps(60))
	{
		putimage(0, 0, game_over_img);
		revive(0xf70000, 1, gameconfig);
		++gameconfig.event_clock;
	}

	getch();
	gameconfig.event_clock = 1;
	for (int i = 0; i < 300; delay_fps(60))
	{
		anti_revive(0x0, 1, gameconfig);
		++i;
	}

	play_BGM(gameconfig, 0);
	delimage(game_over_img);
	delimage(game_over_temp);
}

void game_core(game_config &gameconfig, vector< int > &key)
{
	gameconfig.game_control[6] = 1;//打开楼层打印

	/*********************/
	update_BGM(gameconfig);

	/***********游戏过程***********/
	for (;is_run();delay_fps(60))
	{
		if (gameconfig.game_control[5] && receive_key(key))
		{

			switch (key[0])
			{
			case 0:
				gameconfig.game_control[0] = 0;
				break;
			case 1:
				gameconfig.prole->role_face_change(key[1]);
				gameconfig.event_number = event_sensor(gameconfig);
				if (gameconfig.event_number >= 0)
				{
					gameconfig.event_clock = 0;
					gameconfig.game_control[0] = 1;
					gameconfig.game_control[5] = 0;
				}
				break;
			case 2:
				switch (key[1])
				{
				case 106://查看怪物
					gameconfig.event_number = 7;
					gameconfig.game_control[0] = 1;
					gameconfig.game_control[5] = 0;
					break;
				case 107://K
					if (gameconfig.prole->role_info["compass"] && gameconfig.prole->floor_reached[gameconfig.current_floor_number + 1])
					{
						gameconfig.event_number = 3;
						gameconfig.game_control[0] = 1;
						gameconfig.game_control[5] = 0;
						gameconfig.event_monster_number = 10;
						gameconfig.game_control[1] = 1;
					}
					break;
				case 108://L
					if (gameconfig.prole->role_info["compass"])
					{
						gameconfig.event_number = 3;
						gameconfig.game_control[0] = 1;
						gameconfig.game_control[5] = 0;
						gameconfig.event_monster_number = 11;
						gameconfig.game_control[1] = 1;
					}
					break;
				case 112://P
					gameconfig.event_number = 23;
					gameconfig.game_control[0] = 1;
					gameconfig.game_control[5] = 0;
					break;
				case 117://U
					gameconfig.event_number = 22;
					gameconfig.game_control[0] = 1;
					gameconfig.game_control[5] = 0;
					break;
				}

				break;
			case 3://
				break;
			default:break;
			}
		}

		if (gameconfig.game_control[6])
		{
			print_bkgd();
			for (int i = 0; i < 3; ++i)
			{
				print_scene(gameconfig, i);
			}
			print_frame(*(gameconfig.pgame_scene));
		}

		//更新游戏区
		if (1)
		{
			update_floor_data(gameconfig);
			++gameconfig.floor_clock;
		}

		print_role("stand", gameconfig);

		//事件运作器
		if (gameconfig.game_control[0])
		{
			event_trigger(gameconfig);
			++gameconfig.event_clock;
			my_flush();
			delay(10);

		}

		//事件结束
		if (!gameconfig.game_control[0])
		{
			gameconfig.event_clock = 0;
			gameconfig.event_number = -1;
			gameconfig.game_control[5] = 1;
			gameconfig.game_control[1] = 0;
			gameconfig.game_control[4] = 0;
			gameconfig.power_gather_control.reset();
		}

		//更新游戏区
		if (gameconfig.game_control[6])
		{
			print_scene(gameconfig, 3);
		}

		play_BGM(gameconfig, 2);

		key[0] = key[1] = 0;
		++gameconfig.game_clock;

		//游戏结束
		if (is_game_over(gameconfig))
		{
			gameconfig.event_clock = 1;
			break;
		}
		delay(20);
		//api_sleep(20);
	}
}
