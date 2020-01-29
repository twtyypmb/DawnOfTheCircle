#ifndef GAME_SYSTAM_H_
#define GAME_SYSTAM_H_

//#include <stdexcept>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <cmath>
#include <bitset>
#include <windows.h>

#include "test.h"
#include "monster_class.h"
#include "floor_class.h"
#include "role_class.h"
#include "window_area_class.h"
#include "my_dialog_class.h"
#include "CommonResource.h"     

using namespace std;

class BGM
{
public:
    int music_number;
    int cycle_flag;
    float music_volume;
    int play_position[4];
    MUSIC msc;
    BGM():music_number(0), cycle_flag(0), music_volume(0.1) {}
};

class game_config
{
public:
    unsigned int game_clock;
    unsigned int floor_clock;
    unsigned int event_clock;
    int dialog_clock;
    int event_number;
    int current_floor_number;
    int event_monster_number;//强制触发的虚拟怪物编号

    /**
    0:event_start;  事件开始和结束标志，初始值：0
    1:event_trig_mode;  事件种类标志，0为非对象触发，1为对象触发，初始值：0
    2:game_complete;    游戏通关，初始值：0
    3:game_over;    游戏结束，初始值：0
    4:tempflag; 事件标志，每个事件上用途不一样，初始值：0
    5:role_key_control; 角色控制，0为不可操作， 1为可操作，初始值：0
    6:print_game_scnene_control;  游戏区打印控制，0为不可打印， 1为可打印，初始值：0
    7:保留，初始值：0
    **/

    bitset< 8 > game_control;

    //控制16个能量球的标志位
    bitset< 16 > power_gather_control;

    role *prole;
    my_floor *pall_floor;
    window_area *pgame_scene;
    window_area *prole_property;
    window_area *pkey_detail;
    window_area *phelp_scene;
    window_area *pdialog_scene;
    BGM bgm;
    game_config():game_clock(0),floor_clock(0),
                event_clock(0),dialog_clock(0),
                event_number(0), current_floor_number(0),
                 event_monster_number(0) {}
    ~game_config(){}
};

class power_circle
{
    public:
        int radius;
        unsigned int color1;
        unsigned int color2;
        int positionx;
        int positiony;
        unsigned char blr_alpha;
        power_circle():radius(1), color1(0x7777ff),
                        color2(0xffffff), positionx(0),
                        positiony(0), blr_alpha(0xff) {}
};

class light_pillar
{
    public:
        int width;
        int height;
        int positionx;
        int positiony;
        float circle_rate;
        unsigned int color1;
        unsigned int color2;
        unsigned char blr_alpha;
        light_pillar():width(1), height(1),
                       positionx(20), positiony(20),
                       circle_rate(0.3333),
                       color1(0x111111),color2(0xf73333), blr_alpha(0xff) {}
};


/**接收按键，参数vector，第一位，键值类型，第二位，键值**/
bool receive_key(vector<int> &direction);

/**计算可否打赢，未使用**/
bool unbattlable(game_config &gameconfig);

/**战斗过程，BOSS战使用，参数1：系统配置，参数2：怪物**/
bool battle_process(game_config &gameconfig,monster &current_monster);

/**画楼层到游戏区，参数1：系统配置**/
bool update_floor_data(game_config &gameconfig);

/**画角色，参数1：控制字，参数2：系统配置**/
bool print_role(string command_control,game_config &gameconfig);

/**初始化全部楼层，参数，floor数组**/
bool init_allfloor(my_floor allfloor[]);

/**重置全部楼层，参数，floor数组**/
bool reset_allfloor(my_floor allfloor[]);

/**画背景**/
bool print_bkgd(void);

/**画子区域，参数：系统配置**/
bool print_scene(game_config &gameconfig);

/**事件触发器，参数：系统配置**/
bool event_trigger(game_config &gameconfig);

/**读取面前怪物号，参数，系统配置，返回值，怪物编号**/
int get_face_to_monster_number(game_config &gameconfig);

/**事件感应器，参数：系统配置，返回值：事件编号**/
int event_sensor(game_config &gameconfig);

/**快速战斗函数，
参数1：控制字，非0时为真战斗，0时指模拟战斗（用于怪物列表）
参数2：系统配置，
参数3：怪物，
返回值，怪物造成的伤害值**/
int quick_battle(int control_int, game_config &gameconfig, monster &current_monster);//快速战斗

