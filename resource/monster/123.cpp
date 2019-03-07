#include <fstream>
#include <string>
using namespace std;

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

int main(void)
{
	string floor_filename;
	
    fstream read_floor_file;
	for(int i=0;i<170;++i)
	{
		floor_filename=int2str(i)+".mst";
		read_floor_file.open(floor_filename.c_str(),fstream::out|fstream::app);
		read_floor_file<<' ';
		read_floor_file<<0;
		read_floor_file.close();
		read_floor_file.clear();
	}
	
	return 0;
}