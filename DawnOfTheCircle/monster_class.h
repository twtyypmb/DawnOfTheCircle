#ifndef MONSTER_CLASS_H_
#define MONSTER_CLASS_H_
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "test.h"

using namespace std;


class monster
{
    public:
        bool init_monster(int monster_number);
        //bool set_monster_property(void);
        bool monster_property_output(vector < int > &ivec) ;
        monster() {}
        ~monster() {}
        //friend bool print_floor_role(floor *curren_floor,role *protagonist,const unsigned int game_clock);
        //friend void mainloop(void);

    //private:
        int monster_number;
        string monster_name;
        map<string,int> monster_info;
        //vector< int > monster_position;
        vector< vector< int > > monster_img_number;
    private:
};
#endif // MONSTER_CLASS_H_
