#ifndef ROLE_CLASS_H_
#define ROLE_CLASS_H_
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <graphics.h>
#include <bitset>
#include "test.h"

using namespace std;

//class  floor;

class role
{
    public:
        bool init_role(void);
        bool set_role_position(int position[]);
        bool set_role_position(int positionx, int positiony);
        bool role_position_change(int direction_flag);
        bool role_property_chanege(int control);
        bool role_property_output(vector< int > &ivec);
        bool role_face_change(int direction_flag);

        role() {}
        ~role() {}
            //
        map< string, int > role_info;
        vector< int > coord;
        vector< vector< int > > role_img;
        vector< vector< int > > battle_img;
        bitset< 24 > floor_reached;//判断是否到达过该楼层
    private:
};
#endif // ROLE_CLASS_H_
