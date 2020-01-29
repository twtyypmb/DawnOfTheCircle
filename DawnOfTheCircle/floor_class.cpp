#include "floor_class.h"



using namespace std;

bool my_floor::init_floor(int init_floor_number)
{
    vector< int > temp_ivec(11,0);
    for(int i = 0; i < 11; ++i)
    {
       this->floor_info.push_back(temp_ivec);
    }
    return true;
}

bool my_floor::reset_floor(int init_floor_number)
{
    this->floor_number=init_floor_number;
    string tempstring;
    string floor_filename="resource\\floor\\"+int2str(init_floor_number)+".floor";
    fstream read_floor_file(floor_filename.c_str(),fstream::in);
    if(!read_floor_file)
    {
        //throw runtime_error("read floor file error!");
        test(3, init_floor_number);
        exit(3);
    }

    //int temp(0);

    read_floor_file >> this->floor_name;

    for(int i=0;i<2;++i)
    {
        for(int j=0;j<2;++j)
        {
            read_floor_file >> this->role_init_position[i][j];
        }
    }

    read_floor_file >> this->music_number;

    //vector< int > temp_ivec(11,0);
    for(vector< vector< int > >::iterator ivecivec = this->floor_info.begin(); ivecivec != this->floor_info.end(); ++ivecivec)
    {
        for(vector< int >::iterator ivec = ivecivec->begin(); ivec != ivecivec->end(); ++ivec)
        {
            read_floor_file >> *ivec;
        }
    }

    read_floor_file.close();
    read_floor_file.clear();

    return true;
}

bool my_floor::set_floor_info(int position_number, int expect_number)
{
    vector< vector< int > >::size_type ivecvec_idx=position_number/11;
    vector< int >::size_type ivec_idx=position_number%11;


    if(ivecvec_idx>10||ivec_idx>10)
    {
        return false;
    }
    this->floor_info[ivecvec_idx][ivec_idx]=expect_number;
    return true;
}

/*bool floor::get_info(vector< vector< int > > &temp_floor_info)
{

    return true;
}*/
