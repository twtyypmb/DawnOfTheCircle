#include "test.h"

string int2str( int num)
{


    if (num == 0 )
    {
        return "0" ;
    }
    string str = "" ;
    int num_ = num > 0 ? num : - 1 * num;
    while (num_)
    {
        str = ( char )(num_ % 10 + 48 ) + str;
       num_ /= 10 ;
    }
    if (num < 0 )
      {
          str = " - " + str;
      }
    return str;
}

string uint2str( unsigned int num)
{


    if (!num )
    {
        return "0" ;
    }

    string str = "" ;
    unsigned int num_=num;
    while (num_)
    {
        str = ( char )(num_ % 10 + 48 ) + str;
       num_ /= 10 ;
    }
    return str;
}

void test(int i, int game_clock)
{

    string floor_filename="resource\\err\\"+int2str(i)+".err";
    fstream read_floor_file(floor_filename.c_str(),fstream::out);
    read_floor_file<<game_clock;
    read_floor_file.close();
    read_floor_file.clear();
}

void test(int i, string s)
{

    string floor_filename="resource\\err\\"+int2str(i)+".err";
    fstream read_floor_file(floor_filename.c_str(),fstream::out);
    read_floor_file<<s;
    read_floor_file.close();
    read_floor_file.clear();
}

void test(int i,float f)
{

    string floor_filename="resource\\err\\"+int2str(i)+".err";
    fstream read_floor_file(floor_filename.c_str(),fstream::out);
    read_floor_file<<f;
    read_floor_file.close();
    read_floor_file.clear();
}

void print_info(int idx,int x,int y)
{
    char s[10];
    char s1[10]="     ";
    outtextxy(x, y, s1);
    sprintf_s(s, "%d", idx);
    outtextxy(x, y, s);
}

