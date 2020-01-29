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
    int event_monster_number;//ǿ�ƴ��������������

    /**
    0:event_start;  �¼���ʼ�ͽ�����־����ʼֵ��0
    1:event_trig_mode;  �¼������־��0Ϊ�Ƕ��󴥷���1Ϊ���󴥷�����ʼֵ��0
    2:game_complete;    ��Ϸͨ�أ���ʼֵ��0
    3:game_over;    ��Ϸ��������ʼֵ��0
    4:tempflag; �¼���־��ÿ���¼�����;��һ������ʼֵ��0
    5:role_key_control; ��ɫ���ƣ�0Ϊ���ɲ����� 1Ϊ�ɲ�������ʼֵ��0
    6:print_game_scnene_control;  ��Ϸ����ӡ���ƣ�0Ϊ���ɴ�ӡ�� 1Ϊ�ɴ�ӡ����ʼֵ��0
    7:��������ʼֵ��0
    **/

    bitset< 8 > game_control;

    //����16��������ı�־λ
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


/**���հ���������vector����һλ����ֵ���ͣ��ڶ�λ����ֵ**/
bool receive_key(vector<int> &direction);

/**����ɷ��Ӯ��δʹ��**/
bool unbattlable(game_config &gameconfig);

/**ս�����̣�BOSSսʹ�ã�����1��ϵͳ���ã�����2������**/
bool battle_process(game_config &gameconfig,monster &current_monster);

/**��¥�㵽��Ϸ��������1��ϵͳ����**/
bool update_floor_data(game_config &gameconfig);

/**����ɫ������1�������֣�����2��ϵͳ����**/
bool print_role(string command_control,game_config &gameconfig);

/**��ʼ��ȫ��¥�㣬������floor����**/
bool init_allfloor(my_floor allfloor[]);

/**����ȫ��¥�㣬������floor����**/
bool reset_allfloor(my_floor allfloor[]);

/**������**/
bool print_bkgd(void);

/**�������򣬲�����ϵͳ����**/
bool print_scene(game_config &gameconfig);

/**�¼���������������ϵͳ����**/
bool event_trigger(game_config &gameconfig);

/**��ȡ��ǰ����ţ�������ϵͳ���ã�����ֵ��������**/
int get_face_to_monster_number(game_config &gameconfig);

/**�¼���Ӧ����������ϵͳ���ã�����ֵ���¼����**/
int event_sensor(game_config &gameconfig);

/**����ս��������
����1�������֣���0ʱΪ��ս����0ʱָģ��ս�������ڹ����б�
����2��ϵͳ���ã�
����3�����
����ֵ��������ɵ��˺�ֵ**/
int quick_battle(int control_int, game_config &gameconfig, monster &current_monster);//����ս��

/**����غ���������1������Ѫ��������2����ɫ�˺�ֵ������ֵ������غ���**/
int round_count(int a,int b);

/**����¼�����ʱ�Ķ��ఴ��**/
bool my_flush(void);

/**��ӡ�Ի�������1��ϵͳ���ã�����,2���Ի���ţ�����3���¼�ʱ��**/
bool print_dialog(game_config &gameconfig, int dialog_number, int &dialog_clock);

/**��ӡ���ڿ򣬲�����������**/
bool print_frame(window_area &winarea);
bool print_frame(window_area &winarea, window_area &gamescene);

/**�����б�����1��ϵͳ����**/
bool monster_list(game_config &gameconfig);

/**���Ŷ���������1��ϵͳ���ã�����2����ǰ��� ����3,4����ʱ����**/
bool open_door_cartoon(game_config &gameconfig , monster &current_monster, int tempx, int tempy);

/**��ӡ�����򣬲���1�������򣬲���2��Ҫ��ӡ������**/
void print_power_circle(power_circle &powercirle, window_area &winarea);

/**�����ٻ�����������1��ϵͳ����**/
void quadruple_summon_cartoon(game_config &gameconfig);

/**�ж��Ƿ���Ϸ������������ϵͳ����**/
int is_game_over(game_config &gameconfig);

/**�����ӡ����������1��2���������꣬����3�������뾶������4�� ��תʱ��y��ĽǶȣ�����5��Ҫ��������**/
void quadruple_seal_cartoon(int positionx, int positiony, int randius, float angle, window_area &winarea);

/**�����ػ�������������ϵͳ����**/
void quadruple_guard_cartoon(game_config &gameconfig);

/**�����ۼ�������������ϵͳ����**/
void power_gather_cartoon(game_config &gameconfig);

/**�ж����ķ��ţ�����0����1��С��0����-1������0����0**/
int my_sgn(int number);

/**��ӡ����������1������������2��Ҫ��ӡ������**/
void print_light_pillar(light_pillar &lightpillar, window_area &winarea);

/**�����Ͷ�����������ϵͳ����**/
void death_transport_cartoon(game_config &gameconfig);

/**��ʥ���������������ϵͳ����**/
void holy_blast_cartoon(game_config &gameconfig);

/**�¹�������������������ϵͳ����**/
void dracula_purification_cartoon(game_config &gameconfig);

/**����������Ӱ��������������ϵͳ����**/
void super_overlord_wave_cartoon(game_config &gameconfig);

/**��ʥ���Ͷ�����������ϵͳ����**/
void holy_transport_cartoon(game_config &gameconfig);

/**���±������֣�����1��ϵͳ���ã�����2�����ֱ��**/
bool update_BGM(game_config &gameconfig);
bool update_BGM(game_config &gameconfig, int music_number);

/**�������֣�����1��ϵͳ���ã�����2�������֣�0Ϊֹͣ���ţ�1Ϊ���β��ţ�2Ϊѭ������**/
int play_BGM(game_config &gameconfig, int control);

/**���Ѷ���������1����ɫ������2���ٶȣ�����3��ϵͳ����**/
void revive(unsigned int col, int speed, game_config &gameconfig);

/**�����Ѷ���������1����ɫ������2���ٶȣ�����3��ϵͳ���ã�����4����Ҫ�ٴλ�������**/
void anti_revive(unsigned int col, int speed, game_config &gameconfig);
void anti_revive(unsigned int col, int speed, game_config &gameconfig, window_area &winarea);

/**��Ļ������������ϵͳ����**/
void play_prelude(game_config &gameconfig);

/**��Ļ������������ϵͳ����**/
void play_finale(game_config &gameconfig);

/**�õ��浵·��**/
string get_save_path(void);

/**����**/
bool save_data(game_config &gameconfig);

/**��ȡ**/
bool load_data(game_config &gameconfig);

/**����ϵͳ����**/
void update_gameconfig(game_config &gameconfig);

/**���˵�������1��ϵͳ���ã�����2����������**/
void main_menu(game_config &gameconfig, vector< int > &key);

/**��Ϸ��������**/
void gameover_cartoon(game_config &gameconfig);

/**��Ϸ���ģ�����1��ϵͳ���ã�����2����������**/
void game_core(game_config &gameconfig, vector< int > &key);

/**�ж��Ƿ���XPϵͳ**/
bool is_os_XP(void);

#endif // GAME_SYSTAM_H_

