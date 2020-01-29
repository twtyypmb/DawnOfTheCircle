#include "monster_class.h"

using namespace std;

bool monster::init_monster(int set_monster_number)
{
    vector< int > temp(2,0);
    //this->monster_position.push_back(0);
    //this->monster_position.push_back(0);
    this->monster_number=set_monster_number;
    this->monster_img_number.push_back(temp);
    this->monster_img_number.push_back(temp);
    this->monster_info["monster_number"]=set_monster_number;
    monster_info["life"]=10;
    monster_info["attack"]=0;
    monster_info["defence"]=0;
    monster_info["gold"]=0;
    monster_info["exp"]=0;
    /**event类别：
    -1：不可通过
    0:无事件
    1：有触发事件1:战斗
    2：开门，钥匙减少
    3:楼层改变
    4:钥匙增加
    **/
    /**event类别：
    0：
    1：
    2：
    **/

    string monster_file="resource\\monster\\"+int2str(set_monster_number)+".mst";
    fstream read_monster_file(monster_file.c_str(),fstream::in);
    if(!read_monster_file)
    {
        test(2, set_monster_number);
        //throw runtime_error("read floor file error!");
        exit(2);
    }

    read_monster_file>>monster_name;
    read_monster_file>>monster_info["event"];//触发后可通过
    read_monster_file>>monster_img_number[0][0];
    read_monster_file>>monster_img_number[0][1];
    read_monster_file>>monster_img_number[1][0];
    read_monster_file>>monster_img_number[1][1];
    read_monster_file>>monster_info["life"];
    read_monster_file>>monster_info["attack"];
    read_monster_file>>monster_info["defence"];
    read_monster_file>>monster_info["gold"];
    read_monster_file>>monster_info["exp"];
    read_monster_file>>monster_info["dialog"];
    read_monster_file>>monster_info["music"];

    read_monster_file.close();
    read_monster_file.clear();

    return true;
}

bool monster::monster_property_output(vector < int > &ivec)
{
    ivec.push_back(this->monster_info["life"]);
    ivec.push_back(this->monster_info["attack"]);
    ivec.push_back(this->monster_info["defence"]);
    ivec.push_back(this->monster_info["event"]);
    return true;
}
