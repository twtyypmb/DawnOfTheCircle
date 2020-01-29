#ifndef FLOOR_CLASS_H_
#define FLOOR_CLASS_H_
#include <map>
#include <string>
#include <vector>
#include <graphics.h>
#include <fstream>
#include <stdexcept>
#include "test.h"

using namespace std;


class my_floor
{
    public:
        bool get_info(vector< vector< int > > &temp_floor_info);
        bool init_floor(int init_floor_number);
        bool reset_floor(int init_floor_number);
        bool set_floor_info(int position_number, int expect_number);
        my_floor():floor_number(0), floor_name(" ") { }
        ~my_floor() { }
        //friend bool print_floor_role(floor *curren_floor,role *protagonist,const unsigned int game_clock);
        //friend void mainloop(void);
        //friend bool role::role_position_change(int direction_flag,const floor* current_floor);
    //
        int role_init_position[2][2];
        int floor_number;
        int music_number;
        string floor_name;
        vector< vector< int > > floor_info;
    private:
};
#endif // MAP_INFO_H_
