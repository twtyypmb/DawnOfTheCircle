#include "role_class.h"


using namespace std;

bool role::init_role(void)
{
    string role_img_file="resource\\role\\img.rol";
    fstream read_role_img(role_img_file.c_str(),fstream::in);
    if(!read_role_img)
    {
        test(1,1);
        //throw runtime_error("read floor file error!");
        exit(1);
    }
    /*read_role_data>>*/this->role_info["level"] = 1;
    /*read_role_data>>*/this->role_info["life"] = 1000;
    /*read_role_data>>*/this->role_info["attack"] = 160;
    /*read_role_data>>*/this->role_info["defence"] = 200;
    /*read_role_data>>*/this->role_info["gold"] = 0;
    /*read_role_data>>*/this->role_info["exp"] = 0;
    /*read_role_data>>*/this->role_info["yellow_key"] = 0;
    /*read_role_data>>*/this->role_info["blue_key"] = 0;
    /*read_role_data>>*/this->role_info["red_key"] = 0;
    /*read_role_data>>*/this->role_info["floor"] = 0;
    /*read_role_data>>*/this->role_info["face_direction"] = 0;
    /*read_role_data>>*/this->role_info["compass"] = 0;
    /*read_role_data>>*/this->role_info["fruit"] = 0;
    this->coord.push_back(-1);
    this->coord.push_back(-1);

    vector< int > ivec(8);
    for(int i=0;i<4;++i)
    {
        for(int j=0;j<8;++j)
        {
            read_role_img>>ivec[j];
        }
        this->role_img.push_back(ivec);
    }

    for(int i=0;i<4;++i)
    {
        for(int j=0;j<8;++j)
        {
            read_role_img>>ivec[j];
        }
        this->battle_img.push_back(ivec);
    }

    read_role_img.close();
    read_role_img.clear();

    return true;
}

bool role::set_role_position(int position[])
{
    this->coord[0]=position[0];
    this->coord[1]=position[1];
    return true;
}

bool role::set_role_position(int positionx, int positiony)
{
    this->coord[0]=positionx;
    this->coord[1]=positiony;
    return true;
}

bool role::role_face_change(int direction_flag)
{
    switch(direction_flag)
    {
        case 119:this->role_info["face_direction"]=0;return true;
        case 97:this->role_info["face_direction"]=1;return true;
        case 115:this->role_info["face_direction"]=2;return true;
        case 100:this->role_info["face_direction"]=3;return true;
        default:break;
    }
    return false;
}

bool role::role_position_change(int direction_flag)
{

    int tempx,tempy;
    tempx=coord[0];
    tempy=coord[1];
    switch(direction_flag)
    {
        //case 72:
        case  0:tempy-=1;break;
        //case 75:
        case  1:tempx-=1;break;
        //case 80:
        case  2:tempy+=1;break;
        //case 77:
        case  3:tempx+=1;break;
        default:break;
    }

    if(tempx>10||tempy>10||tempx<0||tempy<0)
    {

        return false;
    }

    coord[0]=tempx;
    coord[1]=tempy;


    return true;
}

bool role::role_property_output(vector< int > &ivec)
{
    ivec.push_back(this->role_info["life"]);
    ivec.push_back(this->role_info["attack"]);
    ivec.push_back(this->role_info["defence"]);
    return true;
}