/**计算回合数，参数1：怪物血量，参数2：角色伤害值，返回值，所需回合数**/
int round_count(int a,int b);

/**清空事件进行时的多余按键**/
bool my_flush(void);

/**打印对话，参数1：系统配置，参数,2：对话编号，参数3：事件时钟**/
bool print_dialog(game_config &gameconfig, int dialog_number, int &dialog_clock);

/**打印窗口框，参数：子区域**/
bool print_frame(window_area &winarea);
bool print_frame(window_area &winarea, window_area &gamescene);

/**怪物列表，参数1：系统配置**/
bool monster_list(game_config &gameconfig);

/**开门动画，参数1，系统配置，参数2，当前怪物， 参数3,4，临时坐标**/
bool open_door_cartoon(game_config &gameconfig , monster &current_monster, int tempx, int tempy);

/**打印能量球，参数1，能量球，参数2，要打印的区域**/
void print_power_circle(power_circle &powercirle, window_area &winarea);

/**四灵召唤动画：参数1：系统配置**/
void quadruple_summon_cartoon(game_config &gameconfig);

/**判断是否游戏结束，参数，系统配置**/
int is_game_over(game_config &gameconfig);

/**四灵封印动画：参数1，2，动画坐标，参数3，动画半径，参数4， 旋转时与y轴的角度，参数5，要画的区域**/
void quadruple_seal_cartoon(int positionx, int positiony, int randius, float angle, window_area &winarea);

/**四灵守护动画，参数，系统配置**/
void quadruple_guard_cartoon(game_config &gameconfig);

/**能量聚集动画：参数，系统配置**/
void power_gather_cartoon(game_config &gameconfig);

/**判断数的符号，大于0返回1，小于0返回-1，等于0返回0**/
int my_sgn(int number);

/**打印光柱，参数1，光柱，参数2，要打印的区域**/
void print_light_pillar(light_pillar &lightpillar, window_area &winarea);

/**死神传送动画，参数，系统配置**/
void death_transport_cartoon(game_config &gameconfig);

/**神圣冲击动画，参数，系统配置**/
void holy_blast_cartoon(game_config &gameconfig);

/**德古拉净化动画，参数，系统配置**/
void dracula_purification_cartoon(game_config &gameconfig);

/**超级霸王电影弹动画，参数，系统配置**/
void super_overlord_wave_cartoon(game_config &gameconfig);

/**神圣传送动画，参数，系统配置**/
void holy_transport_cartoon(game_config &gameconfig);

/**更新背景音乐，参数1，系统配置，参数2，音乐编号**/
bool update_BGM(game_config &gameconfig);
bool update_BGM(game_config &gameconfig, int music_number);

/**播放音乐，参数1，系统配置，参数2，控制字，0为停止播放，1为单次播放，2为循环播放**/
int play_BGM(game_config &gameconfig, int control);

/**清醒动画，参数1，颜色，参数2，速度，参数3，系统配置**/
void revive(unsigned int col, int speed, game_config &gameconfig);

/**反清醒动画，参数1，颜色，参数2，速度，参数3，系统配置，参数4，需要再次画的区域**/
void anti_revive(unsigned int col, int speed, game_config &gameconfig);
void anti_revive(unsigned int col, int speed, game_config &gameconfig, window_area &winarea);

/**序幕动画：参数，系统配置**/
void play_prelude(game_config &gameconfig);

/**闭幕动画：参数，系统配置**/
void play_finale(game_config &gameconfig);

/**得到存档路径**/
string get_save_path(void);

/**保存**/
bool save_data(game_config &gameconfig);

/**读取**/
bool load_data(game_config &gameconfig);

/**更新系统配置**/
void update_gameconfig(game_config &gameconfig);

/**主菜单：参数1，系统配置，参数2，按键接收**/
void main_menu(game_config &gameconfig, vector< int > &key);

/**游戏结束动画**/
void gameover_cartoon(game_config &gameconfig);

/**游戏核心，参数1，系统配置，参数2，按键接收**/
void game_core(game_config &gameconfig, vector< int > &key);

/**判断是否是XP系统**/
bool is_os_XP(void);

#endif // GAME_SYSTAM_H_

